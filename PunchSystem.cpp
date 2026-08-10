#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

class PunchInOut
{
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
    PunchInOut()
    {
        employeeId = 0;
        employeeName = "";
        employeeRole = "";
        department = "";
        punchInDate = "";
        punchInTime = "";
        punchOutDate = "";
        punchOutTime = "";
        isPunchedIn = false;
        totalWorkingHours = 0.0;
    }
    void punchIn()
    {
        if (isPunchedIn)
        {
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
        totalWorkingHours = 0.0;
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

    // --------------------------------------------------
    // PUNCH OUT
    // --------------------------------------------------
    void punchOut()
    {
        if (!isPunchedIn)
        {
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

    // --------------------------------------------------
    // CALCULATE WORKING HOURS
    // --------------------------------------------------
    void calculateWorkingHours()
    {
        if (punchInTime == "" || punchOutTime == "")
        {
            totalWorkingHours = 0.0;
            return;
        }
        int inHour, inMinute, inSecond;
        int outHour, outMinute, outSecond;
        char colon;
        stringstream inStream(punchInTime);
        inStream >> inHour >> colon >> inMinute >> colon >> inSecond;
        stringstream outStream(punchOutTime);
        outStream >> outHour >> colon >> outMinute >> colon >> outSecond;
        int punchInSeconds =(inHour * 3600) + (inMinute * 60) + inSecond;
        int punchOutSeconds = (outHour * 3600) + (outMinute * 60) + outSecond;
        int difference = punchOutSeconds - punchInSeconds;
        if (difference < 0)
        {
            difference += 24 * 60 * 60;
        }
        totalWorkingHours = difference / 3600.0;
    }

    // --------------------------------------------------
    // DISPLAY COMPLETE ATTENDANCE
    // --------------------------------------------------
    void displayAttendance()
    {
        cout << "\n============================================\n";
        cout << "             ATTENDANCE DETAILS\n";
        cout << "============================================\n";
        cout << "Employee ID       : " << employeeId << endl;
        cout << "Employee Name     : " << employeeName << endl;
        cout << "Employee Role     : " << employeeRole << endl;
        cout << "Department        : " << department << endl;
        cout << "--------------------------------------------\n";
        if (punchInDate != "")
        {
            cout << "Punch In Date     : " << punchInDate << endl;
            cout << "Punch In Time     : " << punchInTime << endl;
        }
        else
        {
            cout << "Punch In          : Not Available\n";
        }

        if (punchOutDate != "")
        {
            cout << "Punch Out Date    : " << punchOutDate << endl;
            cout << "Punch Out Time    : " << punchOutTime << endl;
        }
        else
        {
            cout << "Punch Out         : Not Available\n";
        }
        cout << "--------------------------------------------\n";
        cout << "Current Status    : ";
        if (isPunchedIn)
        {
            cout << "PUNCHED IN\n";
        }
        else
        {
            cout << "PUNCHED OUT\n";
        }
        cout << fixed << setprecision(2);
        cout << "Working Hours     : " << totalWorkingHours << " hours\n";
        cout << "============================================\n";
    }

    // --------------------------------------------------
    // DISPLAY PUNCH IN DETAILS
    // --------------------------------------------------
    void displayPunchInDetails()
    {
        cout << "\n====================================\n";
        cout << "        PUNCH IN DETAILS\n";
        cout << "====================================\n";
        if (punchInDate == "" || punchInTime == "")
        {
            cout << "No punch-in record available.\n";
        }
        else
        {
            cout << "Employee ID   : " << employeeId << endl;
            cout << "Employee Name : " << employeeName << endl;
            cout << "Date          : " << punchInDate << endl;
            cout << "Time          : " << punchInTime << endl;
        }
        cout << "====================================\n";
    }

    // --------------------------------------------------
    // DISPLAY PUNCH OUT DETAILS
    // --------------------------------------------------
    void displayPunchOutDetails()
    {
        cout << "\n====================================\n";
        cout << "        PUNCH OUT DETAILS\n";
        cout << "====================================\n";
        if (punchOutDate == "" || punchOutTime == "")
        {
            cout << "No punch-out record available.\n";
        }
        else
        {
            cout << "Employee ID       : " << employeeId << endl;
            cout << "Employee Name     : " << employeeName << endl;
            cout << "Date              : " << punchOutDate << endl;
            cout << "Time              : " << punchOutTime << endl;
            cout << fixed << setprecision(2);
            cout << "Total Working     : "
                 << totalWorkingHours << " hours\n";
        }
        cout << "====================================\n";
    }

    // --------------------------------------------------
    // CHECK PUNCH-IN STATUS
    // --------------------------------------------------
    bool checkPunchInStatus()
    {
        return isPunchedIn;
    }

    // --------------------------------------------------
    // RESET ATTENDANCE
    // --------------------------------------------------
    void resetAttendance()
    {
        punchInDate = "";
        punchInTime = "";
        punchOutDate = "";
        punchOutTime = "";
        isPunchedIn = false;
        totalWorkingHours = 0.0;
        cout << "\nAttendance record has been reset successfully.\n";
    }

    // --------------------------------------------------
    // SET EMPLOYEE DETAILS
    // --------------------------------------------------
    void setEmployeeDetails()
    {
        cout << "\n====================================\n";
        cout << "       ENTER EMPLOYEE DETAILS\n";
        cout << "====================================\n";
        cout << "Enter Employee ID: ";
        cin >> employeeId;
        cin.ignore();
        cout << "Enter Employee Name: ";
        getline(cin, employeeName);
        cout << "Enter Employee Role: ";
        getline(cin, employeeRole);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "\nEmployee details saved successfully.\n";
    }

    // --------------------------------------------------
    // GET EMPLOYEE DETAILS
    // --------------------------------------------------
    void getEmployeeDetails()
    {
        cout << "\n====================================\n";
        cout << "         EMPLOYEE DETAILS\n";
        cout << "====================================\n";
        cout << "Employee ID   : " << employeeId << endl;
        cout << "Employee Name : " << employeeName << endl;
        cout << "Employee Role : " << employeeRole << endl;
        cout << "Department    : " << department << endl;
        cout << "====================================\n";
    }
};