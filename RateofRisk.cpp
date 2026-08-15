#include <iostream>
#include <string>
using namespace std;

class RateOfRisk
{
private:
    int riskId;
    int age;
    int riskLevel;
    int riskScore;
    
    string patientId;
    string patientName;
    string patientCase;
    string disease;

public:
    RateOfRisk();

    void setPatientDetails();
    void calculateRisk();
    void displayRisk();
    void updateRisk();
};


// Constructor
RateOfRisk::RateOfRisk()
{
    riskId = 0;
    age = 0;
    riskLevel = 0;
    riskScore = 0;
}


// Set Patient Details
void RateOfRisk::setPatientDetails()
{
    cout << "\n===== ADD PATIENT DETAILS =====\n";

    cout << "Enter Patient ID: ";
    cin >> patientId;
    cin.ignore();

    cout << "Enter Patient Name: ";
    getline(cin, patientName);

    cout << "Enter Patient Age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter Patient Case: ";
    getline(cin, patientCase);

    cout << "Enter Disease: ";
    getline(cin, disease);

    cout << "\nPatient details added successfully!\n";
}


// Calculate / Set Risk
void RateOfRisk::calculateRisk()
{
    cout << "\n=============================================\n";
    cout << "              LEVEL OF RISK\n";
    cout << "=============================================\n";

    cout << "Enter Risk ID: ";
    cin >> riskId;

    cout << "\n";
    cout << "1. Very Low Risk\n";
    cout << "2. Low Risk\n";
    cout << "3. Medium Condition\n";
    cout << "4. High Risk\n";
    cout << "5. Critical Condition\n";

    cout << "\nEnter Risk Level: ";
    cin >> riskLevel;

    cout << "Enter Risk Score: ";
    cin >> riskScore;

    cout << "\nRisk details added successfully!\n";
}


// Display Risk
void RateOfRisk::displayRisk()
{
    string checkId;

    cout << "\nEnter Patient ID: ";
    cin >> checkId;

    if (checkId == patientId)
    {
        cout << "\n========== PATIENT RISK DETAILS ==========\n";

        cout << "Patient ID       : " << patientId << endl;
        cout << "Patient Name     : " << patientName << endl;
        cout << "Patient Age      : " << age << endl;
        cout << "Patient Case     : " << patientCase << endl;
        cout << "Disease          : " << disease << endl;
        cout << "Risk ID          : " << riskId << endl;

        cout << "Risk Level       : ";

        switch (riskLevel)
        {
            case 1:
                cout << "Very Low Risk";
                break;

            case 2:
                cout << "Low Risk";
                break;

            case 3:
                cout << "Medium Condition";
                break;

            case 4:
                cout << "High Risk";
                break;

            case 5:
                cout << "Critical Condition";
                break;

            default:
                cout << "Invalid Risk Level";
        }

        cout << endl;
        cout << "Risk Score       : " << riskScore << endl;
    }
    else
    {
        cout << "Invalid Patient ID. Check the ID again.\n";
    }
}


// Update Risk
void RateOfRisk::updateRisk()
{
    string checkId;

    cout << "\nEnter Patient ID: ";
    cin >> checkId;

    if (checkId == patientId)
    {
        cout << "\n===== UPDATE PATIENT DETAILS =====\n";

        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, patientName);

        cout << "Enter Patient Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Patient Case: ";
        getline(cin, patientCase);

        cout << "Enter Disease: ";
        getline(cin, disease);

        cout << "\n===== UPDATE RISK DETAILS =====\n";

        cout << "Enter Risk Level (1-5): ";
        cin >> riskLevel;

        cout << "Enter Risk Score: ";
        cin >> riskScore;

        cout << "\nPatient risk details updated successfully!\n";
    }
    else
    {
        cout << "Invalid Patient ID. Check the ID again.\n";
    }
}
