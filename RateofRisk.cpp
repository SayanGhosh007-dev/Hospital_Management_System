#include <iostream>
#include <string>
#include <limits>

using namespace std;

class RateOfRisk {
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
    RateOfRisk(int rId, int pAge, int rLevel, int rScore, const string& pId,
               const string& pName, const string& pCase, const string& pDisease);

    // Getters
    int getRiskId() const;
    int getAge() const;
    int getRiskLevel() const;
    int getRiskScore() const;
    string getPatientId() const;
    string getPatientName() const;
    string getPatientCase() const;
    string getDisease() const;

    // Setters
    void setRiskId(int id);
    void setAge(int a);
    void setRiskLevel(int level);
    void setRiskScore(int score);
    void setPatientId(const string& id);
    void setPatientName(const string& name);
    void setPatientCase(const string& pCase);
    void setDisease(const string& d);

    // Operations
    string getRiskLevelString() const;

    // Interactive functions (kept for backward compatibility)
    void setPatientDetails();
    void calculateRisk();
    void displayRisk();
    void updateRisk();
};

// Wrap helpers in anonymous namespace to avoid translation unit linkage collisions
namespace {
    int getValidInteger(const string& prompt, int minVal = 0, int maxVal = numeric_limits<int>::max()) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (value >= minVal && value <= maxVal) {
                    return value;
                }
                cout << "Value must be between " << minVal << " and " << maxVal << ". Please try again.\n";
            } else {
                cout << "Invalid numeric input. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    string getNonEmptyString(const string& prompt) {
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
}

RateOfRisk::RateOfRisk()
    : riskId(0), age(0), riskLevel(0), riskScore(0),
      patientId(""), patientName(""), patientCase(""), disease("") {}

RateOfRisk::RateOfRisk(int rId, int pAge, int rLevel, int rScore, const string& pId,
                       const string& pName, const string& pCase, const string& pDisease)
    : riskId(rId), age(pAge), riskLevel(rLevel), riskScore(rScore),
      patientId(pId), patientName(pName), patientCase(pCase), disease(pDisease) {}

int RateOfRisk::getRiskId() const { return riskId; }
int RateOfRisk::getAge() const { return age; }
int RateOfRisk::getRiskLevel() const { return riskLevel; }
int RateOfRisk::getRiskScore() const { return riskScore; }
string RateOfRisk::getPatientId() const { return patientId; }
string RateOfRisk::getPatientName() const { return patientName; }
string RateOfRisk::getPatientCase() const { return patientCase; }
string RateOfRisk::getDisease() const { return disease; }

void RateOfRisk::setRiskId(int id) { riskId = id; }
void RateOfRisk::setAge(int a) { if (a >= 0) age = a; }
void RateOfRisk::setRiskLevel(int level) { if (level >= 1 && level <= 5) riskLevel = level; }
void RateOfRisk::setRiskScore(int score) { if (score >= 0) riskScore = score; }
void RateOfRisk::setPatientId(const string& id) { patientId = id; }
void RateOfRisk::setPatientName(const string& name) { patientName = name; }
void RateOfRisk::setPatientCase(const string& pCase) { patientCase = pCase; }
void RateOfRisk::setDisease(const string& d) { disease = d; }

string RateOfRisk::getRiskLevelString() const {
    switch (riskLevel) {
        case 1: return "Very Low Risk";
        case 2: return "Low Risk";
        case 3: return "Medium Condition";
        case 4: return "High Risk";
        case 5: return "Critical Condition";
        default: return "Invalid Risk Level";
    }
}

void RateOfRisk::setPatientDetails() {
    cout << "\n===== ADD PATIENT DETAILS =====\n";
    patientId = getNonEmptyString("Enter Patient ID: ");
    patientName = getNonEmptyString("Enter Patient Name: ");
    age = getValidInteger("Enter Patient Age: ");
    patientCase = getNonEmptyString("Enter Patient Case: ");
    disease = getNonEmptyString("Enter Disease: ");
    cout << "\nPatient details added successfully!\n";
}

void RateOfRisk::calculateRisk() {
    cout << "\n=============================================\n";
    cout << "              LEVEL OF RISK\n";
    cout << "=============================================\n";
    riskId = getValidInteger("Enter Risk ID: ");
    cout << "\n";
    cout << "1. Very Low Risk\n";
    cout << "2. Low Risk\n";
    cout << "3. Medium Condition\n";
    cout << "4. High Risk\n";
    cout << "5. Critical Condition\n";
    riskLevel = getValidInteger("\nEnter Risk Level (1-5): ", 1, 5);
    riskScore = getValidInteger("Enter Risk Score: ");
    cout << "\nRisk details added successfully!\n";
}

void RateOfRisk::displayRisk() {
    string checkId = getNonEmptyString("\nEnter Patient ID: ");
    if (checkId == patientId) {
        cout << "\n========== PATIENT RISK DETAILS ==========\n";
        cout << "Patient ID       : " << patientId << endl;
        cout << "Patient Name     : " << patientName << endl;
        cout << "Patient Age      : " << age << endl;
        cout << "Patient Case     : " << patientCase << endl;
        cout << "Disease          : " << disease << endl;
        cout << "Risk ID          : " << riskId << endl;
        cout << "Risk Level       : " << getRiskLevelString() << endl;
        cout << "Risk Score       : " << riskScore << endl;
    } else {
        cout << "Invalid Patient ID. Check the ID again.\n";
    }
}

void RateOfRisk::updateRisk() {
    string checkId = getNonEmptyString("\nEnter Patient ID: ");
    if (checkId == patientId) {
        cout << "\n===== UPDATE PATIENT DETAILS =====\n";
        patientName = getNonEmptyString("Enter Patient Name: ");
        age = getValidInteger("Enter Patient Age: ");
        patientCase = getNonEmptyString("Enter Patient Case: ");
        disease = getNonEmptyString("Enter Disease: ");
        cout << "\n===== UPDATE RISK DETAILS =====\n";
        riskLevel = getValidInteger("Enter Risk Level (1-5): ", 1, 5);
        riskScore = getValidInteger("Enter Risk Score: ");
        cout << "\nPatient risk details updated successfully!\n";
    } else {
        cout << "Invalid Patient ID. Check the ID again.\n";
    }
}
