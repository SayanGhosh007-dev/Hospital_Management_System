#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Class representing a Doctor
class Doctor {
private:
    int doctorId;
    string name;
    string specialization;
    bool isAvailable;

public:
    Doctor(int id, string docName, string spec) {
        doctorId = id;
        name = docName;
        specialization = spec;
        isAvailable = true;
    }

    int getId() const { return doctorId; }
    string getName() const { return name; }
    string getSpecialization() const { return specialization; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool status) {
        isAvailable = status;
    }

    // Method to simulate receiving an emergency alert message
    void receiveAlert(const string& message) const {
        cout << "\n[ALERT DISPATCHED TO DR. " << name << " (" << specialization << ")]\n";
        cout << "Message: " << message << "\n";
        cout << "Status: Delivered successfully via secure hospital channel.\n";
    }
};

// Class managing the Emergency Protocol
class EmergencySystem {
private:
    vector<Doctor> doctors;

public:
    // Add a doctor to the system registry
    void registerDoctor(const Doctor& doc) {
        doctors.push_back(doc);
    }

    // Trigger emergency alert to doctors matching a specialization or all available doctors
    void triggerEmergency(string requiredSpecialization, string alertDetails) {
        cout << "\n================ EMERGENCY PROTOCOL ACTIVATED ================\n";
        cout << "Details: " << alertDetails << "\n";
        cout << "--------------------------------------------------------------\n";

        bool alertSent = false;
        for (const auto& doc : doctors) {
            // If specialization matches or is general emergency, and doctor is available
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
};

int main() {
    // Initialize the Emergency System
    EmergencySystem emergencySys;

    // Registering some doctors
    emergencySys.registerDoctor(Doctor(101, "Dr. Sharma", "Cardiology"));
    emergencySys.registerDoctor(Doctor(102, "Dr. Verma", "Emergency"));
    emergencySys.registerDoctor(Doctor(103, "Dr. Gupta", "Neurology"));

    // Simulating an incoming emergency case requiring an Emergency specialist
    string emergencyCase = "CRITICAL: Patient experiencing severe cardiac arrest in Room 402. Immediate response required!";
    
    // Triggering the alert
    emergencySys.triggerEmergency("Cardiology", emergencyCase);

    return 0;
}