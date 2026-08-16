# SafeLife Hospital Management System 🏥

A comprehensive, real-time healthcare administration suite built with Django. SafeLife HMS integrates clinical diagnostics, triage telemetry, fleet management, and role-based access controls into a single, unified platform.

## 🌟 Key Features

### 🔐 Role-Based Access Control
The system provides highly specialized dashboards and permissions for 8 distinct roles:
- **Admin**: Full system oversight, staff verification, emergency overrides, and attendance auditing.
- **Doctor**: Appointment scheduling, clinical file access, prescription writing, and emergency "Code Blue" alerts.
- **Nurse**: Patient vitals tracking, ward management, and ventilator telemetry monitoring.
- **Receptionist**: Room & bed allocation, appointment booking, ambulance dispatch, and patient registration.
- **Pharmacist**: Pharmacy inventory management, prescription fulfillment, and stock alerts.
- **Lab Staff**: Deployment of medical diagnostics and lab test results.
- **Accountant**: Auto-billing generation, ledger management, and financial reporting.
- **Patient**: Personal clinical records, prescription history, auto-calculated age tracking, and smart appointment booking.

### 🚑 Public Emergency & Fleet Radar
- **Public SOS Trigger**: A high-visibility emergency dispatch system on the landing page that allows anyone to trigger a "Code Blue" without logging in.
- **Auto-Dispatch Engine**: Automatically routes the first available ambulance to the emergency location and locks its status.
- **SMS Integration Ready**: A built-in mock SMS engine that dynamically generates SMS texts for Patients, Ambulance Drivers, and Doctors during emergencies (pluggable with Twilio/AWS SNS).

### 🛏️ Advanced Ward & Room Allocation
- **Dynamic Bed Tracking**: Manage General, Private, ICU, and Emergency Wards.
- **Medical Case Integration**: Assign patients to beds and dynamically track their specific medical case/reason for admission directly on the occupancy board.
- **Auto-Clearing**: Discharging a patient automatically resets the bed status and clears the medical case.

### 🩺 Clinical Intelligence
- **Digital Ventilation**: Live telemetry tracking for ventilator pressure and oxygen flow, featuring real-time warnings for unstable vitals.
- **Smart Appointments**: Shift-based auto-assignment engine that matches patients to the first available doctor based on the requested department, date, and 3-tier shift schedule (Morning, Evening, Night).
- **Intelligent Auto-Billing**: Seamlessly generates grand totals, percentage discounts, and hardcoded 18% tax rates by analyzing consultation fees, room charges, and lab tests.

## 🛠️ Technology Stack
- **Backend**: Python, Django
- **Database**: SQLite (Development)
- **Frontend**: HTML5, CSS3 (Vanilla), JavaScript, Django Templates
- **Architecture**: MVT (Model-View-Template)

## 🚀 Setup & Installation

1. **Clone the repository**
2. **Set up a virtual environment** (optional but recommended):
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows use: venv\Scripts\activate
   ```
3. **Install Dependencies**:
   ```bash
   pip install django
   ```
4. **Run Migrations**:
   ```bash
   python manage.py makemigrations
   python manage.py migrate
   ```
5. **Start the Development Server**:
   ```bash
   python manage.py runserver
   ```
6. **Access the Portal**: Open `http://127.0.0.1:8000` in your web browser.

## 📋 Staff Verification Protocol
To ensure security, all newly registered staff members (Doctors, Nurses, etc.) must be verified by an **Administrator** before they can access their dashboards. 
- Admins can review pending staff requests in the *Pending Verification* queue on their dashboard.
- Staff must register using a valid Staff ID format (e.g., `_AD_001` for Admins).
