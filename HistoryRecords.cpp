#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PatientRecordSystem {
private:
    int patientId;
    string patientName;
    vector<string> medicalHistory;
    vector<string> notificationLog;

public:
    PatientRecordSystem(int id, const string& name);

    int getPatientId() const;
    string getPatientName() const;
    const vector<string>& getMedicalHistory() const;
    const vector<string>& getNotificationLog() const;

    void setPatientId(int id);
    void setPatientName(const string& name);

    void addMedicalHistory(const string& record);
    void sendNotification(const string& message);
    void displayCompleteRecord() const;
};

PatientRecordSystem::PatientRecordSystem(int id, const string& name)
    : patientId(id), patientName(name) {}

int PatientRecordSystem::getPatientId() const { return patientId; }
string PatientRecordSystem::getPatientName() const { return patientName; }
const vector<string>& PatientRecordSystem::getMedicalHistory() const { return medicalHistory; }
const vector<string>& PatientRecordSystem::getNotificationLog() const { return notificationLog; }

void PatientRecordSystem::setPatientId(int id) { patientId = id; }
void PatientRecordSystem::setPatientName(const string& name) { patientName = name; }

void PatientRecordSystem::addMedicalHistory(const string& record) {
    medicalHistory.push_back(record);
    cout << "[RECORD UPDATED] Added new medical entry for " << patientName << ".\n";
}

void PatientRecordSystem::sendNotification(const string& message) {
    notificationLog.push_back(message);
    cout << "\n[NOTIFICATION SENT TO " << patientName << "]: " << message << "\n";
}

void PatientRecordSystem::displayCompleteRecord() const {
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