#include <iostream>
#include <string>
using namespace std;

class Department
{
private:
    int departmentId;
    int numberOfDoctors;
    int numberOfBeds;
    string departmentName;
    string headDoctor;
    string location;

public:
    Department();

    void addDepartment();
    void displayDepartment();
    void updateDepartment();
    void removeDepartment();
};

Department::Department()
{
    departmentId = 0;
    numberOfDoctors = 0;
    numberOfBeds = 0;
    departmentName = "";
    headDoctor = "";
    location = "";
}

void Department::addDepartment()
{
    cout << "\n===== ADD DEPARTMENT DETAILS =====\n";

    cout << "Enter Department Id: ";
    cin >> departmentId;
    cin.ignore();

    cout << "Enter Department Name: ";
    getline(cin, departmentName);

    cout << "Enter Department Location: ";
    getline(cin, location);

    cout << "Enter Head Doctor Name: ";
    getline(cin, headDoctor);

    cout << "Enter Number Of Doctors: ";
    cin >> numberOfDoctors;

    cout << "Enter Number Of Beds: ";
    cin >> numberOfBeds;

    cout << "\nDepartment added successfully!\n";
}

void Department::displayDepartment()
{
    cout << "\n====== DEPARTMENT DETAILS ======\n";

    cout << "Department Id: " << departmentId << endl;
    cout << "Department Name: " << departmentName << endl;
    cout << "Department Location: " << location << endl;
    cout << "Head Doctor Name: " << headDoctor << endl;
    cout << "Number Of Doctors: " << numberOfDoctors << endl;
    cout << "Number Of Beds: " << numberOfBeds << endl;
}

void Department::updateDepartment()
{
    int checkId;

    cout << "\nEnter Department Id: ";
    cin >> checkId;
    cin.ignore();

    if (checkId == departmentId)
    {
        cout << "\n===== UPDATE DEPARTMENT DETAILS =====\n";

        cout << "Enter Department Id: ";
        cin >> departmentId;
        cin.ignore();

        cout << "Enter Department Name: ";
        getline(cin, departmentName);

        cout << "Enter Department Location: ";
        getline(cin, location);

        cout << "Enter Head Doctor Name: ";
        getline(cin, headDoctor);

        cout << "Enter Number Of Doctors: ";
        cin >> numberOfDoctors;

        cout << "Enter Number Of Beds: ";
        cin >> numberOfBeds;

        cout << "\nDepartment updated successfully!\n";
    }
    else
    {
        cout << "\nDepartment Id not found.\n";
    }
}

void Department::removeDepartment()
{
    int checkId;

    cout << "\nEnter Department Id: ";
    cin >> checkId;

    if (checkId == departmentId)
    {
        departmentId = 0;
        departmentName = "";
        location = "";
        headDoctor = "";
        numberOfDoctors = 0;
        numberOfBeds = 0;

        cout << "\nDepartment removed successfully!\n";
    }
    else
    {
        cout << "\nDepartment Id not found.\n";
    }
}