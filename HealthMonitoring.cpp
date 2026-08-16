#include <iostream>
#include <string>

using namespace std;

class Vitals {
private:
    int heartRate;       // BPM
    int systolicBP;      // mmHg
    int diastolicBP;     // mmHg
    float temperature;   // Fahrenheit
    int oxygenLevel;     // SpO2%

public:
    Vitals(int hr = 72, int sys = 120, int dia = 80, float temp = 98.6f, int o2 = 98);

    void updateVitals(int hr, int sys, int dia, float temp, int o2);
    bool isCritical() const;
    void displayVitals() const;

    int getHeartRate() const;
    int getSystolicBP() const;
    int getDiastolicBP() const;
    float getTemperature() const;
    int getOxygenLevel() const;

    void setHeartRate(int hr);
    void setSystolicBP(int sys);
    void setDiastolicBP(int dia);
    void setTemperature(float temp);
    void setOxygenLevel(int o2);
};

class PatientMonitor {
private:
    int patientId;
    string patientName;
    Vitals currentVitals;

public:
    PatientMonitor(int id, const string& name);

    int getId() const;
    string getName() const;
    const Vitals& getCurrentVitals() const;

    void recordReading(int hr, int sys, int dia, float temp, int o2);
};

Vitals::Vitals(int hr, int sys, int dia, float temp, int o2)
    : heartRate(hr), systolicBP(sys), diastolicBP(dia), temperature(temp), oxygenLevel(o2) {}

void Vitals::updateVitals(int hr, int sys, int dia, float temp, int o2) {
    heartRate = hr;
    systolicBP = sys;
    diastolicBP = dia;
    temperature = temp;
    oxygenLevel = o2;
}

bool Vitals::isCritical() const {
    if (heartRate < 50 || heartRate > 130) return true;
    if (systolicBP > 160 || systolicBP < 90) return true;
    if (oxygenLevel < 92) return true;
    if (temperature > 103.0f || temperature < 95.0f) return true;
    return false;
}

void Vitals::displayVitals() const {
    cout << "   - Heart Rate: " << heartRate << " BPM\n";
    cout << "   - Blood Pressure: " << systolicBP << "/" << diastolicBP << " mmHg\n";
    cout << "   - Temperature: " << temperature << " \u00B0F\n";
    cout << "   - Oxygen Level (SpO2): " << oxygenLevel << "%\n";
}

int Vitals::getHeartRate() const { return heartRate; }
int Vitals::getSystolicBP() const { return systolicBP; }
int Vitals::getDiastolicBP() const { return diastolicBP; }
float Vitals::getTemperature() const { return temperature; }
int Vitals::getOxygenLevel() const { return oxygenLevel; }

void Vitals::setHeartRate(int hr) { heartRate = hr; }
void Vitals::setSystolicBP(int sys) { systolicBP = sys; }
void Vitals::setDiastolicBP(int dia) { diastolicBP = dia; }
void Vitals::setTemperature(float temp) { temperature = temp; }
void Vitals::setOxygenLevel(int o2) { oxygenLevel = o2; }

PatientMonitor::PatientMonitor(int id, const string& name)
    : patientId(id), patientName(name), currentVitals() {}

int PatientMonitor::getId() const { return patientId; }
string PatientMonitor::getName() const { return patientName; }
const Vitals& PatientMonitor::getCurrentVitals() const { return currentVitals; }

void PatientMonitor::recordReading(int hr, int sys, int dia, float temp, int o2) {
    cout << "\n[HEALTH MONITOR] Updating vitals for " << patientName << " (ID: " << patientId << ")\n";
    currentVitals.updateVitals(hr, sys, dia, temp, o2);
    currentVitals.displayVitals();

    if (currentVitals.isCritical()) {
        cout << ">>> CRITICAL WARNING: Abnormal health parameters detected for " << patientName << "! <<< \n";
    } else {
        cout << "Status: Vitals are within stable, safe limits.\n";
    }
}