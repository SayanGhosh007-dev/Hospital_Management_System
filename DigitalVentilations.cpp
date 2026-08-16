#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class DigitalVentilationSystem {
private:
    int patientId;
    int ventilatorId;
    double oxygenLevel;
    double respiratoryRate;
    double tidalVolume;
    double peep;
    double peakPressure;
    double plateauPressure;
    string patientName;
    string ventilationMode;
    string startTime;
    string currentStatus;
    bool ventilatorConnected;

public:
    DigitalVentilationSystem();

    // Programmatic setters and getters
    int getPatientId() const;
    void setPatientId(int id);

    int getVentilatorId() const;
    void setVentilatorId(int id);

    double getOxygenLevel() const;
    void setOxygenLevel(double level);

    double getRespiratoryRate() const;
    void setRespiratoryRate(double rate);

    double getTidalVolume() const;
    void setTidalVolume(double volume);

    double getPeep() const;
    void setPeep(double value);

    double getPeakPressure() const;
    void setPeakPressure(double value);

    double getPlateauPressure() const;
    void setPlateauPressure(double value);

    string getPatientName() const;
    void setPatientName(const string& name);

    string getVentilationMode() const;
    void setVentilationMode(const string& mode);

    string getStartTime() const;
    void setStartTime(const string& time);

    string getCurrentStatus() const;
    void setCurrentStatus(const string& status);

    bool isVentilatorConnected() const;
    void setVentilatorConnected(bool connected);

    // Business Logic Operations
    void assignVentilatorProgrammatic(int pId, const string& pName, int vId, const string& mode, const string& start);
    void removeVentilatorProgrammatic();
    void connectVentilator();
    void disconnectVentilator();
    
    // Safety & Monitoring Check Functions
    bool checkVentilationStatus(string& statusMessage);
    bool checkAlerts(string& alertMessage);

    // Console Interactive Operations (kept for backward compatibility & testing)
    void assignVentilator();
    void removeVentilator();
    void updateVentilationData();
    void displayVentilationData() const;
    void checkVentilationStatus();
    void generateAlert();
    void generateVentilationReport() const;
};

static double vent_getValidDouble(const string& prompt, double minVal = 0.0) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= minVal) {
                return value;
            }
            cout << "Value cannot be less than " << minVal << ". Please try again.\n";
        } else {
            cout << "Invalid numeric input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

static int vent_getValidInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0) {
                return value;
            }
            cout << "Value cannot be negative. Please try again.\n";
        } else {
            cout << "Invalid numeric input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

static string vent_getNonEmptyString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Input cannot be empty. Please try again.\n";
    }
}

DigitalVentilationSystem::DigitalVentilationSystem()
    : patientId(0), ventilatorId(0), oxygenLevel(0.0), respiratoryRate(0.0),
      tidalVolume(0.0), peep(0.0), peakPressure(0.0), plateauPressure(0.0),
      patientName(""), ventilationMode("Not Set"), startTime(""),
      currentStatus("Inactive"), ventilatorConnected(false) {}

int DigitalVentilationSystem::getPatientId() const { return patientId; }
void DigitalVentilationSystem::setPatientId(int id) { patientId = id; }

int DigitalVentilationSystem::getVentilatorId() const { return ventilatorId; }
void DigitalVentilationSystem::setVentilatorId(int id) { ventilatorId = id; }

double DigitalVentilationSystem::getOxygenLevel() const { return oxygenLevel; }
void DigitalVentilationSystem::setOxygenLevel(double level) { if (level >= 0.0) oxygenLevel = level; }

double DigitalVentilationSystem::getRespiratoryRate() const { return respiratoryRate; }
void DigitalVentilationSystem::setRespiratoryRate(double rate) { if (rate >= 0.0) respiratoryRate = rate; }

double DigitalVentilationSystem::getTidalVolume() const { return tidalVolume; }
void DigitalVentilationSystem::setTidalVolume(double volume) { if (volume >= 0.0) tidalVolume = volume; }

double DigitalVentilationSystem::getPeep() const { return peep; }
void DigitalVentilationSystem::setPeep(double value) { if (value >= 0.0) peep = value; }

double DigitalVentilationSystem::getPeakPressure() const { return peakPressure; }
void DigitalVentilationSystem::setPeakPressure(double value) { if (value >= 0.0) peakPressure = value; }

double DigitalVentilationSystem::getPlateauPressure() const { return plateauPressure; }
void DigitalVentilationSystem::setPlateauPressure(double value) { if (value >= 0.0) plateauPressure = value; }

string DigitalVentilationSystem::getPatientName() const { return patientName; }
void DigitalVentilationSystem::setPatientName(const string& name) { patientName = name; }

string DigitalVentilationSystem::getVentilationMode() const { return ventilationMode; }
void DigitalVentilationSystem::setVentilationMode(const string& mode) { ventilationMode = mode; }

string DigitalVentilationSystem::getStartTime() const { return startTime; }
void DigitalVentilationSystem::setStartTime(const string& time) { startTime = time; }

string DigitalVentilationSystem::getCurrentStatus() const { return currentStatus; }
void DigitalVentilationSystem::setCurrentStatus(const string& status) { currentStatus = status; }

bool DigitalVentilationSystem::isVentilatorConnected() const { return ventilatorConnected; }
void DigitalVentilationSystem::setVentilatorConnected(bool connected) { ventilatorConnected = connected; }

void DigitalVentilationSystem::assignVentilatorProgrammatic(int pId, const string& pName, int vId, const string& mode, const string& start) {
    patientId = pId;
    patientName = pName;
    ventilatorId = vId;
    ventilationMode = mode;
    startTime = start;
    currentStatus = "Assigned";
}

void DigitalVentilationSystem::removeVentilatorProgrammatic() {
    ventilatorId = 0;
    ventilationMode = "Not Set";
    startTime = "";
    currentStatus = "Inactive";
    oxygenLevel = 0.0;
    respiratoryRate = 0.0;
    tidalVolume = 0.0;
    peep = 0.0;
    peakPressure = 0.0;
    plateauPressure = 0.0;
    patientId = 0;
    patientName = "";
    ventilatorConnected = false;
}

void DigitalVentilationSystem::assignVentilator() {
    if (ventilatorId != 0) {
        cout << "A ventilator is already assigned to this patient.\n";
        return;
    }
    patientId = vent_getValidInteger("Enter Patient ID: ");
    patientName = vent_getNonEmptyString("Enter Patient Name: ");
    ventilatorId = vent_getValidInteger("Enter Ventilator ID: ");
    ventilationMode = vent_getNonEmptyString("Enter Ventilation Mode: ");
    startTime = vent_getNonEmptyString("Enter Ventilation Start Time: ");
    currentStatus = "Assigned";
    cout << "Ventilator assigned successfully.\n";
}

void DigitalVentilationSystem::removeVentilator() {
    if (ventilatorId == 0) {
        cout << "No ventilator is currently assigned.\n";
        return;
    }
    if (ventilatorConnected) {
        cout << "Disconnect the ventilator before removing it.\n";
        return;
    }
    removeVentilatorProgrammatic();
    cout << "Ventilator removed successfully.\n";
}

void DigitalVentilationSystem::connectVentilator() {
    if (ventilatorId == 0) {
        cout << "No ventilator has been assigned.\n";
        return;
    }
    if (ventilatorConnected) {
        cout << "Ventilator is already connected.\n";
        return;
    }
    ventilatorConnected = true;
    currentStatus = "Connected";
    cout << "Ventilator connected successfully.\n";
}

void DigitalVentilationSystem::disconnectVentilator() {
    if (!ventilatorConnected) {
        cout << "Ventilator is already disconnected.\n";
        return;
    }
    ventilatorConnected = false;
    currentStatus = "Disconnected";
    cout << "Ventilator disconnected successfully.\n";
}

void DigitalVentilationSystem::updateVentilationData() {
    if (!ventilatorConnected) {
        cout << "Cannot update ventilation data. Ventilator is not connected.\n";
        return;
    }
    cout << "\n--- Update Ventilation Data ---\n";
    oxygenLevel = vent_getValidDouble("Enter Oxygen Level (%): ");
    respiratoryRate = vent_getValidDouble("Enter Respiratory Rate (breaths/min): ");
    tidalVolume = vent_getValidDouble("Enter Tidal Volume (mL): ");
    peep = vent_getValidDouble("Enter PEEP (cmH2O): ");
    peakPressure = vent_getValidDouble("Enter Peak Pressure (cmH2O): ");
    plateauPressure = vent_getValidDouble("Enter Plateau Pressure (cmH2O): ");
    currentStatus = "Monitoring";
    cout << "Ventilation data updated successfully.\n";
}

void DigitalVentilationSystem::displayVentilationData() const {
    if (ventilatorId == 0) {
        cout << "No ventilator information available.\n";
        return;
    }
    cout << "\n========================================\n";
    cout << "       VENTILATION DATA\n";
    cout << "========================================\n";
    cout << "Patient ID          : " << patientId << endl;
    cout << "Patient Name        : " << patientName << endl;
    cout << "Ventilator ID       : " << ventilatorId << endl;
    cout << "ventilation Mode    : " << ventilationMode << endl;
    cout << "Oxygen Level        : " << fixed << setprecision(2) << oxygenLevel << " %\n";
    cout << "Respiratory Rate    : " << respiratoryRate << " breaths/min\n";
    cout << "Tidal Volume        : " << tidalVolume << " mL\n";
    cout << "PEEP                : " << peep << " cmH2O\n";
    cout << "Peak Pressure       : " << peakPressure << " cmH2O\n";
    cout << "Plateau Pressure    : " << plateauPressure << " cmH2O\n";
    cout << "Start Time          : " << startTime << endl;
    cout << "Connection Status   : " << (ventilatorConnected ? "Connected" : "Disconnected") << endl;
    cout << "Current Status      : " << currentStatus << endl;
    cout << "========================================\n";
}

bool DigitalVentilationSystem::checkVentilationStatus(string& statusMessage) {
    if (!ventilatorConnected) {
        statusMessage = "WARNING: Ventilator is not connected.";
        currentStatus = "Disconnected";
        return false;
    }
    bool abnormal = false;
    statusMessage = "";
    if (oxygenLevel < 21.0 || oxygenLevel > 100.0) { statusMessage += "WARNING: Oxygen level outside valid range (21-100%).\n"; abnormal = true; }
    if (respiratoryRate <= 0) { statusMessage += "WARNING: Respiratory rate is invalid.\n"; abnormal = true; }
    if (tidalVolume <= 0) { statusMessage += "WARNING: Tidal volume is invalid.\n"; abnormal = true; }
    if (peep < 0) { statusMessage += "WARNING: PEEP value cannot be negative.\n"; abnormal = true; }
    if (peakPressure < 0) { statusMessage += "WARNING: Peak pressure cannot be negative.\n"; abnormal = true; }
    if (plateauPressure < 0) { statusMessage += "WARNING: Plateau pressure cannot be negative.\n"; abnormal = true; }
    if (plateauPressure > peakPressure && peakPressure > 0) { statusMessage += "WARNING: Plateau pressure is greater than peak pressure.\n"; abnormal = true; }

    if (abnormal) {
        currentStatus = "Alert";
        return false;
    }
    currentStatus = "Stable";
    statusMessage = "Ventilation parameters are within configured limits.";
    return true;
}

void DigitalVentilationSystem::checkVentilationStatus() {
    string msg;
    checkVentilationStatus(msg);
    cout << "\n--- Ventilation Safety Check ---\n" << msg << endl;
}

bool DigitalVentilationSystem::checkAlerts(string& alertMessage) {
    if (ventilatorId == 0) {
        alertMessage = "No ventilator assigned.";
        return false;
    }
    if (!ventilatorConnected) {
        alertMessage = "ALERT: Ventilator disconnected from patient!";
        return true;
    }
    bool alert = false;
    alertMessage = "";
    if (oxygenLevel < 21.0 || oxygenLevel > 100.0) { alertMessage += "ALERT: Abnormal Oxygen Level!\n"; alert = true; }
    if (respiratoryRate <= 0) { alertMessage += "ALERT: Invalid Respiratory Rate!\n"; alert = true; }
    if (tidalVolume <= 0) { alertMessage += "ALERT: Invalid Tidal Volume!\n"; alert = true; }
    if (peakPressure < 0 || plateauPressure < 0) { alertMessage += "ALERT: Invalid Pressure Reading!\n"; alert = true; }
    if (plateauPressure > peakPressure && peakPressure > 0) { alertMessage += "ALERT: Abnormal Pressure Relationship!\n"; alert = true; }
    return alert;
}

void DigitalVentilationSystem::generateAlert() {
    string msg;
    if (checkAlerts(msg)) {
        cout << "\n*** ALERTS DETECTED ***\n" << msg;
    } else {
        cout << "No critical alerts detected.\n";
    }
}

void DigitalVentilationSystem::generateVentilationReport() const {
    if (ventilatorId == 0) {
        cout << "Cannot generate report. No ventilator is assigned.\n";
        return;
    }
    cout << "\n============================================\n";
    cout << "       DIGITAL VENTILATION REPORT\n";
    cout << "============================================\n";
    cout << "Patient ID          : " << patientId << endl;
    cout << "Patient Name        : " << patientName << endl;
    cout << "Ventilator ID       : " << ventilatorId << endl;
    cout << "Ventilation Mode    : " << ventilationMode << endl;
    cout << "Start Time          : " << startTime << endl;
    cout << "\n--- Ventilation Parameters ---\n";
    cout << "Oxygen Level        : " << fixed << setprecision(2) << oxygenLevel << " %\n";
    cout << "Respiratory Rate    : " << respiratoryRate << " breaths/min\n";
    cout << "Tidal Volume        : " << tidalVolume << " mL\n";
    cout << "PEEP                : " << peep << " cmH2O\n";
    cout << "Peak Pressure       : " << peakPressure << " cmH2O\n";
    cout << "Plateau Pressure    : " << plateauPressure << " cmH2O\n";
    cout << "\n--- System Information ---\n";
    cout << "Connection Status   : " << (ventilatorConnected ? "Connected" : "Disconnected") << endl;
    cout << "Current Status      : " << currentStatus << endl;
    cout << "\n--- Safety Assessment ---\n";
    if (currentStatus == "Alert") {
        cout << "Status: ATTENTION REQUIRED\n";
    } else if (currentStatus == "Stable") {
        cout << "Status: STABLE\n";
    } else {
        cout << "Status: " << currentStatus << endl;
    }
    cout << "============================================\n";
}