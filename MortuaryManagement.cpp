#include <iostream>
#include <string>
#include <limits>

using namespace std;

class MortuaryManagement {
private:
    int mortuaryId;
    int age;
    string deceasedId;
    string deceasedName;
    string gender;
    string dateOfDeath;
    string causeOfDeath;
    string dateOfAdmission;
    string identificationStatus;
    string releaseStatus;

public:
    MortuaryManagement();
    MortuaryManagement(int mId, int mAge, const string& decId, const string& decName, const string& mGender,
                       const string& deathDate, const string& deathCause, const string& admDate,
                       const string& identStatus, const string& relStatus);

    // Getters
    int getMortuaryId() const;
    int getAge() const;
    string getDeceasedId() const;
    string getDeceasedName() const;
    string getGender() const;
    string getDateOfDeath() const;
    string getCauseOfDeath() const;
    string getDateOfAdmission() const;
    string getIdentificationStatus() const;
    string getReleaseStatus() const;

    // Setters
    void setMortuaryId(int id);
    void setAge(int a);
    void setDeceasedId(const string& id);
    void setDeceasedName(const string& name);
    void setGender(const string& g);
    void setDateOfDeath(const string& d);
    void setCauseOfDeath(const string& c);
    void setDateOfAdmission(const string& d);
    void setIdentificationStatus(const string& status);
    void setReleaseStatus(const string& status);

    // Interactive functions (kept for backward compatibility)
    void admitBody();
    void recordDeathDetails();
    void identifyBody();
    void releaseBody();
    void displayMortuaryRecord() const;
    void updateMortuaryRecord();
};

static int mort_getValidInteger(const string& prompt) {
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

static string mort_getNonEmptyString(const string& prompt) {
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

MortuaryManagement::MortuaryManagement()
    : mortuaryId(0), age(0), deceasedId(""), deceasedName(""), gender(""),
      dateOfDeath(""), causeOfDeath(""), dateOfAdmission(""),
      identificationStatus("Not Identified"), releaseStatus("Not Released") {}

MortuaryManagement::MortuaryManagement(int mId, int mAge, const string& decId, const string& decName, const string& mGender,
                                       const string& deathDate, const string& deathCause, const string& admDate,
                                       const string& identStatus, const string& relStatus)
    : mortuaryId(mId), age(mAge), deceasedId(decId), deceasedName(decName), gender(mGender),
      dateOfDeath(deathDate), causeOfDeath(deathCause), dateOfAdmission(admDate),
      identificationStatus(identStatus), releaseStatus(relStatus) {}

int MortuaryManagement::getMortuaryId() const { return mortuaryId; }
int MortuaryManagement::getAge() const { return age; }
string MortuaryManagement::getDeceasedId() const { return deceasedId; }
string MortuaryManagement::getDeceasedName() const { return deceasedName; }
string MortuaryManagement::getGender() const { return gender; }
string MortuaryManagement::getDateOfDeath() const { return dateOfDeath; }
string MortuaryManagement::getCauseOfDeath() const { return causeOfDeath; }
string MortuaryManagement::getDateOfAdmission() const { return dateOfAdmission; }
string MortuaryManagement::getIdentificationStatus() const { return identificationStatus; }
string MortuaryManagement::getReleaseStatus() const { return releaseStatus; }

void MortuaryManagement::setMortuaryId(int id) { mortuaryId = id; }
void MortuaryManagement::setAge(int a) { if (a >= 0) age = a; }
void MortuaryManagement::setDeceasedId(const string& id) { deceasedId = id; }
void MortuaryManagement::setDeceasedName(const string& name) { deceasedName = name; }
void MortuaryManagement::setGender(const string& g) { gender = g; }
void MortuaryManagement::setDateOfDeath(const string& d) { dateOfDeath = d; }
void MortuaryManagement::setCauseOfDeath(const string& c) { causeOfDeath = c; }
void MortuaryManagement::setDateOfAdmission(const string& d) { dateOfAdmission = d; }
void MortuaryManagement::setIdentificationStatus(const string& status) { identificationStatus = status; }
void MortuaryManagement::setReleaseStatus(const string& status) { releaseStatus = status; }

void MortuaryManagement::admitBody() {
    cout << "\n====== ADD BODY DETAILS ======\n";
    mortuaryId = mort_getValidInteger("Enter Mortuary Id : ");
    deceasedId = mort_getNonEmptyString("Enter Deceased Person Id : ");
    deceasedName = mort_getNonEmptyString("Enter Deceased Person Name : ");
    age = mort_getValidInteger("Enter Deceased Person Age : ");
    gender = mort_getNonEmptyString("Enter Deceased Person Gender : ");
    dateOfAdmission = mort_getNonEmptyString("Enter Date Of Admission : ");
    cout << "\nBody Admitted Successfully.\n";
}

void MortuaryManagement::recordDeathDetails() {
    cout << "\n====== ENTER DEATH DETAILS ======\n";
    dateOfDeath = mort_getNonEmptyString("Enter Date Of Death : ");
    causeOfDeath = mort_getNonEmptyString("Enter Cause Of Death : ");
    cout << "\nDeath Details Recorded Successfully.\n";
}

void MortuaryManagement::identifyBody() {
    cout << "\n====== IDENTIFY BODY ======\n";
    identificationStatus = mort_getNonEmptyString("Enter Identification Status : ");
    cout << "\nIdentification Status Updated Successfully.\n";
}

void MortuaryManagement::releaseBody() {
    cout << "\n====== RELEASE BODY ======\n";
    if (identificationStatus == "Identified" || identificationStatus == "identified") {
        releaseStatus = mort_getNonEmptyString("Enter Release Status : ");
        cout << "\nBody Release Status Updated Successfully.\n";
    } else {
        cout << "\nBody Not Identified. Please Identify The Body First.\n";
    }
}

void MortuaryManagement::displayMortuaryRecord() const {
    cout << "\n====== MORTUARY RECORD ======\n";
    cout << "Mortuary Id           : " << mortuaryId << endl;
    cout << "Deceased Person Id    : " << deceasedId << endl;
    cout << "Deceased Person Name  : " << deceasedName << endl;
    cout << "Deceased Person Age   : " << age << endl;
    cout << "Deceased Person Gender: " << gender << endl;
    cout << "Date Of Admission     : " << dateOfAdmission << endl;
    cout << "Date Of Death         : " << dateOfDeath << endl;
    cout << "Cause Of Death        : " << causeOfDeath << endl;
    cout << "Identification Status : " << identificationStatus << endl;
    cout << "Release Status        : " << releaseStatus << endl;
}

void MortuaryManagement::updateMortuaryRecord() {
    int checkId = mort_getValidInteger("\nEnter Mortuary Id To Update : ");
    if (checkId == mortuaryId) {
        cout << "\n====== UPDATE MORTUARY RECORD ======\n";
        deceasedId = mort_getNonEmptyString("Enter Deceased Person Id : ");
        deceasedName = mort_getNonEmptyString("Enter Deceased Person Name : ");
        age = mort_getValidInteger("Enter Deceased Person Age : ");
        gender = mort_getNonEmptyString("Enter Deceased Person Gender : ");
        dateOfAdmission = mort_getNonEmptyString("Enter Date Of Admission : ");
        dateOfDeath = mort_getNonEmptyString("Enter Date Of Death : ");
        causeOfDeath = mort_getNonEmptyString("Enter Cause Of Death : ");
        identificationStatus = mort_getNonEmptyString("Enter Identification Status : ");
        releaseStatus = mort_getNonEmptyString("Enter Release Status : ");
        cout << "\nRecord Updated Successfully.\n";
    } else {
        cout << "\nId Doesn't Match. Please Check Again.\n";
    }
}