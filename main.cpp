#include "Department.cpp"
#include "AmbulanceRadars.cpp"
#include "DigitalVentilations.cpp"
#include "EmergencyProtocol.cpp"
#include "HealthMonitoring.cpp"
#include "HistoryRecords.cpp"
#include "InventorySystems.cpp"
#include "Maintenance.cpp"
#include "MortuaryManagement.cpp"
#include "PunchSystems.cpp"
#include "RateofRisk.cpp"
#include "Staff.cpp"
#include "roomoccupancy.cpp"

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// Main console input validators
namespace {
    int main_getValidInteger(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (value >= 0) return value;
                cout << "Value cannot be negative. Please try again.\n";
            } else {
                cout << "Invalid numeric input. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    double main_getValidDouble(const string& prompt) {
        double value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (value >= 0.0) return value;
                cout << "Value cannot be negative. Please try again.\n";
            } else {
                cout << "Invalid numeric input. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    float main_getValidFloat(const string& prompt) {
        float value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (value >= 0.0f) return value;
                cout << "Value cannot be negative. Please try again.\n";
            } else {
                cout << "Invalid numeric input. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    string main_getNonEmptyString(const string& prompt) {
        string value;
        while (true) {
            cout << prompt;
            getline(cin, value);
            if (!value.empty()) return value;
            cout << "Input cannot be empty. Please try again.\n";
        }
    }
}

int main() {
    cout << "========================================================\n";
    cout << "       HOSPITAL MANAGEMENT SYSTEM INTEGRATED DASHBOARD\n";
    cout << "========================================================\n";

    // Module instances to interact with
    Department department;
    AmbulanceRadar ambulance;
    DigitalVentilationSystem ventilator;
    EmergencySystem emergency;
    PatientMonitor monitor(0, "");
    PatientRecordSystem patientRecord(0, "");
    InventoryItem inventory;
    Maintenance maintenance;
    MortuaryManagement mortuary;
    PunchInOut punchSystem;
    RateOfRisk riskAssessment;
    Staff staff;
    Room room;

    while (true) {
        cout << "\n========================================================\n";
        cout << "                 MAIN INTEGRATION MENU\n";
        cout << "========================================================\n";
        cout << "1.  Department Module\n";
        cout << "2.  Ambulance Radar Module\n";
        cout << "3.  Digital Ventilation Module\n";
        cout << "4.  Emergency Protocol Module\n";
        cout << "5.  Health Monitoring Module\n";
        cout << "6.  History Records Module\n";
        cout << "7.  Inventory System Module\n";
        cout << "8.  Maintenance Module\n";
        cout << "9.  Mortuary Management Module\n";
        cout << "10. Punch In/Out System\n";
        cout << "11. Rate of Risk Assessment Module\n";
        cout << "12. Staff Management Module\n";
        cout << "13. Room Occupancy Module\n";
        cout << "14. Exit Integrated Application\n";
        cout << "========================================================\n";

        int choice = main_getValidInteger("Select a module to test (1-14): ");
        if (choice == 14) {
            cout << "\nExiting Integrated HMS Application. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: { // Department
                bool sub = true;
                while (sub) {
                    cout << "\n--- Department Submenu ---\n";
                    cout << "1. Add Department\n";
                    cout << "2. Display Department Details\n";
                    cout << "3. Update Department Details\n";
                    cout << "4. Remove Department Details\n";
                    cout << "5. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 5) { sub = false; break; }
                    switch (subChoice) {
                        case 1: department.addDepartment(); break;
                        case 2: department.displayDepartment(); break;
                        case 3: department.updateDepartment(); break;
                        case 4: department.removeDepartment(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 2: { // Ambulance Radar
                bool sub = true;
                while (sub) {
                    cout << "\n--- Ambulance Radar Submenu ---\n";
                    cout << "1. Set/Update Ambulance Details\n";
                    cout << "2. Display Location Tracker\n";
                    cout << "3. Display Full Ambulance Details\n";
                    cout << "4. Assign Ambulance to Patient\n";
                    cout << "5. Release Ambulance (Make Available)\n";
                    cout << "6. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 6) { sub = false; break; }
                    switch (subChoice) {
                        case 1: {
                            int id = main_getValidInteger("Enter Ambulance ID: ");
                            string number = main_getNonEmptyString("Enter Plate Number: ");
                            string driver = main_getNonEmptyString("Enter Driver Name: ");
                            string phone = main_getNonEmptyString("Enter Contact Number: ");
                            string loc = main_getNonEmptyString("Enter Current Location: ");
                            string dest = main_getNonEmptyString("Enter Destination Location: ");
                            double lat = main_getValidDouble("Enter Latitude coordinate: ");
                            double lon = main_getValidDouble("Enter Longitude coordinate: ");
                            ambulance = AmbulanceRadar(id, number, driver, phone, loc, dest, lat, lon);
                            cout << "Ambulance Details saved.\n";
                            break;
                        }
                        case 2: ambulance.displayLocation(); break;
                        case 3: ambulance.displayAmbulanceDetails(); break;
                        case 4: ambulance.assignAmbulance(); cout << "Ambulance assigned.\n"; break;
                        case 5: ambulance.releaseAmbulance(); cout << "Ambulance released.\n"; break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 3: { // Digital Ventilation
                bool sub = true;
                while (sub) {
                    cout << "\n--- Ventilation Control Submenu ---\n";
                    cout << "1. Assign Ventilator\n";
                    cout << "2. Connect Ventilator\n";
                    cout << "3. Update Ventilation Parameters\n";
                    cout << "4. Display Current Ventilation Data\n";
                    cout << "5. Perform Ventilation Safety & Status Check\n";
                    cout << "6. Generate Critical Alerts\n";
                    cout << "7. Print Ventilation Report\n";
                    cout << "8. Disconnect Ventilator\n";
                    cout << "9. Remove Ventilator Assignment\n";
                    cout << "10. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 10) { sub = false; break; }
                    switch (subChoice) {
                        case 1: ventilator.assignVentilator(); break;
                        case 2: ventilator.connectVentilator(); break;
                        case 3: ventilator.updateVentilationData(); break;
                        case 4: ventilator.displayVentilationData(); break;
                        case 5: ventilator.checkVentilationStatus(); break;
                        case 6: ventilator.generateAlert(); break;
                        case 7: ventilator.generateVentilationReport(); break;
                        case 8: ventilator.disconnectVentilator(); break;
                        case 9: ventilator.removeVentilator(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 4: { // Emergency Protocol
                bool sub = true;
                while (sub) {
                    cout << "\n--- Emergency Protocols Submenu ---\n";
                    cout << "1. Register On-Call Doctor\n";
                    cout << "2. Trigger Emergency Protocol Alert\n";
                    cout << "3. View All Registered On-Call Doctors\n";
                    cout << "4. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 4) { sub = false; break; }
                    switch (subChoice) {
                        case 1: {
                            int id = main_getValidInteger("Enter Doctor ID: ");
                            string name = main_getNonEmptyString("Enter Doctor Name: ");
                            string specialty = main_getNonEmptyString("Enter Specialization: ");
                            emergency.registerDoctor(EmergencyDoctor(id, name, specialty));
                            cout << "Emergency doctor registered.\n";
                            break;
                        }
                        case 2: {
                            string spec = main_getNonEmptyString("Enter required Doctor Specialization (or 'General'): ");
                            string msg = main_getNonEmptyString("Enter emergency broadcast alert details: ");
                            emergency.triggerEmergency(spec, msg);
                            break;
                        }
                        case 3: {
                            const auto& list = emergency.getRegisteredDoctors();
                            if (list.empty()) {
                                cout << "No on-call emergency doctors registered.\n";
                            } else {
                                cout << "\n--- Registered Doctors ---\n";
                                for (const auto& doc : list) {
                                    cout << "ID: " << doc.getId() << " | Name: " << doc.getName() << " | Dept: " << doc.getSpecialization() << endl;
                                }
                            }
                            break;
                        }
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 5: { // Health Monitoring
                bool sub = true;
                while (sub) {
                    cout << "\n--- Health Monitoring Submenu ---\n";
                    cout << "1. Setup Patient Monitor\n";
                    cout << "2. Record New Vitals Reading\n";
                    cout << "3. Check Current Vitals & Alert Status\n";
                    cout << "4. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 4) { sub = false; break; }
                    switch (subChoice) {
                        case 1: {
                            int id = main_getValidInteger("Enter Patient ID: ");
                            string name = main_getNonEmptyString("Enter Patient Name: ");
                            monitor = PatientMonitor(id, name);
                            cout << "Patient monitor setup completed.\n";
                            break;
                        }
                        case 2: {
                            int hr = main_getValidInteger("Enter Heart Rate (BPM): ");
                            int sys = main_getValidInteger("Enter Systolic BP (mmHg): ");
                            int dia = main_getValidInteger("Enter Diastolic BP (mmHg): ");
                            float temp = main_getValidFloat("Enter Body Temperature (°F): ");
                            int oxy = main_getValidInteger("Enter SpO2 Oxygen Level (%): ");
                            monitor.recordReading(hr, sys, dia, temp, oxy);
                            break;
                        }
                        case 3: {
                            monitor.getCurrentVitals().displayVitals();
                            if (monitor.getCurrentVitals().isCritical()) {
                                cout << "ALERT: Patient is in CRITICAL state!\n";
                            }
                            break;
                        }
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 6: { // History Records
                bool sub = true;
                while (sub) {
                    cout << "\n--- Patient History Submenu ---\n";
                    cout << "1. Setup Patient Record Base\n";
                    cout << "2. Add Medical Diagnosis Entry\n";
                    cout << "3. View Full Patient Record & Notification Logs\n";
                    cout << "4. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 4) { sub = false; break; }
                    switch (subChoice) {
                        case 1: {
                            int id = main_getValidInteger("Enter Patient ID: ");
                            string name = main_getNonEmptyString("Enter Patient Name: ");
                            patientRecord = PatientRecordSystem(id, name);
                            cout << "Patient record base created.\n";
                            break;
                        }
                        case 2: {
                            string diag = main_getNonEmptyString("Enter Diagnosis/Medical Log: ");
                            patientRecord.addMedicalHistory(diag);
                            break;
                        }
                        case 3: {
                            patientRecord.displayCompleteRecord();
                            break;
                        }
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 7: { // Inventory System
                bool sub = true;
                while (sub) {
                    cout << "\n--- Inventory Submenu ---\n";
                    cout << "1. Add Item to Inventory\n";
                    cout << "2. Display Item Details\n";
                    cout << "3. Add Stock\n";
                    cout << "4. Remove/Deduct Stock\n";
                    cout << "5. Check Stock Status\n";
                    cout << "6. Check Low Stock Alarm\n";
                    cout << "7. Check Expiry Details\n";
                    cout << "8. Update Item Information\n";
                    cout << "9. Delete Item Record\n";
                    cout << "10. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 10) { sub = false; break; }
                    switch (subChoice) {
                        case 1: inventory.addItem(); break;
                        case 2: inventory.displayItemDetails(); break;
                        case 3: inventory.addStock(); break;
                        case 4: inventory.removeStock(); break;
                        case 5: inventory.checkStock(); break;
                        case 6: inventory.checkLowStock(); break;
                        case 7: inventory.checkExpiry(); break;
                        case 8: inventory.updateItem(); break;
                        case 9: inventory.deleteItem(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 8: { // Maintenance
                bool sub = true;
                while (sub) {
                    cout << "\n--- Maintenance Record Submenu ---\n";
                    cout << "1. Add Maintenance Record\n";
                    cout << "2. View Maintenance Record\n";
                    cout << "3. Update Maintenance Record Details\n";
                    cout << "4. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 4) { sub = false; break; }
                    switch (subChoice) {
                        case 1: maintenance.addMaintenanceRecord(); break;
                        case 2: maintenance.viewMaintenanceRecord(); break;
                        case 3: maintenance.updateMaintenanceRecord(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 9: { // Mortuary Management
                bool sub = true;
                while (sub) {
                    cout << "\n--- Mortuary Management Submenu ---\n";
                    cout << "1. Admit Body to Mortuary\n";
                    cout << "2. Record Death Details\n";
                    cout << "3. Update Body Identification Status\n";
                    cout << "4. Release Body to Family/Guardians\n";
                    cout << "5. Display Mortuary Record\n";
                    cout << "6. Update Mortuary Record Details\n";
                    cout << "7. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 7) { sub = false; break; }
                    switch (subChoice) {
                        case 1: mortuary.admitBody(); break;
                        case 2: mortuary.recordDeathDetails(); break;
                        case 3: mortuary.identifyBody(); break;
                        case 4: mortuary.releaseBody(); break;
                        case 5: mortuary.displayMortuaryRecord(); break;
                        case 6: mortuary.updateMortuaryRecord(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 10: { // Punch In/Out System
                bool sub = true;
                while (sub) {
                    cout << "\n--- Punch In/Out Submenu ---\n";
                    cout << "1. Enter Employee Profile Details\n";
                    cout << "2. Punch In\n";
                    cout << "3. Punch Out\n";
                    cout << "4. Display Employee Profile Details\n";
                    cout << "5. View Punch Attendance Log\n";
                    cout << "6. Reset Attendance Records\n";
                    cout << "7. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 7) { sub = false; break; }
                    switch (subChoice) {
                        case 1: punchSystem.setEmployeeDetails(); break;
                        case 2: punchSystem.punchIn(); break;
                        case 3: punchSystem.punchOut(); break;
                        case 4: punchSystem.getEmployeeDetails(); break;
                        case 5: punchSystem.displayAttendance(); break;
                        case 6: punchSystem.resetAttendance(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 11: { // Rate of Risk
                bool sub = true;
                while (sub) {
                    cout << "\n--- Risk Rate Assessment Submenu ---\n";
                    cout << "1. Set Patient & Admission Details\n";
                    cout << "2. Calculate & Score Condition Risk Level\n";
                    cout << "3. Display Risk Assessment Report\n";
                    cout << "4. Update Assessment Details\n";
                    cout << "5. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 5) { sub = false; break; }
                    switch (subChoice) {
                        case 1: riskAssessment.setPatientDetails(); break;
                        case 2: riskAssessment.calculateRisk(); break;
                        case 3: riskAssessment.displayRisk(); break;
                        case 4: riskAssessment.updateRisk(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 12: { // Staff Management
                bool sub = true;
                while (sub) {
                    cout << "\n--- Staff Directory Submenu ---\n";
                    cout << "1. Add Doctor Record\n";
                    cout << "2. View All Doctors\n";
                    cout << "3. Update Doctor Details\n";
                    cout << "4. Delete Doctor Record\n";
                    cout << "5. Search Doctor\n";
                    cout << "6. Add Nurse Record\n";
                    cout << "7. View All Nurses\n";
                    cout << "8. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 8) { sub = false; break; }
                    switch (subChoice) {
                        case 1: staff.addDoctor(); break;
                        case 2: staff.viewDoctorDetails(); break;
                        case 3: staff.updateDoctorDetails(); break;
                        case 4: staff.deleteDoctor(); break;
                        case 5: staff.searchDoctor(); break;
                        case 6: staff.addNurse(); break;
                        case 7: staff.viewNurseDetails(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            case 13: { // Room Occupancy
                bool sub = true;
                while (sub) {
                    cout << "\n--- Room Occupancy Submenu ---\n";
                    cout << "1. Add Room Details\n";
                    cout << "2. View All Rooms\n";
                    cout << "3. Check Available Rooms\n";
                    cout << "4. Allocate Room to Patient\n";
                    cout << "5. Vacate Room\n";
                    cout << "6. Update Room Status\n";
                    cout << "7. Search Room\n";
                    cout << "8. Return to Main Menu\n";
                    int subChoice = main_getValidInteger("Enter Choice: ");
                    if (subChoice == 8) { sub = false; break; }
                    switch (subChoice) {
                        case 1: room.addRoom(); break;
                        case 2: room.viewRooms(); break;
                        case 3: room.checkRoomAvailability(); break;
                        case 4: room.allocateRoom(); break;
                        case 5: room.vacateRoom(); break;
                        case 6: room.updateRoomStatus(); break;
                        case 7: room.searchRoom(); break;
                        default: cout << "Invalid choice.\n"; break;
                    }
                }
                break;
            }
            default:
                cout << "Invalid main menu selection. Please try again.\n";
                break;
        }
    }
    return 0;
}
