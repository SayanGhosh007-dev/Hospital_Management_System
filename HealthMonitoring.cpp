#include <iostream>
#include <string>

using namespace std;

// Class representing Patient Vitals
class Vitals {
private:
    int heartRate;       // in beats per minute (BPM)
    int systolicBP;      // mmHg
    int diastolicBP;     // mmHg
    float temperature;   // Fahrenheit
    int oxygenLevel;     // SpO2 percentage

public:
    // Constructor with default normal values
    Vitals(int hr = 72, int sys = 120, int dia = 80, float temp = 98.6, int o2 = 98) {
        heartRate = hr;
        systolicBP = sys;
        diastolicBP = dia;
        temperature = temp;
        oxygenLevel = o2;
    }

    // Update vitals method
    void updateVitals(int hr, int sys, int dia, float temp, int o2) {
        heartRate = hr;
        systolicBP = sys;
        diastolicBP = dia;
        temperature = temp;
        oxygenLevel = o2;
    }

    // Logic to check if vitals are in a critical state
    bool isCritical() const {
        if (heartRate < 50 || heartRate > 130) return true;
        if (systolicBP > 160 || systolicBP < 90) return true;
        if (oxygenLevel < 92) return true;
        if (temperature > 103.0 || temperature < 95.0) return true;
        return false;
    }

    // Display current vitals
    void displayVitals() const {
        cout << "   - Heart Rate: " << heartRate << " BPM\n";
        cout << "   - Blood Pressure: " << systolicBP << "/" << diastolicBP << " mmHg\n";
        cout << "   - Temperature: " << temperature << " °F\n";
        cout << "   - Oxygen Level (SpO2): " << oxygenLevel << "%\n";
    }
};

// Class managing individual Patient Health Monitoring
class PatientMonitor {
private:
    int patientId;
    string patientName;
    Vitals currentVitals; // Composition: PatientMonitor has a Vitals object

public:
    PatientMonitor(int id, string name) {
        patientId = id;
        patientName = name;
    }

    int getId() const { return patientId; }
    string getName() const { return patientName; }

    // Record and check new vitals reading
    void recordReading(int hr, int sys, int dia, float temp, int o2) {
        cout << "\n[HEALTH MONITOR] Updating vitals for " << patientName << " (ID: " << patientId << ")\n";
        currentVitals.updateVitals(hr, sys, dia, temp, o2);
        currentVitals.displayVitals();

        if (currentVitals.isCritical()) {
            cout << ">>> CRITICAL WARNING: Abnormal health parameters detected for " << patientName << "! <<< \n";
        } else {
            cout << "Status: Vitals are within stable, safe limits.\n";
        }
    }
};

int main() {
    // Initializing a patient monitor
    PatientMonitor monitor1(201, "Rahul Sharma");

    // Simulating normal health reading update
    monitor1.recordReading(75, 120, 80, 98.4, 99);

    // Simulating a critical health reading update
    monitor1.recordReading(140, 170, 100, 104.2, 88);

    return 0;
}