from django.core.management.base import BaseCommand
from django.contrib.auth.models import User, Group
from hms_app.models import UserProfile, Department, DoctorProfile, NurseProfile, Patient, Room, Ventilator, InventoryItem, Ambulance
import datetime

class Command(BaseCommand):
    help = "Seeds database with groups, roles, and dummy credentials for hospital management development."

    def handle(self, *args, **options):
        self.stdout.write("Seeding roles and user groups...")

        roles = ['Admin', 'Doctor', 'Nurse', 'Receptionist', 'Pharmacist', 'LabStaff', 'Accountant', 'Patient']
        groups = {}
        for role in roles:
            group, created = Group.objects.get_or_str(name=role) if hasattr(Group.objects, 'get_or_str') else Group.objects.get_or_create(name=role)
            groups[role] = group

        # Seed Departments
        depts_data = [
            {"name": "Cardiology", "location": "Wing A, 2nd Floor", "head": "Dr. John Watson", "docs": 5, "beds": 10},
            {"name": "Neurology", "location": "Wing B, 3rd Floor", "head": "Dr. Sarah Jenkins", "docs": 4, "beds": 8},
            {"name": "Emergency", "location": "Ground Floor, Entrance", "head": "Dr. House", "docs": 10, "beds": 20},
            {"name": "Pediatrics", "location": "Wing C, 1st Floor", "head": "Dr. Lisa Cuddy", "docs": 6, "beds": 12},
        ]
        depts = {}
        for d in depts_data:
            dept, created = Department.objects.get_or_create(
                name=d["name"],
                defaults={
                    "location": d["location"],
                    "head_doctor": d["head"],
                    "number_of_doctors": d["docs"],
                    "number_of_beds": d["beds"]
                }
            )
            depts[d["name"]] = dept

        # Helper to create user & profile
        def create_user_profile(username, password, first_name, last_name, role, phone="123-456-7890"):
            user, created = User.objects.get_or_create(
                username=username,
                defaults={
                    "first_name": first_name,
                    "last_name": last_name,
                    "email": f"{username}@hospital.com"
                }
            )
            if created:
                user.set_password(password)
                user.save()
            user.groups.add(groups[role])
            
            profile, p_created = UserProfile.objects.get_or_create(
                user=user,
                defaults={"role": role, "phone": phone}
            )
            return profile

        self.stdout.write("Creating demo accounts...")
        # 1. Admin
        create_user_profile("admin", "sayan", "System", "Admin", "Admin")

        # 2. Doctor
        doc_prof = create_user_profile("doctor", "sayan", "John", "Watson", "Doctor")
        DoctorProfile.objects.get_or_create(
            profile=doc_prof,
            defaults={
                "specialization": "Cardiology",
                "qualification": "MD, FACC",
                "department": depts["Cardiology"],
                "is_available": True
            }
        )

        # 3. Nurse
        nurse_prof = create_user_profile("nurse", "sayan", "Clara", "Barton", "Nurse")
        NurseProfile.objects.get_or_create(
            profile=nurse_prof,
            defaults={
                "qualification": "BSN, RN",
                "department": depts["Emergency"]
            }
        )

        # 4. Receptionist
        create_user_profile("receptionist", "sayan", "Pam", "Beesly", "Receptionist")

        # 5. Pharmacist
        create_user_profile("pharmacist", "sayan", "Gregory", "House", "Pharmacist")

        # 6. Lab Staff
        create_user_profile("labstaff", "sayan", "Sherlock", "Holmes", "LabStaff")

        # 7. Accountant
        create_user_profile("accountant", "sayan", "Oscar", "Martinez", "Accountant")

        # 8. Patient
        patient_prof = create_user_profile("patient", "sayan", "Bob", "Smith", "Patient")
        Patient.objects.get_or_create(
            profile=patient_prof,
            defaults={
                "name": "Bob Smith",
                "age": 45,
                "gender": "Male",
                "phone": "555-0199",
                "email": "bob.smith@gmail.com",
                "medical_history": "Hypertension diagnosed 2024\nNo known allergies"
            }
        )

        # Create general patients
        Patient.objects.get_or_create(
            name="Alice Cooper",
            defaults={
                "age": 30,
                "gender": "Female",
                "phone": "555-9876",
                "email": "alice@cooper.com",
                "medical_history": "Asthma"
            }
        )

        # Create Rooms
        for num in [101, 102, 103, 201, 202, 301]:
            room_type = 'ICU' if num >= 300 else ('Private' if num >= 200 else 'General')
            charges = 5000.00 if room_type == 'ICU' else (2500.00 if room_type == 'Private' else 1000.00)
            Room.objects.get_or_create(
                room_number=num,
                defaults={
                    "room_type": room_type,
                    "charges": charges,
                    "status": "Available"
                }
            )

        # Create Ventilators
        for v_id in ["VENT-01", "VENT-02", "VENT-03"]:
            Ventilator.objects.get_or_create(device_id=v_id)

        # Create Ambulances
        Ambulance.objects.get_or_create(
            ambulance_number="AMB-999",
            defaults={
                "driver_name": "Roy DeSoto",
                "driver_contact": "555-9111",
                "current_location": "Main Entrance",
                "latitude": 40.7128,
                "longitude": -74.0060,
                "status": "Available"
            }
        )

        # Create InventoryItems
        items = [
            {"name": "Paracetamol 500mg", "cat": "Analgesics", "qty": 100, "min": 20, "price": 5.00},
            {"name": "Amoxicillin 250mg", "cat": "Antibiotics", "qty": 15, "min": 25, "price": 12.50},
            {"name": "Insulin Glargine", "cat": "Antidiabetics", "qty": 8, "min": 10, "price": 45.00},
        ]
        for it in items:
            InventoryItem.objects.get_or_create(
                item_name=it["name"],
                defaults={
                    "category": it["cat"],
                    "quantity": it["qty"],
                    "minimum_stock": it["min"],
                    "price": it["price"],
                    "supplier_name": "PharmaCorp Industries",
                    "supplier_contact": "1-800-PHARMA",
                    "batch_number": "BATCH-XYZ",
                    "manufacturing_date": datetime.date(2025, 1, 1),
                    "expiry_date": datetime.date(2027, 1, 1),
                    "storage_location": "Cabinet A, Shelf 2"
                }
            )

        self.stdout.write(self.style.SUCCESS("Database seeded successfully with roles and sample data!"))
