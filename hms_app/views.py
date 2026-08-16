from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.http import HttpResponseForbidden
from django.db.models import Sum, Q, Count
import datetime
from .models import (
    UserProfile, Department, DoctorProfile, NurseProfile, Patient, VitalsReading,
    EMRRecord, Ventilator, VentilatorSession, RiskAssessment, Room, Bed, Appointment,
    EmergencyAlert, Ambulance, InventoryItem, MortuaryRecord, Attendance, LabTest, Bill, Notification
)
from .forms import (
    PatientForm, AppointmentForm, VitalsReadingForm, LabTestForm, InventoryItemForm,
    BillForm, BedForm, BedAllocationForm, VentilatorSessionForm, EmergencyAlertForm, AmbulanceForm
)

def landing_page(request):
    doctors = DoctorProfile.objects.all()[:4]
    departments = Department.objects.all()
    return render(request, 'landing.html', {'doctors': doctors, 'departments': departments})

def public_emergency(request):
    if request.method == 'POST':
        spec = request.POST.get('specialization', 'General')
        location = request.POST.get('location', 'Unknown Location')
        contact = request.POST.get('contact', '')
        
        details = f"PUBLIC SOS at {location}. Contact: {contact}. Type: {spec}"
        alert = EmergencyAlert.objects.create(specialization_required=spec, details=details)
        docs = alert.get_notified_doctors()
        
        from .utils import send_sms_notification
        
        # 1. Send SMS to Doctors
        for d in docs:
            if d.profile.phone:
                send_sms_notification(d.profile.phone, f"CODE BLUE [{spec}]: Emergency triggered at {location}. Check dashboard immediately.")
        
        # Try to dispatch ambulance
        amb = Ambulance.objects.filter(status='Available').first()
        if amb:
            amb.assign(location)
            # 2. Send SMS to Ambulance Driver
            if amb.driver_contact:
                send_sms_notification(amb.driver_contact, f"🚨 URGENT DISPATCH: New emergency at {location}. Patient contact: {contact}. Proceed immediately.")
            
            # 3. Send SMS to Patient
            send_sms_notification(contact, f"Ambulance {amb.ambulance_number} has been dispatched and is en route to your location ({location}). Please stay calm.")
            
            messages.success(request, f"Emergency dispatched! Ambulance {amb.ambulance_number} is on the way to {location}. {docs.count()} doctors alerted.")
        else:
            send_sms_notification(contact, f"CRITICAL: Alert broadcasted to {docs.count()} doctors, but NO AMBULANCES ARE CURRENTLY AVAILABLE. Please seek alternative transport.")
            messages.warning(request, f"Emergency Alert broadcasted to {docs.count()} doctors, but NO AMBULANCES ARE CURRENTLY AVAILABLE. Please seek alternative transport immediately.")
            
    return redirect('landing')

def login_view(request):
    if request.user.is_authenticated:
        return redirect('dashboard_redirect')
    if request.method == 'POST':
        u = request.POST.get('username')
        p = request.POST.get('password')
        user = authenticate(request, username=u, password=p)
        if user is not None:
            login(request, user)
            return redirect('dashboard_redirect')
        else:
            # Check if user exists but is inactive
            from django.contrib.auth.models import User
            existing_user = User.objects.filter(username=u).first()
            if existing_user and existing_user.check_password(p) and not existing_user.is_active:
                messages.warning(request, "Your account is pending verification by an Administrator. Please check back later.")
            else:
                messages.error(request, "Invalid username or password.")
    return render(request, 'authentication/login.html')

def logout_view(request):
    logout(request)
    return redirect('login')

@login_required
def dashboard_redirect(request):
    try:
        profile = request.user.profile
        role = profile.role
    except UserProfile.DoesNotExist:
        # Default to Patient if profile missing but user is patient-like
        role = 'Patient'
    
    if role == 'Admin':
        return redirect('admin_dashboard')
    elif role == 'Doctor':
        return redirect('doctor_dashboard')
    elif role == 'Nurse':
        return redirect('nurse_dashboard')
    elif role == 'Receptionist':
        return redirect('receptionist_dashboard')
    elif role == 'Pharmacist':
        return redirect('pharmacist_dashboard')
    elif role == 'LabStaff':
        return redirect('lab_dashboard')
    elif role == 'Accountant':
        return redirect('accountant_dashboard')
    else:
        return redirect('patient_dashboard')

# RBAC helper decorator
def role_required(allowed_roles):
    def decorator(view_func):
        @login_required
        def _wrapped_view(request, *args, **kwargs):
            try:
                role = request.user.profile.role
            except UserProfile.DoesNotExist:
                role = 'Patient'
            if role in allowed_roles:
                return view_func(request, *args, **kwargs)
            return render(request, 'errors/403.html', status=403)
        return _wrapped_view
    return decorator

# --- DASHBOARDS ---

@role_required(['Admin'])
def admin_dashboard(request):
    ctx = {
        'total_patients': Patient.objects.count(),
        'total_doctors': DoctorProfile.objects.count(),
        'total_staff': UserProfile.objects.exclude(role='Patient').count(),
        'today_appointments': Appointment.objects.filter(date=datetime.date.today()).count(),
        'occupied_beds': Bed.objects.filter(status='Occupied').count(),
        'available_beds': Bed.objects.filter(status='Available').count(),
        'pending_bills_count': Bill.objects.filter(status='Pending').count(),
        'today_revenue': sum(b.get_total() for b in Bill.objects.filter(status='Paid', created_at__date=datetime.date.today())),
        'pending_lab_tests': LabTest.objects.filter(status__in=['Pending', 'Processing', 'Sample Collected']).count(),
        'recent_patients': Patient.objects.all().order_by('-created_at')[:5],
        'recent_appointments': Appointment.objects.all().order_by('-date', '-time_slot')[:5],
        'critical_alerts': EmergencyAlert.objects.filter(is_active=True)[:3],
        'low_stock_alerts': [item for item in InventoryItem.objects.all() if item.is_low_stock()][:4],
        'room_count': Room.objects.count(),
        # Total beds is the sum of beds across all rooms
        'total_beds': Bed.objects.count(),
        'vacant_beds': Bed.objects.filter(status='Available').count(),
    }
    return render(request, 'dashboards/admin.html', ctx)

@role_required(['Doctor'])
def doctor_dashboard(request):
    doc = get_object_or_404(DoctorProfile, profile__user=request.user)
    today = datetime.date.today()
    ctx = {
        'doc': doc,
        'today_appointments': Appointment.objects.filter(doctor=doc, date=today).order_by('time_slot'),
        'all_appointments': Appointment.objects.filter(doctor=doc).order_by('-date', 'time_slot'),
        'upcoming_appointments': Appointment.objects.filter(doctor=doc, date__gt=today).order_by('date', 'time_slot')[:5],
        'patients': Patient.objects.all()[:10],
        'recent_lab_reports': LabTest.objects.filter(requested_by=doc).order_by('-updated_at')[:5],
        'active_emergencies': EmergencyAlert.objects.filter(is_active=True, specialization_required__icontains=doc.specialization)[:3]
    }
    return render(request, 'dashboards/doctor.html', ctx)

@role_required(['Nurse'])
def nurse_dashboard(request):
    vitals_count = VitalsReading.objects.count()
    ctx = {
        'allocated_rooms': Room.objects.filter(status='Occupied'),
        'maintenance_rooms': Room.objects.filter(status='Maintenance'),
        'critical_vitals': [v for v in VitalsReading.objects.all().order_by('-recorded_at')[:10] if v.is_critical()],
        'active_ventilators': VentilatorSession.objects.filter(is_active=True),
        'recent_vitals': VitalsReading.objects.all().order_by('-recorded_at')[:8],
    }
    return render(request, 'dashboards/nurse.html', ctx)

@role_required(['Receptionist'])
def receptionist_dashboard(request):
    search_q = request.GET.get('q', '')
    if search_q:
        patients = Patient.objects.filter(
            Q(name__icontains=search_q) | Q(phone__icontains=search_q) | Q(email__icontains=search_q)
        )
    else:
        patients = Patient.objects.all().order_by('-created_at')[:8]
    
    ctx = {
        'patients': patients,
        'rooms': Room.objects.all().order_by('room_number'),
        'today_appointments': Appointment.objects.filter(date=datetime.date.today()),
        'available_ambulances': Ambulance.objects.filter(status='Available'),
        'room_count': Room.objects.count(),
        # Total beds across all rooms
        'total_beds': Bed.objects.count(),
        'vacant_beds': Bed.objects.filter(status='Available').count(),
        'occupied_beds': Bed.objects.filter(status='Occupied').count(),
        'all_patient_names': Patient.objects.values_list('name', flat=True),
    }
    return render(request, 'dashboards/receptionist.html', ctx)

@role_required(['Pharmacist'])
def pharmacist_dashboard(request):
    inventory = InventoryItem.objects.all()
    low_stock = [item for item in inventory if item.is_low_stock()]
    ctx = {
        'inventory': inventory,
        'low_stock': low_stock,
        'out_of_stock': [item for item in inventory if item.is_out_of_stock()],
        'expired_soon': [item for item in inventory if item.expiry_date <= datetime.date.today() + datetime.timedelta(days=90)]
    }
    return render(request, 'dashboards/pharmacist.html', ctx)

@role_required(['LabStaff'])
def lab_dashboard(request):
    ctx = {
        'pending_tests': LabTest.objects.filter(status__in=['Pending', 'Sample Collected', 'Processing']).order_by('created_at'),
        'completed_tests': LabTest.objects.filter(status='Completed').order_by('-updated_at')[:10]
    }
    return render(request, 'dashboards/laboratory.html', ctx)

@role_required(['Accountant'])
def accountant_dashboard(request):
    bills = Bill.objects.all().order_by('-created_at')
    ctx = {
        'bills': bills,
        'total_revenue': sum(b.get_total() for b in Bill.objects.filter(status='Paid')),
        'pending_payments': sum(b.get_total() for b in Bill.objects.filter(status='Pending')),
        'partially_paid': sum(b.get_total() for b in Bill.objects.filter(status='Partially Paid'))
    }
    return render(request, 'dashboards/accountant.html', ctx)

@login_required
def patient_dashboard(request):
    try:
        patient = Patient.objects.get(profile__user=request.user)
        # Always update age from profile if available
        if patient.profile.age is not None and patient.age != patient.profile.age:
            patient.age = patient.profile.age
            patient.save()
    except Patient.DoesNotExist:
        # Create default patient profile for user
        patient = Patient.objects.create(
            profile=request.user.profile,
            name=request.user.get_full_name() or request.user.username,
            age=request.user.profile.age or 30,
            gender='Other',
            phone=request.user.profile.phone or '123-456-7890'
        )

    ctx = {
        'patient': patient,
        'appointments': Appointment.objects.filter(patient=patient).order_by('-date'),
        'vitals': VitalsReading.objects.filter(patient=patient).order_by('-recorded_at'),
        'emr_records': EMRRecord.objects.filter(patient=patient).order_by('-created_at'),
        'bills': Bill.objects.filter(patient=patient).order_by('-created_at'),
        'lab_reports': LabTest.objects.filter(patient=patient).order_by('-updated_at')
    }
    return render(request, 'dashboards/patient.html', ctx)

@login_required
def patient_my_details(request):
    try:
        patient = Patient.objects.get(profile__user=request.user)
    except Patient.DoesNotExist:
        return redirect('patient_dashboard') # Fallback if no patient profile
    
    ctx = {
        'patient': patient,
        'vitals': VitalsReading.objects.filter(patient=patient).order_by('-recorded_at'),
    }
    return render(request, 'dashboards/my_details.html', ctx)

@login_required
def patient_my_prescriptions(request):
    try:
        patient = Patient.objects.get(profile__user=request.user)
    except Patient.DoesNotExist:
        return redirect('patient_dashboard')
    
    ctx = {
        'patient': patient,
        'emr_records': EMRRecord.objects.filter(patient=patient).order_by('-created_at'),
    }
    return render(request, 'dashboards/my_prescriptions.html', ctx)

# --- SYSTEM PROFILE ---
@login_required
def profile_view(request):
    profile = request.user.profile
    role = profile.role
    context = {'profile': profile, 'role': role}
    
    if role == 'Doctor':
        context['doctor_profile'] = get_object_or_404(DoctorProfile, profile=profile)
    elif role == 'Nurse':
        context['nurse_profile'] = get_object_or_404(NurseProfile, profile=profile)
    
    return render(request, 'profile.html', context)


# --- GENERAL CRUD MODULES ---

# Patients
@role_required(['Admin', 'Receptionist', 'Doctor', 'Nurse', 'LabStaff'])
def patient_list(request):
    q = request.GET.get('q', '')
    if q:
        patients = Patient.objects.filter(Q(name__icontains=q) | Q(phone__icontains=q)).distinct()
    else:
        patients = Patient.objects.all().order_by('-created_at')
    
    all_names = Patient.objects.values_list('name', flat=True)
    return render(request, 'patients/list.html', {'patients': patients, 'q': q, 'all_patient_names': all_names})

@role_required(['Admin', 'Receptionist'])
def patient_create(request):
    if request.method == 'POST':
        form = PatientForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, "Patient record created successfully.")
            return redirect('patient_list')
    else:
        form = PatientForm()
    return render(request, 'patients/form.html', {'form': form, 'title': 'Register New Patient'})

@role_required(['Admin', 'Receptionist', 'Doctor', 'Nurse', 'Patient', 'LabStaff'])
def patient_detail(request, pk):
    patient = get_object_or_404(Patient, pk=pk)
    vitals_form = VitalsReadingForm()
    emr_records = EMRRecord.objects.filter(patient=patient).order_by('-created_at')
    vitals = VitalsReading.objects.filter(patient=patient).order_by('-recorded_at')
    return render(request, 'patients/detail.html', {
        'patient': patient,
        'vitals_form': vitals_form,
        'emr_records': emr_records,
        'vitals': vitals
    })

@role_required(['Admin', 'Receptionist'])
def patient_delete(request, pk):
    patient = get_object_or_404(Patient, pk=pk)
    if request.method == 'POST':
        patient.delete()
        messages.success(request, "Patient record removed successfully.")
        return redirect('patient_list')
    return render(request, 'confirm_delete.html', {
        'object_name': f"Patient '{patient.name}'",
        'cancel_url': '/patients/'
    })

# Appointments
@role_required(['Admin', 'Receptionist', 'Doctor', 'Patient'])
def appointment_book(request):
    from datetime import time
    from .models import DoctorProfile

    def get_shift_for_time(t):
        if time(8, 0) <= t < time(16, 0):
            return 'Morning'
        elif time(16, 0) <= t <= time(23, 59, 59):
            return 'Evening'
        else:
            return 'Night'

    if request.method == 'POST':
        form = AppointmentForm(request.POST)
        if form.is_valid():
            appointment = form.save(commit=False)
            
            req_time = appointment.time_slot
            req_shift = get_shift_for_time(req_time)
            dept = form.cleaned_data.get('department')
            
            # Find an available doctor in the department with the required shift
            doctor = DoctorProfile.objects.filter(
                department=dept,
                is_available=True,
                shift=req_shift
            ).first()
            
            if doctor:
                appointment.doctor = doctor
                appointment.save()
                messages.success(request, f"Appointment booked successfully with Dr. {doctor.profile.user.get_full_name() or doctor.profile.user.username}.")
                return redirect('dashboard_redirect')
            else:
                messages.error(request, f"No available doctors in {dept.name} during the {req_shift} shift. Please choose another time.")
    else:
        # Pre-fill patient if user is a patient
        initial = {}
        if hasattr(request.user, 'profile') and request.user.profile.role == 'Patient':
            patient = Patient.objects.filter(profile=request.user.profile).first()
            if patient:
                initial['patient'] = patient
        form = AppointmentForm(initial=initial)
        
    return render(request, 'appointments/book.html', {'form': form})



def signup_view(request):
    from .forms import SignUpForm
    if request.method == 'POST':
        form = SignUpForm(request.POST)
        if form.is_valid():
            # Don't save to DB yet so we can modify is_active
            user = form.save(commit=False)
            role = form.cleaned_data.get('role')
            phone = form.cleaned_data.get('phone')
            staff_id = form.cleaned_data.get('staff_id')
            date_of_birth = form.cleaned_data.get('date_of_birth')
            
            is_verified = True
            if role != 'Patient':
                user.is_active = False # Require admin verification
                is_verified = False
            
            user.save()
            
            # Create user profile
            from .models import UserProfile
            UserProfile.objects.create(user=user, role=role, phone=phone, staff_id=staff_id, is_verified=is_verified, date_of_birth=date_of_birth)
            
            if role == 'Patient':
                messages.success(request, "Account created successfully! You can now log in.")
            else:
                messages.warning(request, "Account created! Please wait for an Administrator to verify your Staff ID before you can log in.")
                
            return redirect('login')
    else:
        form = SignUpForm()
        
    from .models import UserProfile
    from django.db.models import Count
    import json
    
    counts = dict(UserProfile.objects.values_list('role').annotate(count=Count('role')))
    role_counts = {role: counts.get(role, 0) + 1 for role in ['Admin', 'Doctor', 'Nurse', 'Receptionist', 'Pharmacist', 'LabStaff', 'Accountant', 'Patient']}
    
    return render(request, 'authentication/signup.html', {'form': form, 'role_counts': json.dumps(role_counts)})

# Vitals Recording
@role_required(['Admin', 'Nurse', 'Doctor'])
def record_vitals(request, patient_id):
    patient = get_object_or_404(Patient, pk=patient_id)
    if request.method == 'POST':
        form = VitalsReadingForm(request.POST)
        if form.is_valid():
            vital = form.save(commit=False)
            vital.patient = patient
            vital.save()
            if vital.is_critical():
                messages.warning(request, f"Alert: Vitals captured for {patient.name} are CRITICAL! Check immediately.")
            else:
                messages.success(request, "Vitals captured successfully.")
    return redirect('patient_detail', pk=patient_id)

# Room allocations
@role_required(['Admin', 'Receptionist', 'Nurse'])
def manage_rooms(request):
    room_types = ['Emergency Ward', 'General Ward', 'Private', 'ICU']
    selected_type = request.GET.get('room_type', 'All')
    
    if selected_type in room_types:
        rooms = Room.objects.filter(room_type=selected_type).order_by('room_number')
    else:
        rooms = Room.objects.all().order_by('room_number')
    
    # We want to sort the beds of each room according to their category.
    category_order = {
        'Emergency Ward': 0,
        'General Ward': 1,
        'Economy': 2,
        '2 Sharing': 3,
        '3 Sharing': 4,
        '4 Sharing': 5,
        '5 Sharing': 6,
        'Economy Premium': 7,
        'Premium': 8,
        'Standard Private': 9,
        'Deluxe Private': 10,
        'Super Deluxe Private': 11,
        'Suite': 12,
        'ICU': 13,
    }
    
    def get_bed_sort_key(bed):
        try:
            return int(bed.bed_number)
        except ValueError:
            return 9999

    for room in rooms:
        # Prefetch/sort beds in memory for this room to avoid DB complexity
        sorted_beds = sorted(
            room.beds.all(),
            key=get_bed_sort_key
        )
        room.sorted_beds = sorted_beds

    return render(request, 'rooms/manage.html', {
        'rooms': rooms,
        'room_types': room_types,
        'selected_type': selected_type
    })

@role_required(['Admin', 'Receptionist'])
def room_create(request):
    from .forms import RoomForm
    from .models import Bed
    if request.method == 'POST':
        form = RoomForm(request.POST)
        if form.is_valid():
            room = form.save()
            
            # Automatically create the requested number of beds
            num_beds = form.cleaned_data.get('number_of_beds', 0)
            if num_beds > 0:
                # Determine the bed category based on room_type or private_category
                bed_cat = room.private_category if (room.room_type == 'Private' and room.private_category) else room.room_type
                for i in range(1, num_beds + 1):
                    Bed.objects.create(room=room, bed_number=str(i), category=bed_cat)
                    
            messages.success(request, f"Room {room.room_number} created with {num_beds} beds.")
            return redirect('manage_rooms')
    else:
        form = RoomForm()
    return render(request, 'rooms/form.html', {'form': form, 'title': 'Create New Room'})

@role_required(['Admin', 'Receptionist'])
def room_update(request, room_id):
    from .forms import RoomForm
    from .models import Bed
    room = get_object_or_404(Room, pk=room_id)
    current_beds = room.beds.count()
    
    if request.method == 'POST':
        form = RoomForm(request.POST, instance=room)
        if form.is_valid():
            room = form.save()
            new_beds = form.cleaned_data.get('number_of_beds', 0)
            bed_cat = room.private_category if (room.room_type == 'Private' and room.private_category) else room.room_type
            
            # Update category of existing available beds if room type changed
            room.beds.filter(status='Available').update(category=bed_cat)
            
            if new_beds > current_beds:
                # Add beds
                for i in range(current_beds + 1, new_beds + 1):
                    Bed.objects.create(room=room, bed_number=str(i), category=bed_cat)
                messages.success(request, f"Room {room.room_number} updated successfully. {new_beds - current_beds} new beds added.")
            elif new_beds < current_beds:
                # Remove beds if possible
                diff = current_beds - new_beds
                available_beds = list(room.beds.filter(status='Available').order_by('-id'))
                if len(available_beds) >= diff:
                    for b in available_beds[:diff]:
                        b.delete()
                    messages.success(request, f"Room {room.room_number} updated successfully. {diff} beds removed.")
                else:
                    messages.warning(request, f"Room updated, but could not remove {diff} empty beds because they are currently occupied.")
            else:
                messages.success(request, f"Room {room.room_number} updated successfully.")
            return redirect('manage_rooms')
    else:
        form = RoomForm(instance=room, initial={'number_of_beds': current_beds})
    return render(request, 'rooms/form.html', {'form': form, 'title': 'Edit Room Details'})

@role_required(['Admin'])
def manage_pricing(request):
    from django.forms import modelformset_factory
    from .models import RoomPricing
    
    # Ensure all categories exist in the DB
    categories = ['General Ward', 'Standard Private', 'Deluxe Private', 'Super Deluxe Private', 'Suite', 'ICU']
    for cat in categories:
        RoomPricing.objects.get_or_create(category=cat)
        
    PricingFormSet = modelformset_factory(RoomPricing, fields=('daily_charge',), extra=0)
    
    if request.method == 'POST':
        formset = PricingFormSet(request.POST, queryset=RoomPricing.objects.all().order_by('id'))
        if formset.is_valid():
            formset.save()
            messages.success(request, "Room pricing updated successfully.")
            return redirect('manage_rooms')
    else:
        formset = PricingFormSet(queryset=RoomPricing.objects.all().order_by('id'))
        
    return render(request, 'rooms/pricing.html', {'formset': formset})

@role_required(['Admin', 'Receptionist', 'Nurse'])
def allocate_room(request, room_id):
    # This view now displays the beds inside the room, allowing actions on beds
    room = get_object_or_404(Room, pk=room_id)
    return redirect('manage_rooms')

@role_required(['Admin', 'Receptionist'])
def bed_create(request, room_id):
    from .forms import BedForm
    room = get_object_or_404(Room, pk=room_id)
    if request.method == 'POST':
        form = BedForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, f"Bed added to Room {room.room_number}.")
            return redirect('manage_rooms')
    else:
        form = BedForm(initial={'room': room})
    return render(request, 'patients/form.html', {'form': form, 'title': f'Add Bed to Room {room.room_number}'})

@role_required(['Admin', 'Receptionist'])
def bed_update(request, bed_id):
    from .forms import BedForm
    bed = get_object_or_404(Bed, pk=bed_id)
    if request.method == 'POST':
        form = BedForm(request.POST, instance=bed)
        if form.is_valid():
            form.save()
            messages.success(request, f"Bed {bed.bed_number} details updated.")
            return redirect('manage_rooms')
    else:
        form = BedForm(instance=bed)
    return render(request, 'patients/form.html', {'form': form, 'title': f'Edit Bed {bed.bed_number} (Room {bed.room.room_number})'})

@role_required(['Admin', 'Receptionist', 'Nurse'])
def bed_allocate(request, bed_id):
    from .forms import BedAllocationForm
    bed = get_object_or_404(Bed, pk=bed_id)
    if request.method == 'POST':
        form = BedAllocationForm(request.POST, instance=bed)
        if form.is_valid():
            form.save()
            messages.success(request, f"Bed {bed.bed_number} allocation updated.")
            return redirect('manage_rooms')
    else:
        form = BedAllocationForm(instance=bed)
    return render(request, 'rooms/allocate.html', {'form': form, 'room': bed.room, 'bed': bed})

@role_required(['Admin', 'Receptionist'])
def bed_delete(request, bed_id):
    bed = get_object_or_404(Bed, pk=bed_id)
    if request.method == 'POST':
        bed.delete()
        messages.success(request, f"Bed {bed.bed_number} removed successfully.")
        return redirect('manage_rooms')
    return render(request, 'confirm_delete.html', {
        'object_name': f"Bed {bed.bed_number} in Room {bed.room.room_number}",
        'cancel_url': '/rooms/'
    })

@role_required(['Admin', 'Receptionist'])
def room_delete(request, room_id):
    room = get_object_or_404(Room, pk=room_id)
    if request.method == 'POST':
        room.delete()
        messages.success(request, f"Room {room.room_number} removed successfully.")
        return redirect('manage_rooms')
    return render(request, 'confirm_delete.html', {
        'object_name': f"Room {room.room_number}",
        'cancel_url': '/rooms/'
    })

# Ventilation sessions
@role_required(['Admin', 'Doctor', 'Nurse'])
def ventilator_sessions(request):
    sessions = VentilatorSession.objects.all().order_by('-start_time')
    return render(request, 'ventilators/list.html', {'sessions': sessions})

@role_required(['Admin', 'Doctor', 'Nurse'])
def ventilator_create(request):
    if request.method == 'POST':
        patient_id = request.POST.get('patient')
        ventilator_id = request.POST.get('ventilator')
        mode = request.POST.get('mode')
        patient = get_object_or_404(Patient, pk=patient_id)
        ventilator = get_object_or_404(Ventilator, pk=ventilator_id)
        
        session = VentilatorSession.objects.create(
            patient=patient,
            ventilator=ventilator,
            mode=mode,
            is_active=True
        )
        ventilator.status = 'Assigned'
        ventilator.save()
        messages.success(request, "Ventilator session started.")
        return redirect('ventilator_sessions')
    
    patients = Patient.objects.all()
    ventilators = Ventilator.objects.filter(status='Available')
    return render(request, 'ventilators/create.html', {'patients': patients, 'ventilators': ventilators})

@role_required(['Admin', 'Doctor', 'Nurse'])
def ventilator_detail(request, pk):
    session = get_object_or_404(VentilatorSession, pk=pk)
    if request.method == 'POST':
        form = VentilatorSessionForm(request.POST, instance=session)
        if form.is_valid():
            session = form.save(commit=False)
            
            # If the ventilator is being disconnected, mark session as inactive and free the machine
            if not session.connected and session.is_active:
                from django.utils import timezone
                session.is_active = False
                session.end_time = timezone.now()
                session.ventilator.status = 'Available'
                session.ventilator.save()
            
            session.save()
            
            status = session.check_status()
            if "Alert" in status:
                messages.warning(request, status)
            else:
                messages.success(request, "Ventilator telemetry parameters updated.")
            return redirect('ventilator_detail', pk=pk)
    else:
        form = VentilatorSessionForm(instance=session)
    return render(request, 'ventilators/detail.html', {'session': session, 'form': form})

# Billing Invoices
@role_required(['Admin', 'Accountant', 'Receptionist'])
def billing_list(request):
    bills = Bill.objects.all().order_by('-created_at')
    grand_total = sum(b.get_total() for b in bills)
    return render(request, 'billing/list.html', {'bills': bills, 'grand_total': grand_total})

@role_required(['Admin', 'Accountant', 'Receptionist'])
def billing_create(request):
    from .forms import BillForm
    if request.method == 'POST':
        form = BillForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, "Invoice generated successfully.")
            return redirect('billing_list')
    else:
        form = BillForm()
    return render(request, 'billing/form.html', {'form': form})

from django.http import JsonResponse
from .models import Appointment, LabTest, Bed

@role_required(['Admin', 'Accountant', 'Receptionist'])
def get_patient_billing_data(request, patient_id):
    # 1. Consultant Fees ($150 per Appointment)
    appointments_count = Appointment.objects.filter(patient_id=patient_id).count()
    consultation_fee = appointments_count * 150.0

    # 2. Room Charges
    room_charges = 0.0
    bed = Bed.objects.filter(patient_id=patient_id, status='Occupied').first()
    if bed:
        room_charges = float(bed.room.charges)

    # 3. Lab Charges ($100 per Lab Test)
    lab_tests_count = LabTest.objects.filter(patient_id=patient_id).count()
    lab_charges = lab_tests_count * 100.0

    # 4. Medicine Charges (Leave 0 for manual entry)
    medicine_charges = 0.0

    return JsonResponse({
        'consultation_fee': consultation_fee,
        'room_charges': room_charges,
        'medicine_charges': medicine_charges,
        'lab_charges': lab_charges,
    })

# Inventory Stock
@role_required(['Admin', 'Pharmacist'])
def inventory_list(request):
    items = InventoryItem.objects.all()
    return render(request, 'inventory/list.html', {'items': items})

@role_required(['Admin', 'Pharmacist'])
def inventory_create(request):
    if request.method == 'POST':
        form = InventoryItemForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, "Inventory stock item created.")
            return redirect('inventory_list')
    else:
        form = InventoryItemForm()
    return render(request, 'inventory/form.html', {'form': form, 'title': 'Add New Inventory Stock Item'})

@role_required(['Admin', 'Pharmacist'])
def inventory_update(request, pk):
    item = get_object_or_404(InventoryItem, pk=pk)
    if request.method == 'POST':
        form = InventoryItemForm(request.POST, instance=item)
        if form.is_valid():
            form.save()
            messages.success(request, "Inventory stock level updated.")
            return redirect('inventory_list')
    else:
        form = InventoryItemForm(instance=item)
    return render(request, 'inventory/form.html', {'form': form, 'item': item, 'title': f'Update {item.item_name}'})

@role_required(['Admin', 'Pharmacist'])
def inventory_delete(request, pk):
    item = get_object_or_404(InventoryItem, pk=pk)
    if request.method == 'POST':
        item.delete()
        messages.success(request, "Stock item removed successfully.")
        return redirect('inventory_list')
    return render(request, 'confirm_delete.html', {
        'object_name': f"Inventory Item '{item.item_name}'",
        'cancel_url': '/inventory/'
    })

# Laboratory Tests
@role_required(['Admin', 'LabStaff', 'Doctor'])
def lab_test_update(request, pk):
    test = get_object_or_404(LabTest, pk=pk)
    if request.method == 'POST':
        form = LabTestForm(request.POST, instance=test)
        if form.is_valid():
            form.save()
            messages.success(request, f"Lab test results for {test.patient.name} updated.")
            return redirect('dashboard_redirect')
    else:
        form = LabTestForm(instance=test)
    return render(request, 'laboratory/form.html', {'form': form, 'test': test})

@role_required(['Admin', 'LabStaff', 'Doctor'])
def lab_test_create(request, patient_id=None):
    initial_data = {}
    if patient_id:
        patient = get_object_or_404(Patient, pk=patient_id)
        initial_data['patient'] = patient
    
    if request.method == 'POST':
        form = LabTestForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, "New lab test result deployed successfully.")
            return redirect('dashboard_redirect')
    else:
        form = LabTestForm(initial=initial_data)
    
    return render(request, 'laboratory/form.html', {'form': form, 'title': 'Deploy Test Result'})

# Punch attendance system
@role_required(['Admin', 'Doctor', 'Nurse', 'Receptionist', 'Pharmacist', 'LabStaff', 'Accountant'])
def punch_attendance(request):
    record = Attendance.objects.filter(user=request.user, punch_out__isnull=True).first()
    
    if request.method == 'POST':
        action = request.POST.get('action')
        if action == 'in':
            if not record:
                from django.utils import timezone
                Attendance.objects.create(user=request.user, punch_in=timezone.now())
                messages.success(request, "Successfully punched IN.")
            else:
                messages.warning(request, "You are already punched in.")
        elif action == 'out':
            if record:
                from django.utils import timezone
                record.punch_out = timezone.now()
                record.calculate_hours()
                messages.success(request, f"Successfully punched OUT. Total duration: {record.working_hours} hours.")
            else:
                messages.warning(request, "You do not have a running punch session.")
        return redirect('dashboard_redirect')
    
    is_admin = request.user.profile.role == 'Admin'
    if is_admin:
        all_records = Attendance.objects.all().order_by('-punch_in')
    else:
        all_records = Attendance.objects.filter(user=request.user).order_by('-punch_in')
    
    return render(request, 'attendance.html', {'current_punch': record, 'records': all_records, 'is_admin': is_admin})

# Emergency Protocol Triggering
@role_required(['Admin', 'Doctor', 'Nurse', 'Receptionist'])
def trigger_emergency(request):
    if request.method == 'POST':
        spec = request.POST.get('specialization', '')
        details = request.POST.get('details', '')
        alert = EmergencyAlert.objects.create(specialization_required=spec, details=details)
        docs = alert.get_notified_doctors()
        messages.success(request, f"Code Blue Emergency triggered! {docs.count()} doctor(s) on-call alerted.")
        return redirect('dashboard_redirect')
    return render(request, 'emergency.html')

# Ambulance dispatch
@role_required(['Admin', 'Receptionist'])
def ambulance_dispatch(request):
    ambulances = Ambulance.objects.all()
    if request.method == 'POST':
        amb_id = request.POST.get('ambulance_id')
        dest = request.POST.get('destination')
        amb = get_object_or_404(Ambulance, pk=amb_id)
        if amb.assign(dest):
            messages.success(request, f"Ambulance {amb.ambulance_number} dispatched to {dest}.")
        else:
            messages.error(request, "Ambulance is not available.")
        return redirect('ambulance_dispatch')
    return render(request, 'ambulances.html', {'ambulances': ambulances})

@role_required(['Admin', 'Receptionist'])
def ambulance_create(request):
    if request.method == 'POST':
        form = AmbulanceForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, "New Ambulance added to fleet radar.")
            return redirect('ambulance_dispatch')
    else:
        form = AmbulanceForm()
    return render(request, 'patients/form.html', {'form': form, 'title': 'Register New Fleet Ambulance'})

@role_required(['Admin'])
def ambulance_delete(request, amb_id):
    amb = get_object_or_404(Ambulance, pk=amb_id)
    if request.method == 'POST':
        num = amb.ambulance_number
        amb.delete()
        messages.success(request, f"Ambulance {num} removed from fleet radar.")
        return redirect('ambulance_dispatch')
    return render(request, 'confirm_delete.html', {
        'object_name': f"Ambulance {amb.ambulance_number} (Driver: {amb.driver_name})",
        'cancel_url': '/ambulances/'
    })

# Admin Verification Module
@role_required(['Admin'])
def pending_requests(request):
    from .models import UserProfile, ROLE_CHOICES
    
    # Exclude 'Patient' from the filter choices since they don't pend verification
    staff_roles = [r[0] for r in ROLE_CHOICES if r[0] != 'Patient']
    
    selected_role = request.GET.get('role', 'All')
    
    if selected_role in staff_roles:
        pending = UserProfile.objects.filter(is_verified=False, role=selected_role).order_by('-user__date_joined')
    else:
        pending = UserProfile.objects.filter(is_verified=False).order_by('-user__date_joined')
        
    return render(request, 'dashboards/pending_requests.html', {
        'pending': pending,
        'staff_roles': staff_roles,
        'selected_role': selected_role
    })

@role_required(['Admin'])
def approve_staff(request, profile_id):
    from .models import UserProfile, StaffVerificationLog
    profile = get_object_or_404(UserProfile, pk=profile_id)
    if request.method == 'POST':
        profile.is_verified = True
        profile.save()
        profile.user.is_active = True
        profile.user.save()
        
        # Log the verification
        StaffVerificationLog.objects.create(
            user_profile=profile,
            approved_by=request.user,
            notes=f"Approved automatically via Admin Dashboard by {request.user.username}"
        )
        
        messages.success(request, f"Account for {profile.user.username} (ID: {profile.staff_id}) has been approved and activated.")
    return redirect('pending_requests')

@role_required(['Admin'])
def reject_staff(request, profile_id):
    from .models import UserProfile
    profile = get_object_or_404(UserProfile, pk=profile_id)
    if request.method == 'POST':
        username = profile.user.username
        staff_id = profile.staff_id
        
        # Completely remove the rejected registration
        user = profile.user
        user.delete()
        
        messages.success(request, f"Registration request for {username} (ID: {staff_id}) has been declined and the pending account removed.")
    return redirect('pending_requests')
