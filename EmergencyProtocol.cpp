#include <iostream>
#include <vector>
#include <string>

using namespace std;

class EmergencyDoctor {
private:
    int doctorId;
    string name;
    string specialization;
    bool isAvailable;

public:
    EmergencyDoctor(int id, const string& docName, const string& spec);

    int getId() const;
    string getName() const;
    string getSpecialization() const;
    bool getAvailability() const;

    void setAvailability(bool status);
    void receiveAlert(const string& message) const;
};

class EmergencySystem {
private:
    vector<EmergencyDoctor> doctors;

public:
    void registerDoctor(const EmergencyDoctor& doc);
    void triggerEmergency(const string& requiredSpecialization, const string& alertDetails);
    const vector<EmergencyDoctor>& getRegisteredDoctors() const;
};

EmergencyDoctor::EmergencyDoctor(int id, const string& docName, const string& spec)
    : doctorId(id), name(docName), specialization(spec), isAvailable(true) {}

int EmergencyDoctor::getId() const { return doctorId; }
string EmergencyDoctor::getName() const { return name; }
string EmergencyDoctor::getSpecialization() const { return specialization; }
bool EmergencyDoctor::getAvailability() const { return isAvailable; }

void EmergencyDoctor::setAvailability(bool status) {
    isAvailable = status;
}

void EmergencyDoctor::receiveAlert(const string& message) const {
    cout << "\n[ALERT DISPATCHED TO DR. " << name << " (" << specialization << ")]\n";
    cout << "Message: " << message << "\n";
    cout << "Status: Delivered successfully via secure hospital channel.\n";
}

void EmergencySystem::registerDoctor(const EmergencyDoctor& doc) {
    doctors.push_back(doc);
}

void EmergencySystem::triggerEmergency(const string& requiredSpecialization, const string& alertDetails) {
    cout << "\n================ EMERGENCY PROTOCOL ACTIVATED ================\n";
    cout << "Details: " << alertDetails << "\n";
    cout << "--------------------------------------------------------------\n";

    bool alertSent = false;
    for (const auto& doc : doctors) {
        if ((doc.getSpecialization() == requiredSpecialization || requiredSpecialization == "General") && doc.getAvailability()) {
            doc.receiveAlert(alertDetails);
            alertSent = true;
        }
    }

    if (!alertSent) {
        cout << "WARNING: No available doctors found for specialization: " << requiredSpecialization << "!\n";
    }
    cout << "==============================================================\n";
}

const vector<EmergencyDoctor>& EmergencySystem::getRegisteredDoctors() const {
    return doctors;
}