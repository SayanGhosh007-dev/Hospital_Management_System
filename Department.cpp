#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Department {
private:
    int departmentId;
    string departmentName;
    string location;
    string headDoctor;
    int numberOfDoctors;
    int numberOfBeds;

public:
    Department();
    Department(int id, const string& name, const string& loc, const string& head, int docs, int beds);

    int getDepartmentId() const;
    string getDepartmentName() const;
    string getLocation() const;
    string getHeadDoctor() const;
    int getNumberOfDoctors() const;
    int getNumberOfBeds() const;

    void setDepartmentId(int id);
    void setDepartmentName(const string& name);
    void setLocation(const string& loc);
    void setHeadDoctor(const string& head);
    void setNumberOfDoctors(int docs);
    void setNumberOfBeds(int beds);

    void addDepartment();
    void displayDepartment() const;
    void updateDepartment();
    void removeDepartment();
};

// Unique prefix helpers to avoid collision when modules are textually included in main.cpp
static int dept_getValidInteger(const string& prompt) {
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

static string dept_getNonEmptyString(const string& prompt) {
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

Department::Department() 
    : departmentId(0), numberOfDoctors(0), numberOfBeds(0), departmentName(""), headDoctor(""), location("") {}

Department::Department(int id, const string& name, const string& loc, const string& head, int docs, int beds)
    : departmentId(id), departmentName(name), location(loc), headDoctor(head), numberOfDoctors(docs), numberOfBeds(beds) {}

int Department::getDepartmentId() const { return departmentId; }
string Department::getDepartmentName() const { return departmentName; }
string Department::getLocation() const { return location; }
string Department::getHeadDoctor() const { return headDoctor; }
int Department::getNumberOfDoctors() const { return numberOfDoctors; }
int Department::getNumberOfBeds() const { return numberOfBeds; }

void Department::setDepartmentId(int id) { departmentId = id; }
void Department::setDepartmentName(const string& name) { departmentName = name; }
void Department::setLocation(const string& loc) { location = loc; }
void Department::setHeadDoctor(const string& head) { headDoctor = head; }
void Department::setNumberOfDoctors(int docs) { if (docs >= 0) numberOfDoctors = docs; }
void Department::setNumberOfBeds(int beds) { if (beds >= 0) numberOfBeds = beds; }

void Department::addDepartment() {
    cout << "\n===== ADD DEPARTMENT DETAILS =====\n";
    departmentId = dept_getValidInteger("Enter Department Id: ");
    departmentName = dept_getNonEmptyString("Enter Department Name: ");
    location = dept_getNonEmptyString("Enter Department Location: ");
    headDoctor = dept_getNonEmptyString("Enter Head Doctor Name: ");
    numberOfDoctors = dept_getValidInteger("Enter Number Of Doctors: ");
    numberOfBeds = dept_getValidInteger("Enter Number Of Beds: ");
    cout << "\nDepartment added successfully!\n";
}

void Department::displayDepartment() const {
    cout << "\n====== DEPARTMENT DETAILS ======\n";
    cout << "Department Id: " << departmentId << endl;
    cout << "Department Name: " << departmentName << endl;
    cout << "Department Location: " << location << endl;
    cout << "Head Doctor Name: " << headDoctor << endl;
    cout << "Number Of Doctors: " << numberOfDoctors << endl;
    cout << "Number Of Beds: " << numberOfBeds << endl;
}

void Department::updateDepartment() {
    int checkId = dept_getValidInteger("\nEnter Department Id to verify: ");
    if (checkId == departmentId) {
        cout << "\n===== UPDATE DEPARTMENT DETAILS =====\n";
        departmentName = dept_getNonEmptyString("Enter Department Name: ");
        location = dept_getNonEmptyString("Enter Department Location: ");
        headDoctor = dept_getNonEmptyString("Enter Head Doctor Name: ");
        numberOfDoctors = dept_getValidInteger("Enter Number Of Doctors: ");
        numberOfBeds = dept_getValidInteger("Enter Number Of Beds: ");
        cout << "\nDepartment updated successfully!\n";
    } else {
        cout << "\nDepartment Id not found.\n";
    }
}

void Department::removeDepartment() {
    int checkId = dept_getValidInteger("\nEnter Department Id to verify: ");
    if (checkId == departmentId) {
        departmentId = 0;
        departmentName = "";
        location = "";
        headDoctor = "";
        numberOfDoctors = 0;
        numberOfBeds = 0;
        cout << "\nDepartment removed successfully!\n";
    } else {
        cout << "\nDepartment Id not found.\n";
    }
}