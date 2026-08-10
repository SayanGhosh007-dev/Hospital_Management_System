#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class DigitalVentilationSystem
{
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
        void assignVentilator();
        void removeVentilator();
        void connectVentilator();
        void disconnectVentilator();
        void updateVentilationData();
        void displayVentilationData();
        void checkVentilationStatus();
        void generateAlert();
        void generateVentilationReport();
};

// Constructor

DigitalVentilationSystem::DigitalVentilationSystem()
{
    patientId = 0;
    patientName = "";

    ventilatorId = 0;

    ventilationMode = "Not Set";

    oxygenLevel = 0.0;
    respiratoryRate = 0.0;
    tidalVolume = 0.0;

    peep = 0.0;
    peakPressure = 0.0;
    plateauPressure = 0.0;

    startTime = "";
    currentStatus = "Inactive";

    ventilatorConnected = false;
}

// Patient/Ventilator Management

void DigitalVentilationSystem::assignVentilator()
{
    if (ventilatorId != 0)
    {
        cout << "A ventilator is already assigned to this patient.\n";
        return;
    }

    cout << "Enter Patient ID: ";
    cin >> patientId;

    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, patientName);

    cout << "Enter Ventilator ID: ";
    cin >> ventilatorId;

    cin.ignore();

    cout << "Enter Ventilation Mode: ";
    getline(cin, ventilationMode);

    cout << "Enter Ventilation Start Time: ";
    getline(cin, startTime);

    currentStatus = "Assigned";

    cout << "Ventilator assigned successfully.\n";
}


void DigitalVentilationSystem::removeVentilator()
{
    if (ventilatorId == 0)
    {
        cout << "No ventilator is currently assigned.\n";
        return;
    }

    if (ventilatorConnected)
    {
        cout << "Disconnect the ventilator before removing it.\n";
        return;
    }

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

    cout << "Ventilator removed successfully.\n";
}

// Connection Management

void DigitalVentilationSystem::connectVentilator()
{
    if (ventilatorId == 0)
    {
        cout << "No ventilator has been assigned.\n";
        return;
    }

    if (ventilatorConnected)
    {
        cout << "Ventilator is already connected.\n";
        return;
    }

    ventilatorConnected = true;
    currentStatus = "Connected";

    cout << "Ventilator connected successfully.\n";
}


void DigitalVentilationSystem::disconnectVentilator()
{
    if (!ventilatorConnected)
    {
        cout << "Ventilator is already disconnected.\n";
        return;
    }

    ventilatorConnected = false;
    currentStatus = "Disconnected";

    cout << "Ventilator disconnected successfully.\n";
}

// Monitoring

void DigitalVentilationSystem::updateVentilationData()
{
    if (!ventilatorConnected)
    {
        cout << "Cannot update ventilation data.\n";
        cout << "Ventilator is not connected.\n";
        return;
    }

    cout << "\n--- Update Ventilation Data ---\n";

    cout << "Enter Oxygen Level (%): ";
    cin >> oxygenLevel;

    cout << "Enter Respiratory Rate (breaths/min): ";
    cin >> respiratoryRate;

    cout << "Enter Tidal Volume (mL): ";
    cin >> tidalVolume;

    cout << "Enter PEEP (cmH2O): ";
    cin >> peep;

    cout << "Enter Peak Pressure (cmH2O): ";
    cin >> peakPressure;

    cout << "Enter Plateau Pressure (cmH2O): ";
    cin >> plateauPressure;

    currentStatus = "Monitoring";

    cout << "Ventilation data updated successfully.\n";
}


void DigitalVentilationSystem::displayVentilationData()
{
    if (ventilatorId == 0)
    {
        cout << "No ventilator information available.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "       VENTILATION DATA\n";
    cout << "========================================\n";

    cout << "Patient ID          : " << patientId << endl;
    cout << "Patient Name        : " << patientName << endl;

    cout << "Ventilator ID       : " << ventilatorId << endl;
    cout << "Ventilation Mode    : " << ventilationMode << endl;

    cout << "Oxygen Level        : "
         << fixed << setprecision(2)
         << oxygenLevel << " %\n";

    cout << "Respiratory Rate    : "
         << respiratoryRate << " breaths/min\n";

    cout << "Tidal Volume        : "
         << tidalVolume << " mL\n";

    cout << "PEEP                : "
         << peep << " cmH2O\n";

    cout << "Peak Pressure       : "
         << peakPressure << " cmH2O\n";

    cout << "Plateau Pressure    : "
         << plateauPressure << " cmH2O\n";

    cout << "Start Time          : " << startTime << endl;

    cout << "Connection Status   : "
         << (ventilatorConnected ? "Connected" : "Disconnected")
         << endl;

    cout << "Current Status      : " << currentStatus << endl;

    cout << "========================================\n";
}

// Safety / Alert

void DigitalVentilationSystem::checkVentilationStatus()
{
    if (!ventilatorConnected)
    {
        cout << "WARNING: Ventilator is not connected.\n";
        currentStatus = "Disconnected";
        return;
    }

    bool abnormalCondition = false;

    cout << "\n--- Ventilation Safety Check ---\n";

    // Oxygen level check
    if (oxygenLevel < 21.0 || oxygenLevel > 100.0)
    {
        cout << "WARNING: Oxygen level is outside the valid range.\n";
        abnormalCondition = true;
    }

    // Respiratory rate check
    if (respiratoryRate <= 0)
    {
        cout << "WARNING: Respiratory rate is invalid.\n";
        abnormalCondition = true;
    }

    // Tidal volume check
    if (tidalVolume <= 0)
    {
        cout << "WARNING: Tidal volume is invalid.\n";
        abnormalCondition = true;
    }

    // PEEP check
    if (peep < 0)
    {
        cout << "WARNING: PEEP value cannot be negative.\n";
        abnormalCondition = true;
    }

    // Peak pressure check
    if (peakPressure < 0)
    {
        cout << "WARNING: Peak pressure cannot be negative.\n";
        abnormalCondition = true;
    }

    // Plateau pressure check
    if (plateauPressure < 0)
    {
        cout << "WARNING: Plateau pressure cannot be negative.\n";
        abnormalCondition = true;
    }

    // Important pressure relationship
    if (plateauPressure > peakPressure && peakPressure > 0)
    {
        cout << "WARNING: Plateau pressure is greater than peak pressure.\n";
        abnormalCondition = true;
    }

    if (abnormalCondition)
    {
        currentStatus = "Alert";
        cout << "Ventilation system requires attention.\n";
    }
    else
    {
        currentStatus = "Stable";
        cout << "Ventilation parameters are within the configured limits.\n";
    }
}


void DigitalVentilationSystem::generateAlert()
{
    if (ventilatorId == 0)
    {
        cout << "No ventilator assigned. No alert can be generated.\n";
        return;
    }

    if (!ventilatorConnected)
    {
        cout << "\n*** ALERT ***\n";
        cout << "Ventilator disconnected from patient.\n";
        return;
    }

    bool alertGenerated = false;

    if (oxygenLevel < 21.0 || oxygenLevel > 100.0)
    {
        cout << "\n*** ALERT: Abnormal Oxygen Level ***\n";
        alertGenerated = true;
    }

    if (respiratoryRate <= 0)
    {
        cout << "\n*** ALERT: Invalid Respiratory Rate ***\n";
        alertGenerated = true;
    }

    if (tidalVolume <= 0)
    {
        cout << "\n*** ALERT: Invalid Tidal Volume ***\n";
        alertGenerated = true;
    }

    if (peakPressure < 0 || plateauPressure < 0)
    {
        cout << "\n*** ALERT: Invalid Pressure Reading ***\n";
        alertGenerated = true;
    }

    if (plateauPressure > peakPressure && peakPressure > 0)
    {
        cout << "\n*** ALERT: Abnormal Pressure Relationship ***\n";
        alertGenerated = true;
    }

    if (!alertGenerated)
    {
        cout << "No critical alerts detected.\n";
    }
}

// Report

void DigitalVentilationSystem::generateVentilationReport()
{
    if (ventilatorId == 0)
    {
        cout << "Cannot generate report.\n";
        cout << "No ventilator is assigned.\n";
        return;
    }

    cout << "\n";
    cout << "============================================\n";
    cout << "       DIGITAL VENTILATION REPORT\n";
    cout << "============================================\n";

    cout << "Patient ID          : " << patientId << endl;
    cout << "Patient Name        : " << patientName << endl;

    cout << "Ventilator ID       : " << ventilatorId << endl;
    cout << "Ventilation Mode    : " << ventilationMode << endl;
    cout << "Start Time          : " << startTime << endl;

    cout << "\n--- Ventilation Parameters ---\n";

    cout << "Oxygen Level        : "
         << fixed << setprecision(2)
         << oxygenLevel << " %\n";

    cout << "Respiratory Rate    : "
         << respiratoryRate << " breaths/min\n";

    cout << "Tidal Volume        : "
         << tidalVolume << " mL\n";

    cout << "PEEP                : "
         << peep << " cmH2O\n";

    cout << "Peak Pressure       : "
         << peakPressure << " cmH2O\n";

    cout << "Plateau Pressure    : "
         << plateauPressure << " cmH2O\n";

    cout << "\n--- System Information ---\n";

    cout << "Connection Status   : "
         << (ventilatorConnected ? "Connected" : "Disconnected")
         << endl;

    cout << "Current Status      : "
         << currentStatus << endl;

    cout << "\n--- Safety Assessment ---\n";

    if (currentStatus == "Alert")
    {
        cout << "Status: ATTENTION REQUIRED\n";
    }
    else if (currentStatus == "Stable")
    {
        cout << "Status: STABLE\n";
    }
    else
    {
        cout << "Status: " << currentStatus << endl;
    }

    cout << "============================================\n";
}