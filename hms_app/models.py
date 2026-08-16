from django.db import models
from django.contrib.auth.models import User
from django.core.exceptions import ValidationError

# Roles defined in instructions
ROLE_CHOICES = (
    ('Admin', 'Administrator'),
    ('Doctor', 'Doctor'),
    ('Nurse', 'Nurse'),
    ('Receptionist', 'Receptionist'),
    ('Pharmacist', 'Pharmacist'),
    ('LabStaff', 'Laboratory Staff'),
    ('Accountant', 'Accountant'),
    ('Patient', 'Patient'),
)

class UserProfile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='profile')
    role = models.CharField(max_length=20, choices=ROLE_CHOICES)
    phone = models.CharField(max_length=20, blank=True, null=True)
    staff_id = models.CharField(max_length=50, blank=True, null=True, help_text="Required for all staff roles")
    is_verified = models.BooleanField(default=False)
    date_of_birth = models.DateField(blank=True, null=True)

    def __str__(self):
        return f"{self.user.username} ({self.role})"

    @property
    def age(self):
        from datetime import date
        if self.date_of_birth:
            today = date.today()
            return today.year - self.date_of_birth.year - ((today.month, today.day) < (self.date_of_birth.month, self.date_of_birth.day))
        return None


class Department(models.Model):
    name = models.CharField(max_length=100, unique=True)
    location = models.CharField(max_length=150)
    head_doctor = models.CharField(max_length=100, blank=True, null=True)
    number_of_doctors = models.PositiveIntegerField(default=0)
    number_of_beds = models.PositiveIntegerField(default=0)

    def __str__(self):
        return self.name


class DoctorProfile(models.Model):
    profile = models.OneToOneField(UserProfile, on_delete=models.CASCADE, limit_choices_to={'role': 'Doctor'})
    specialization = models.CharField(max_length=100)
    qualification = models.CharField(max_length=100)
    department = models.ForeignKey(Department, on_delete=models.SET_NULL, null=True, blank=True)
    is_available = models.BooleanField(default=True)
    shift = models.CharField(max_length=20, default='Morning', choices=(
        ('Morning', 'Morning (08:00 - 16:00)'),
        ('Evening', 'Evening (16:00 - 00:00)'),
        ('Night', 'Night (00:00 - 08:00)')
    ))

    def __str__(self):
        return f"Dr. {self.profile.user.first_name or self.profile.user.username} - {self.specialization}"


class NurseProfile(models.Model):
    profile = models.OneToOneField(UserProfile, on_delete=models.CASCADE, limit_choices_to={'role': 'Nurse'})
    qualification = models.CharField(max_length=100)
    department = models.ForeignKey(Department, on_delete=models.SET_NULL, null=True, blank=True)

    def __str__(self):
        return f"Nurse {self.profile.user.first_name or self.profile.user.username}"


class Patient(models.Model):
    profile = models.OneToOneField(UserProfile, on_delete=models.CASCADE, limit_choices_to={'role': 'Patient'}, null=True, blank=True)
    name = models.CharField(max_length=100)
    age = models.PositiveIntegerField()
    gender = models.CharField(max_length=10, choices=(('Male', 'Male'), ('Female', 'Female'), ('Other', 'Other')))
    phone = models.CharField(max_length=20)
    email = models.EmailField(blank=True, null=True)
    medical_history = models.TextField(blank=True, null=True, help_text="Separated by newlines")
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.name} (Age: {self.age})"


class VitalsReading(models.Model):
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE, related_name='vitals')
    heart_rate = models.IntegerField(help_text="BPM")
    systolic_bp = models.IntegerField(help_text="mmHg")
    diastolic_bp = models.IntegerField(help_text="mmHg")
    temperature = models.FloatField(help_text="°F")
    oxygen_level = models.IntegerField(help_text="SpO2 %")
    recorded_at = models.DateTimeField(auto_now_add=True)

    def is_critical(self):
        # Ported from HealthMonitoring.cpp
        # Heart rate: < 50 or > 130 BPM
        # Systolic BP: > 160 or < 90 mmHg
        # Oxygen SpO2: < 92%
        # Temperature: > 103.0°F or < 95.0°F
        if (self.heart_rate < 50 or self.heart_rate > 130 or
            self.systolic_bp > 160 or self.systolic_bp < 90 or
            self.oxygen_level < 92 or
            self.temperature > 103.0 or self.temperature < 95.0):
            return True
        return False

    def critical_factors(self):
        factors = []
        if self.heart_rate < 50 or self.heart_rate > 130:
            factors.append(f"Heart Rate: {self.heart_rate} BPM")
        if self.systolic_bp > 160 or self.systolic_bp < 90:
            factors.append(f"Systolic BP: {self.systolic_bp} mmHg")
        if self.oxygen_level < 92:
            factors.append(f"Oxygen: {self.oxygen_level}%")
        if self.temperature > 103.0 or self.temperature < 95.0:
            factors.append(f"Temp: {self.temperature}°F")
        return ", ".join(factors)

    def __str__(self):
        status = "CRITICAL" if self.is_critical() else "Stable"
        return f"Vitals for {self.patient.name} at {self.recorded_at.strftime('%Y-%m-%d %H:%M')} - {status}"


class EMRRecord(models.Model):
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE, related_name='emr_records')
    doctor = models.ForeignKey(DoctorProfile, on_delete=models.SET_NULL, null=True)
    diagnosis = models.TextField()
    treatment = models.TextField()
    prescriptions = models.TextField(blank=True, null=True, help_text="List medicines details")
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"EMR entry for {self.patient.name} by {self.doctor}"


class Ventilator(models.Model):
    device_id = models.CharField(max_length=50, unique=True)
    model_name = models.CharField(max_length=100, default="VentiFlow-2000")
    status = models.CharField(max_length=20, default="Available", choices=(
        ('Available', 'Available'),
        ('Assigned', 'Assigned'),
        ('Maintenance', 'Maintenance')
    ))

    def __str__(self):
        return f"Ventilator {self.device_id} ({self.status})"


class VentilatorSession(models.Model):
    # Ported from DigitalVentilation.cpp
    ventilator = models.ForeignKey(Ventilator, on_delete=models.CASCADE)
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    mode = models.CharField(max_length=20, choices=(('CMV', 'CMV'), ('SIMV', 'SIMV'), ('CPAP', 'CPAP')))
    start_time = models.DateTimeField(auto_now_add=True)
    end_time = models.DateTimeField(null=True, blank=True)
    is_active = models.BooleanField(default=True)

    oxygen_level = models.FloatField(default=40.0, help_text="FiO2 % (21.0 - 100.0)")
    respiratory_rate = models.FloatField(default=14.0, help_text="BPM")
    tidal_volume = models.FloatField(default=500.0, help_text="mL")
    peep = models.FloatField(default=5.0, help_text="cmH2O")
    peak_pressure = models.FloatField(default=20.0, help_text="cmH2O")
    plateau_pressure = models.FloatField(default=15.0, help_text="cmH2O")
    connected = models.BooleanField(default=True)

    def check_status(self):
        # Ventilation verification checks from DigitalVentilation.cpp
        warnings = []
        if not self.connected:
            return "Alert: Ventilator disconnected"
        if not (21.0 <= self.oxygen_level <= 100.0):
            warnings.append("Oxygen Level out of range (21%-100%)")
        if self.respiratory_rate <= 0:
            warnings.append("Respiratory rate must be positive")
        if self.tidal_volume <= 0:
            warnings.append("Tidal Volume must be positive")
        if self.plateau_pressure > self.peak_pressure:
            warnings.append("Plateau pressure exceeds Peak pressure")
        
        if warnings:
            return "Alert: " + "; ".join(warnings)
        return "Stable"

    def __str__(self):
        return f"Ventilator Session {self.ventilator.device_id} -> {self.patient.name}"


class RiskAssessment(models.Model):
    # Ported from RateofRisk.cpp
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    disease = models.CharField(max_length=150)
    risk_level = models.IntegerField(choices=((1, 'Very Low Risk'), (2, 'Low Risk'), (3, 'Medium Condition'), (4, 'High Risk'), (5, 'Critical Condition')))
    risk_score = models.IntegerField()
    notes = models.TextField(blank=True, null=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def get_risk_level_string(self):
        mapping = {
            1: "Very Low Risk",
            2: "Low Risk",
            3: "Medium Condition",
            4: "High Risk",
            5: "Critical Condition",
        }
        return mapping.get(self.risk_level, "Unknown")

    def __str__(self):
        return f"{self.patient.name} - {self.disease} (Risk: {self.get_risk_level_string()})"


class RoomPricing(models.Model):
    category = models.CharField(max_length=50, unique=True, choices=(
        ('Emergency Ward', 'Emergency Ward'),
        ('General Ward', 'General Ward'),
        ('Standard Private', 'Standard Private'), 
        ('Deluxe Private', 'Deluxe Private'), 
        ('Super Deluxe Private', 'Super Deluxe Private'), 
        ('Suite', 'Suite'),
        ('ICU', 'ICU')
    ))
    daily_charge = models.DecimalField(max_digits=10, decimal_places=2, default=0.00)

    def __str__(self):
        return f"{self.category} - ${self.daily_charge}"


class Room(models.Model):
    room_number = models.IntegerField(unique=True)
    room_type = models.CharField(max_length=50, choices=(('Emergency Ward', 'Emergency Ward'), ('General Ward', 'General Ward'), ('Private', 'Private'), ('ICU', 'ICU')))
    private_category = models.CharField(max_length=50, blank=True, null=True, choices=(
        ('Standard Private', 'Standard Private'), 
        ('Deluxe Private', 'Deluxe Private'), 
        ('Super Deluxe Private', 'Super Deluxe Private'), 
        ('Suite', 'Suite')
    ), help_text="Required if Room Type is Private.")
    status = models.CharField(max_length=20, default='Available', choices=(
        ('Available', 'Available'),
        ('Maintenance', 'Maintenance')
    ))

    @property
    def category_name(self):
        return self.private_category if self.room_type == 'Private' and self.private_category else self.room_type

    @property
    def charges(self):
        try:
            pricing = RoomPricing.objects.get(category=self.category_name)
            return pricing.daily_charge
        except RoomPricing.DoesNotExist:
            return 0.00

    def __str__(self):
        return f"Room {self.room_number} [{self.room_type}]"


class Bed(models.Model):
    BED_CATEGORIES = (
        ('General Ward', 'General Ward'),
        ('Economy', 'Economy'),
        ('2 Sharing', '2 Sharing'),
        ('3 Sharing', '3 Sharing'),
        ('4 Sharing', '4 Sharing'),
        ('5 Sharing', '5 Sharing'),
        ('Economy Premium', 'Economy Premium'),
        ('Premium', 'Premium'),
        ('Standard Private', 'Standard Private'), 
        ('Deluxe Private', 'Deluxe Private'), 
        ('Super Deluxe Private', 'Super Deluxe Private'), 
        ('Suite', 'Suite'),
        ('ICU', 'ICU')
    )

    room = models.ForeignKey(Room, on_delete=models.CASCADE, related_name='beds')
    bed_number = models.CharField(max_length=10)
    category = models.CharField(max_length=30, choices=BED_CATEGORIES, default='General')
    status = models.CharField(max_length=20, default='Available', choices=(
        ('Available', 'Available'),
        ('Occupied', 'Occupied'),
        ('Maintenance', 'Maintenance')
    ))
    patient = models.ForeignKey(Patient, on_delete=models.SET_NULL, null=True, blank=True)
    medical_case = models.TextField(blank=True, null=True, help_text="Reason for admission / current case")

    class Meta:
        unique_together = ('room', 'bed_number')

    def save(self, *args, **kwargs):
        """Automatically update status based on patient assignment.
        If a patient is linked, the bed becomes 'Occupied'.
        If the patient is cleared, revert to 'Available' unless explicitly set otherwise.
        """
        if self.patient:
            self.status = 'Occupied'
        else:
            # When unassigned, default to Available if it was previously Occupied
            if self.status == 'Occupied':
                self.status = 'Available'
            self.medical_case = None  # Clear case when patient is discharged
        super().save(*args, **kwargs)

    def __str__(self):
        return f"Room {self.room.room_number} - Bed {self.bed_number} [{self.category}] ({self.status})"


class Appointment(models.Model):
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE, related_name='appointments')
    doctor = models.ForeignKey(DoctorProfile, on_delete=models.CASCADE, related_name='appointments')
    date = models.DateField()
    time_slot = models.TimeField()
    status = models.CharField(max_length=20, default='Pending', choices=(
        ('Pending', 'Pending'),
        ('Confirmed', 'Confirmed'),
        ('Checked In', 'Checked In'),
        ('Completed', 'Completed'),
        ('Cancelled', 'Cancelled'),
        ('No Show', 'No Show'),
    ))
    reason = models.CharField(max_length=255, blank=True, null=True)

    class Meta:
        unique_together = ('doctor', 'date', 'time_slot')

    def __str__(self):
        return f"{self.patient.name} with {self.doctor} at {self.date} {self.time_slot}"


class EmergencyAlert(models.Model):
    # Ported from EmergencyProtocol.cpp
    specialization_required = models.CharField(max_length=100)
    details = models.TextField()
    is_active = models.BooleanField(default=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def get_notified_doctors(self):
        if self.specialization_required.lower() == 'general' or not self.specialization_required:
            return DoctorProfile.objects.filter(is_available=True)
        return DoctorProfile.objects.filter(specialization__icontains=self.specialization_required, is_available=True)

    def __str__(self):
        return f"EMERGENCY [{self.specialization_required}]: {self.details[:30]}"


class Ambulance(models.Model):
    # Ported from AmbulanceRadar.cpp
    ambulance_number = models.CharField(max_length=50, unique=True)
    driver_name = models.CharField(max_length=100)
    driver_contact = models.CharField(max_length=20)
    current_location = models.CharField(max_length=255)
    destination = models.CharField(max_length=255, blank=True, null=True)
    latitude = models.FloatField(default=0.0)
    longitude = models.FloatField(default=0.0)
    status = models.CharField(max_length=20, default='Available', choices=(
        ('Available', 'Available'),
        ('Assigned', 'Assigned'),
        ('Maintenance', 'Maintenance')
    ))
    patient_count = models.PositiveIntegerField(default=0)

    def assign(self, dest):
        if self.status == 'Available':
            self.status = 'Assigned'
            self.destination = dest
            self.patient_count += 1
            self.save()
            return True
        return False

    def release(self):
        self.status = 'Available'
        self.destination = None
        self.save()

    def __str__(self):
        return f"Ambulance {self.ambulance_number} ({self.status})"


class InventoryItem(models.Model):
    # Ported from InventorySystem.cpp
    item_name = models.CharField(max_length=100)
    category = models.CharField(max_length=50)
    quantity = models.IntegerField(default=0)
    minimum_stock = models.IntegerField(default=10)
    price = models.DecimalField(max_digits=10, decimal_places=2)
    supplier_name = models.CharField(max_length=100)
    supplier_contact = models.CharField(max_length=20)
    batch_number = models.CharField(max_length=50)
    manufacturing_date = models.DateField()
    expiry_date = models.DateField()
    storage_location = models.CharField(max_length=100)

    def is_low_stock(self):
        return self.quantity <= self.minimum_stock

    def is_out_of_stock(self):
        return self.quantity <= 0

    def __str__(self):
        return f"{self.item_name} (Stock: {self.quantity})"


class MortuaryRecord(models.Model):
    # Ported from MortuaryManagement.cpp
    deceased_name = models.CharField(max_length=100)
    age = models.PositiveIntegerField()
    gender = models.CharField(max_length=10, choices=(('Male', 'Male'), ('Female', 'Female'), ('Other', 'Other')))
    date_of_admission = models.DateField()
    date_of_death = models.DateField()
    cause_of_death = models.CharField(max_length=255)
    identification_status = models.CharField(max_length=20, default='Not Identified', choices=(
        ('Not Identified', 'Not Identified'),
        ('Identified', 'Identified')
    ))
    release_status = models.CharField(max_length=20, default='Not Released', choices=(
        ('Not Released', 'Not Released'),
        ('Released', 'Released')
    ))

    def clean(self):
        if self.release_status == 'Released' and self.identification_status != 'Identified':
            raise ValidationError("A body can only be released if identification status is 'Identified'.")

    def save(self, *args, **kwargs):
        self.full_clean()
        super().save(*args, **kwargs)

    def __str__(self):
        return f"Mortuary Record: {self.deceased_name} - {self.release_status}"


class Attendance(models.Model):
    # Ported from PunchSystem.cpp
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    punch_in = models.DateTimeField()
    punch_out = models.DateTimeField(null=True, blank=True)
    working_hours = models.FloatField(default=0.0)

    def calculate_hours(self):
        if self.punch_in and self.punch_out:
            delta = self.punch_out - self.punch_in
            self.working_hours = round(delta.total_seconds() / 3600.0, 2)
            self.save()

    def __str__(self):
        return f"Attendance: {self.user.username} at {self.punch_in.strftime('%Y-%m-%d')}"


class LabTest(models.Model):
    # Ported from laboratory references
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    test_name = models.CharField(max_length=100)
    requested_by = models.ForeignKey(DoctorProfile, on_delete=models.SET_NULL, null=True)
    status = models.CharField(max_length=20, default='Pending', choices=(
        ('Pending', 'Pending'),
        ('Sample Collected', 'Sample Collected'),
        ('Processing', 'Processing'),
        ('Completed', 'Completed')
    ))
    result_details = models.TextField(blank=True, null=True)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)

    def __str__(self):
        return f"{self.test_name} for {self.patient.name}"


class Bill(models.Model):
    # Ported from billing references
    patient = models.ForeignKey(Patient, on_delete=models.CASCADE)
    consultation_fee = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    room_charges = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    medicine_charges = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    lab_charges = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    other_charges = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    discount = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    tax = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    status = models.CharField(max_length=20, default='Pending', choices=(
        ('Pending', 'Pending'),
        ('Partially Paid', 'Partially Paid'),
        ('Paid', 'Paid'),
        ('Cancelled', 'Cancelled')
    ))
    created_at = models.DateTimeField(auto_now_add=True)

    def get_total(self):
        from decimal import Decimal
        subtotal = (self.consultation_fee + self.room_charges + 
                    self.medicine_charges + self.lab_charges + self.other_charges)
        discount_amount = subtotal * (self.discount / Decimal('100.0'))
        subtotal = subtotal - discount_amount
        tax_amount = subtotal * Decimal('0.18')
        return subtotal + tax_amount

    def __str__(self):
        return f"Bill for {self.patient.name} - Total: {self.get_total()}"


class Notification(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    message = models.TextField()
    is_read = models.BooleanField(default=False)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"Notification for {self.user.username}: {self.message[:30]}"

class StaffVerificationLog(models.Model):
    user_profile = models.ForeignKey(UserProfile, on_delete=models.CASCADE, related_name='verification_logs')
    approved_by = models.ForeignKey(User, on_delete=models.SET_NULL, null=True)
    approved_at = models.DateTimeField(auto_now_add=True)
    notes = models.TextField(blank=True, null=True)

    def __str__(self):
        return f"Approved {self.user_profile.user.username} by {self.approved_by.username} at {self.approved_at}"
