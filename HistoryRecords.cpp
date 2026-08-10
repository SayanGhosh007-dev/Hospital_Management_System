#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PatientRecordSystem {
private:
    int patientId;
    string patientName;
    vector<string> medicalHistory; // Stores past diagnoses/treatments
    vector<string> notificationLog; // Stores historical alerts/notifications sent

public:
    PatientRecordSystem(int id, string name) {
        patientId = id;
        patientName = name;
    }

    // Add a new diagnosis or treatment note to history
    void addMedicalHistory(const string& record) {
        medicalHistory.push_back(record);
        cout << "[RECORD UPDATED] Added new medical entry for " << patientName << ".\n";
    }

    // Log and send a notification
    void sendNotification(const string& message) {
        notificationLog.push_back(message);
        cout << "\n[NOTIFICATION SENT TO " << patientName << "]: " << message << "\n";
    }

    // Display complete patient history and notifications
    void displayCompleteRecord() const {
        cout << "\n==============================================================\n";
        cout << "MEDICAL RECORD FOR: " << patientName << " (ID: " << patientId << ")\n";
        cout << "--------------------------------------------------------------\n";
        
        cout << "Past Medical History & Treatments:\n";
        if (medicalHistory.empty()) {
            cout << "  (No prior history recorded)\n";
        } else {
            for (size_t i = 0; i < medicalHistory.size(); ++i) {
                cout << "  " << (i + 1) << ". " << medicalHistory[i] << "\n";
            }
        }

        cout << "\nNotification & Alert Log:\n";
        if (notificationLog.empty()) {
            cout << "  (No notifications sent)\n";
        } else {
            for (size_t i = 0; i < notificationLog.size(); ++i) {
                cout << "  - " << notificationLog[i] << "\n";
            }
        }
        cout << "==============================================================\n";
    }
};

int main() {
    // Initializing the record system for a patient
    PatientRecordSystem record(301, "Aman Verma");

    // Adding history entries
    record.addMedicalHistory("Diagnosed with Mild Hypertension - Jan 2026");
    record.addMedicalHistory("Prescribed beta-blockers and scheduled follow-up - Feb 2026");

    // Sending notifications
    record.sendNotification("Reminder: Take your medication at 9:00 PM tonight.");
    record.sendNotification("Appointment confirmed with Dr. Gupta for next Tuesday.");

    // Displaying the full integrated record
    record.displayCompleteRecord();

    return 0;
}