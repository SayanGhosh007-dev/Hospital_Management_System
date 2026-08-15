#include<iostream>
#include<string>

using namespace std;

class MortuaryManagement
{
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

    void admitBody();
    void recordDeathDetails();
    void identifyBody();
    void releaseBody();
    void displayMortuaryRecord();
    void updateMortuaryRecord();
};

MortuaryManagement::MortuaryManagement()
{
    mortuaryId = 0;
    age = 0;
    identificationStatus = "Not Identified";
    releaseStatus = "Not Released";
}

void MortuaryManagement::admitBody()
{
    cout << "\n====== ADD BODY DETAILS ======\n";

    cout << "Enter Mortuary Id : ";
    cin >> mortuaryId;
    cin.ignore();

    cout << "Enter Deceased Person Id : ";
    cin >> deceasedId;
    cin.ignore();

    cout << "Enter Deceased Person Name : ";
    cin >> deceasedName;
    cin.ignore();

    cout << "Enter Deceased Person Age : ";
    cin >> age;
    cin.ignore();

    cout << "Enter Deceased Person Gender : ";
    cin >> gender;
    cin.ignore();

    cout << "Enter Date Of Admission : ";
    cin >> dateOfAdmission;
    cin.ignore();

    cout << "\nBody Admitted Successfully.\n";
}

void MortuaryManagement::recordDeathDetails()
{
    cout << "\n====== ENTER DEATH DETAILS ======\n";

    cout << "Enter Date Of Death : ";
    cin >> dateOfDeath;
    cin.ignore();

    cout << "Enter Cause Of Death : ";
    cin >> causeOfDeath;
    cin.ignore();

    cout << "\nDeath Details Recorded Successfully.\n";
}

void MortuaryManagement::identifyBody()
{
    cout << "\n====== IDENTIFY BODY ======\n";

    cout << "Enter Identification Status : ";
    cin >> identificationStatus;
    cin.ignore();

    cout << "\nIdentification Status Updated Successfully.\n";
}

void MortuaryManagement::releaseBody()
{
    cout << "\n====== RELEASE BODY ======\n";

    if (identificationStatus == "Identified" ||
        identificationStatus == "identified")
    {
        cout << "Enter Release Status : ";
        cin >> releaseStatus;
        cin.ignore();

        cout << "\nBody Release Status Updated Successfully.\n";
    }
    else
    {
        cout << "\nBody Not Identified. Please Identify The Body First.\n";
    }
}

void MortuaryManagement::displayMortuaryRecord()
{
    cout << "\n====== MORTUARY RECORD ======\n";

    cout << "Mortuary Id           : " << mortuaryId << endl;
    cout << "Deceased Person Id    : " << deceasedId << endl;
    cout << "Deceased Person Name  : " << deceasedName << endl;
    cout << "Deceased Person Age   : " << age << endl;
    cout << "Deceased Person Gender: " << gender << endl;
    cout << "Date Of Admission     : " << dateOfAdmission << endl;
    cout << "Date Of Death        : " << dateOfDeath << endl;
    cout << "Cause Of Death        : " << causeOfDeath << endl;
    cout << "Identification Status : " << identificationStatus << endl;
    cout << "Release Status        : " << releaseStatus << endl;
}

void MortuaryManagement::updateMortuaryRecord()
{
    int checkId;

    cout << "\nEnter Mortuary Id To Update : ";
    cin >> checkId;
    cin.ignore();

    if (checkId == mortuaryId)
    {
        cout << "\n====== UPDATE MORTUARY RECORD ======\n";

        cout << "Enter Deceased Person Id : ";
        cin >> deceasedId;
        cin.ignore();

        cout << "Enter Deceased Person Name : ";
        cin >> deceasedName;
        cin.ignore();

        cout << "Enter Deceased Person Age : ";
        cin >> age;
        cin.ignore();

        cout << "Enter Deceased Person Gender : ";
        cin >> gender;
        cin.ignore();

        cout << "Enter Date Of Admission : ";
        cin >> dateOfAdmission;
        cin.ignore();

        cout << "Enter Date Of Death : ";
        cin >> dateOfDeath;
        cin.ignore();

        cout << "Enter Cause Of Death : ";
        cin >> causeOfDeath;
        cin.ignore();

        cout << "Enter Identification Status : ";
        cin >> identificationStatus;
        cin.ignore();

        cout << "Enter Release Status : ";
        cin >> releaseStatus;
        cin.ignore();

        cout << "\nRecord Updated Successfully.\n";
    }
    else
    {
        cout << "\nId Doesn't Match. Please Check Again.\n";
    }
}