#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

class PunchInOut {
private:
    int employeeId;
    float totalWorkingHours;
    string employeeName;
    string employeeRole;
    string department;
    string punchInDate;
    string punchInTime;
    string punchOutDate;
    string punchOutTime;
    bool isPunchedIn;

public:
    PunchInOut();
    PunchInOut(int empId, const string& name, const string& role, const string& dept);

    // Getters
    int getEmployeeId() const;
    float getTotalWorkingHours() const;
    string getEmployeeName() const;
    string getEmployeeRole() const;
    string getDepartment() const;
    string getPunchInDate() const;
    string getPunchInTime() const;
    string getPunchOutDate() const;
    string getPunchOutTime() const;
    bool checkPunchInStatus() const;

    // Setters
    void setEmployeeId(int id);
    void setEmployeeName(const string& name);
    void setEmployeeRole(const string& role);
    void setDepartment(const string& dept);

    // Punch Operations
    void punchIn();
    void punchOut();
    void calculateWorkingHours();
    void resetAttendance();

    // Display / I/O Operations (kept for compatibility)
    void displayAttendance() const;
    void displayPunchInDetails() const;
    void displayPunchOutDetails() const;
    void setEmployeeDetails();
    void getEmployeeDetails() const;
};

static int punch_getValidInteger(const string& prompt) {
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

static string punch_getNonEmptyString(const string& prompt) {
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

PunchInOut::PunchInOut()
    : employeeId(0), totalWorkingHours(0.0f), employeeName(""), employeeRole(""),
      department(""), punchInDate(""), punchInTime(""), punchOutDate(""),
      punchOutTime(""), isPunchedIn(false) {}

PunchInOut::PunchInOut(int empId, const string& name, const string& role, const string& dept)
    : employeeId(empId), totalWorkingHours(0.0f), employeeName(name), employeeRole(role),
      department(dept), punchInDate(""), punchInTime(""), punchOutDate(""),
      punchOutTime(""), isPunchedIn(false) {}

int PunchInOut::getEmployeeId() const { return employeeId; }
float PunchInOut::getTotalWorkingHours() const { return totalWorkingHours; }
string PunchInOut::getEmployeeName() const { return employeeName; }
string PunchInOut::getEmployeeRole() const { return employeeRole; }
string PunchInOut::getDepartment() const { return department; }
string PunchInOut::getPunchInDate() const { return punchInDate; }
string PunchInOut::getPunchInTime() const { return punchInTime; }
string PunchInOut::getPunchOutDate() const { return punchOutDate; }
string PunchInOut::getPunchOutTime() const { return punchOutTime; }
bool PunchInOut::checkPunchInStatus() const { return isPunchedIn; }

void PunchInOut::setEmployeeId(int id) { employeeId = id; }
void PunchInOut::setEmployeeName(const string& name) { employeeName = name; }
void PunchInOut::setEmployeeRole(const string& role) { employeeRole = role; }
void PunchInOut::setDepartment(const string& dept) { department = dept; }

void PunchInOut::punchIn() {
    if (isPunchedIn) {
        cout << "\nEmployee is already punched in.\n";
        cout << "Punch In Time: " << punchInTime << endl;
        return;
    }
    time_t now = time(0);
    tm *localTime = localtime(&now);
    char dateBuffer[11];
    char timeBuffer[9];
    strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", localTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", localTime);
    punchInDate = dateBuffer;
    punchInTime = timeBuffer;
    punchOutDate = "";
    punchOutTime = "";
    totalWorkingHours = 0.0f;
    isPunchedIn = true;
    cout << "\n====================================\n";
    cout << "          PUNCH IN SUCCESSFUL\n";
    cout << "====================================\n";
    cout << "Employee ID   : " << employeeId << endl;
    cout << "Employee Name : " << employeeName << endl;
    cout << "Date          : " << punchInDate << endl;
    cout << "Time          : " << punchInTime << endl;
    cout << "====================================\n";
}

void PunchInOut::punchOut() {
    if (!isPunchedIn) {
        cout << "\nEmployee is not currently punched in.\n";
        cout << "Please punch in first.\n";
        return;
    }
    time_t now = time(0);
    tm *localTime = localtime(&now);
    char dateBuffer[11];
    char timeBuffer[9];
    strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", localTime);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", localTime);
    punchOutDate = dateBuffer;
    punchOutTime = timeBuffer;
    isPunchedIn = false;
    calculateWorkingHours();
    cout << "\n====================================\n";
    cout << "         PUNCH OUT SUCCESSFUL\n";
    cout << "====================================\n";
    cout << "Employee ID       : " << employeeId << endl;
    cout << "Employee Name     : " << employeeName << endl;
    cout << "Punch Out Date    : " << punchOutDate << endl;
    cout << "Punch Out Time    : " << punchOutTime << endl;
    cout << fixed << setprecision(2);
    cout << "Working Hours     : " << totalWorkingHours << " hours\n";
    cout << "====================================\n";
}

void PunchInOut::calculateWorkingHours() {
    if (punchInTime.empty() || punchOutTime.empty()) {
        totalWorkingHours = 0.0f;
        return;
    }
    int inHour, inMinute, inSecond;
    int outHour, outMinute, outSecond;
    char colon;
    stringstream inStream(punchInTime);
    inStream >> inHour >> colon >> inMinute >> colon >> inSecond;
    stringstream outStream(punchOutTime);
    outStream >> outHour >> colon >> outMinute >> colon >> outSecond;
    int punchInSeconds = (inHour * 3600) + (inMinute * 60) + inSecond;
    int punchOutSeconds = (outHour * 3600) + (outMinute * 60) + outSecond;
    int difference = punchOutSeconds - punchInSeconds;
    if (difference < 0) {
        difference += 24 * 60 * 60;
    }
    totalWorkingHours = static_cast<float>(difference / 3600.0);
}

void PunchInOut::displayAttendance() const {
    cout << "\n============================================\n";
    cout << "             ATTENDANCE DETAILS\n";
    cout << "============================================\n";
    cout << "Employee ID       : " << employeeId << endl;
    cout << "Employee Name     : " << employeeName << endl;
    cout << "Employee Role     : " << employeeRole << endl;
    cout << "Department        : " << department << endl;
    cout << "--------------------------------------------\n";
    if (!punchInDate.empty()) {
        cout << "Punch In Date     : " << punchInDate << endl;
        cout << "Punch In Time     : " << punchInTime << endl;
    } else {
        cout << "Punch In          : Not Available\n";
    }

    if (!punchOutDate.empty()) {
        cout << "Punch Out Date    : " << punchOutDate << endl;
        cout << "Punch Out Time    : " << punchOutTime << endl;
    } else {
        cout << "Punch Out         : Not Available\n";
    }
    cout << "--------------------------------------------\n";
    cout << "Current Status    : " << (isPunchedIn ? "PUNCHED IN" : "PUNCHED OUT") << endl;
    cout << fixed << setprecision(2);
    cout << "Working Hours     : " << totalWorkingHours << " hours\n";
    cout << "============================================\n";
}

void PunchInOut::displayPunchInDetails() const {
    cout << "\n====================================\n";
    cout << "        PUNCH IN DETAILS\n";
    cout << "====================================\n";
    if (punchInDate.empty() || punchInTime.empty()) {
        cout << "No punch-in record available.\n";
    } else {
        cout << "Employee ID   : " << employeeId << endl;
        cout << "Employee Name : " << employeeName << endl;
        cout << "Date          : " << punchInDate << endl;
        cout << "Time          : " << punchInTime << endl;
    }
    cout << "====================================\n";
}

void PunchInOut::displayPunchOutDetails() const {
    cout << "\n====================================\n";
    cout << "        PUNCH OUT DETAILS\n";
    cout << "====================================\n";
    if (punchOutDate.empty() || punchOutTime.empty()) {
        cout << "No punch-out record available.\n";
    } else {
        cout << "Employee ID       : " << employeeId << endl;
        cout << "Employee Name     : " << employeeName << endl;
        cout << "Date              : " << punchOutDate << endl;
        cout << "Time              : " << punchOutTime << endl;
        cout << fixed << setprecision(2);
        cout << "Total Working     : " << totalWorkingHours << " hours\n";
    }
    cout << "====================================\n";
}

void PunchInOut::resetAttendance() {
    punchInDate = "";
    punchInTime = "";
    punchOutDate = "";
    punchOutTime = "";
    isPunchedIn = false;
    totalWorkingHours = 0.0f;
    cout << "\nAttendance record has been reset successfully.\n";
}

void PunchInOut::setEmployeeDetails() {
    cout << "\n====================================\n";
    cout << "       ENTER EMPLOYEE DETAILS\n";
    cout << "====================================\n";
    employeeId = punch_getValidInteger("Enter Employee ID: ");
    employeeName = punch_getNonEmptyString("Enter Employee Name: ");
    employeeRole = punch_getNonEmptyString("Enter Employee Role: ");
    department = punch_getNonEmptyString("Enter Department: ");
    cout << "\nEmployee details saved successfully.\n";
}

void PunchInOut::getEmployeeDetails() const {
    cout << "\n====================================\n";
    cout << "         EMPLOYEE DETAILS\n";
    cout << "====================================\n";
    cout << "Employee ID   : " << employeeId << endl;
    cout << "Employee Name : " << employeeName << endl;
    cout << "Employee Role : " << employeeRole << endl;
    cout << "Department    : " << department << endl;
    cout << "====================================\n";
}