from django import forms
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
from .models import Patient, Appointment, VitalsReading, LabTest, InventoryItem, Bill, Room, Bed, VentilatorSession, EmergencyAlert, Ambulance, ROLE_CHOICES, Department

class PatientForm(forms.ModelForm):
    class Meta:
        model = Patient
        fields = ['name', 'age', 'gender', 'phone', 'email', 'medical_history']
        widgets = {
            'medical_history': forms.Textarea(attrs={'rows': 3, 'placeholder': 'Enter medical history, one entry per line...'}),
        }

class AppointmentForm(forms.ModelForm):
    department = forms.ModelChoiceField(queryset=Department.objects.all(), required=True, label="Department")

    class Meta:
        model = Appointment
        fields = ['patient', 'department', 'date', 'time_slot', 'reason']
        widgets = {
            'date': forms.DateInput(attrs={'type': 'date'}),
            'time_slot': forms.TimeInput(attrs={'type': 'time'}),
        }

class VitalsReadingForm(forms.ModelForm):
    class Meta:
        model = VitalsReading
        fields = ['heart_rate', 'systolic_bp', 'diastolic_bp', 'temperature', 'oxygen_level']

    def clean_temperature(self):
        temp = self.cleaned_data.get('temperature')
        if temp < 50.0 or temp > 120.0:
            raise forms.ValidationError("Please enter a valid patient body temperature.")
        return temp

class LabTestForm(forms.ModelForm):
    class Meta:
        model = LabTest
        fields = ['patient', 'test_name', 'requested_by', 'status', 'result_details']
        widgets = {
            'result_details': forms.Textarea(attrs={'rows': 3}),
        }

class InventoryItemForm(forms.ModelForm):
    class Meta:
        model = InventoryItem
        fields = '__all__'
        widgets = {
            'manufacturing_date': forms.DateInput(attrs={'type': 'date'}),
            'expiry_date': forms.DateInput(attrs={'type': 'date'}),
        }

    def clean(self):
        cleaned_data = super().clean()
        mfg = cleaned_data.get('manufacturing_date')
        exp = cleaned_data.get('expiry_date')
        if mfg and exp and exp < mfg:
            raise forms.ValidationError("Expiry date cannot be before manufacturing date.")
        price = cleaned_data.get('price')
        if price is not None and price < 0:
            raise forms.ValidationError("Price cannot be negative.")
        quantity = cleaned_data.get('quantity')
        if quantity is not None and quantity < 0:
            raise forms.ValidationError("Stock quantity cannot be negative.")
        return cleaned_data

class BillForm(forms.ModelForm):
    class Meta:
        model = Bill
        exclude = ['tax']
        labels = {
            'discount': 'Discount (%)',
        }

    def clean(self):
        cleaned_data = super().clean()
        for field in ['consultation_fee', 'room_charges', 'medicine_charges', 'lab_charges', 'other_charges', 'discount']:
            val = cleaned_data.get(field)
            if val is not None and val < 0:
                raise forms.ValidationError(f"{field.replace('_', ' ').capitalize()} cannot be negative.")
        
        discount = cleaned_data.get('discount')
        if discount is not None and discount > 100:
            raise forms.ValidationError("Discount percentage cannot exceed 100%.")
        
        return cleaned_data

class RoomForm(forms.ModelForm):
    number_of_beds = forms.IntegerField(min_value=0, initial=0, help_text="Automatically create this many beds when saving.")

    class Meta:
        model = Room
        fields = ['room_number', 'room_type', 'private_category', 'status']

    def clean(self):
        cleaned_data = super().clean()
        room_type = cleaned_data.get('room_type')
        private_category = cleaned_data.get('private_category')

        if room_type == 'Private' and not private_category:
            self.add_error('private_category', 'Private Category is required when Room Type is Private.')
        elif room_type != 'Private':
            cleaned_data['private_category'] = None

        return cleaned_data

class BedForm(forms.ModelForm):
    class Meta:
        model = Bed
        fields = ['room', 'bed_number', 'category', 'status', 'patient']

class BedAllocationForm(forms.ModelForm):
    class Meta:
        model = Bed
        fields = ['patient', 'medical_case']

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        # Show only patients not currently assigned to any bed
        from .models import Patient
        self.fields['patient'].queryset = Patient.objects.filter(bed__isnull=True).distinct()

    def save(self, commit=True):
        bed = super().save(commit=False)
        if bed.patient:
            bed.status = 'Occupied'
        else:
            bed.status = 'Available'
        if commit:
            bed.save()
        return bed

class VentilatorSessionForm(forms.ModelForm):
    class Meta:
        model = VentilatorSession
        fields = ['mode', 'oxygen_level', 'respiratory_rate', 'tidal_volume', 'peep', 'peak_pressure', 'plateau_pressure', 'connected']

    def clean(self):
        cleaned_data = super().clean()
        return cleaned_data

class EmergencyAlertForm(forms.ModelForm):
    class Meta:
        model = EmergencyAlert
        fields = ['specialization_required', 'details']
        widgets = {
            'details': forms.Textarea(attrs={'rows': 3}),
        }

class AmbulanceForm(forms.ModelForm):
    class Meta:
        model = Ambulance
        fields = ['ambulance_number', 'driver_name', 'driver_contact', 'current_location', 'latitude', 'longitude', 'status']

class SignUpForm(UserCreationForm):
    role = forms.ChoiceField(
        choices=[('', '---------')] + list(ROLE_CHOICES), 
        required=True
    )
    phone = forms.CharField(max_length=20, required=False, help_text="Optional contact number.")
    staff_id = forms.CharField(max_length=50, required=False)
    date_of_birth = forms.DateField(required=False, widget=forms.DateInput(attrs={'type': 'date'}), help_text="Optional Date of Birth.")

    field_order = ['first_name', 'last_name', 'date_of_birth', 'role', 'username', 'email', 'phone', 'staff_id']

    class Meta:
        model = User
        fields = ['first_name', 'last_name', 'username', 'email']

    def clean(self):
        cleaned_data = super().clean()
        role = cleaned_data.get('role')
        staff_id = cleaned_data.get('staff_id')

        if role == 'Admin':
            from .models import UserProfile
            admin_count = UserProfile.objects.filter(role='Admin').count() + 1
            suffix = f"_AD_{admin_count:03d}"
            
            if staff_id:
                if not staff_id.endswith(suffix):
                    # Ensure we don't duplicate if they somehow typed it exactly
                    # Strip any existing _AD_... just in case? No, just append it.
                    staff_id = f"{staff_id}{suffix}"
            else:
                staff_id = f"ADMIN{suffix}"
                
            cleaned_data['staff_id'] = staff_id

        elif role and role != 'Patient' and not staff_id:
            self.add_error('staff_id', 'Staff ID is required for all non-patient accounts.')
        
        return cleaned_data
