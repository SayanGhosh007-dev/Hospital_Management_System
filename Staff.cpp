#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Staff
{
private:

    // Doctor details
    struct Doctor
    {
        int id;
        string name;
        string specialization;
        string qualification;
        string phone;
    };

    // Nurse details
    struct Nurse
    {
        int id;
        string name;
        string qualification;
        string department;
        string phone;
    };

    // Other staff details
    struct OtherStaff
    {
        int id;
        string name;
        string designation;
        string department;
        string phone;
    };

    vector<Doctor> doctors;
    vector<Nurse> nurses;
    vector<OtherStaff> staffMembers;


public:

    // ================= DOCTOR =================

    void addDoctor()
    {
        Doctor d;

        cout << "\nEnter Doctor ID: ";
        cin >> d.id;

        cin.ignore();

        cout << "Enter Doctor Name: ";
        getline(cin, d.name);

        cout << "Enter Specialization: ";
        getline(cin, d.specialization);

        cout << "Enter Qualification: ";
        getline(cin, d.qualification);

        cout << "Enter Phone Number: ";
        getline(cin, d.phone);

        doctors.push_back(d);

        cout << "\nDoctor added successfully!\n";
    }


    void viewDoctorDetails()
    {
        if (doctors.empty())
        {
            cout << "\nNo doctor records found.\n";
            return;
        }

        cout << "\n========== DOCTOR DETAILS ==========\n";

        for (const auto &d : doctors)
        {
            cout << "\nDoctor ID: " << d.id;
            cout << "\nName: " << d.name;
            cout << "\nSpecialization: " << d.specialization;
            cout << "\nQualification: " << d.qualification;
            cout << "\nPhone: " << d.phone;
            cout << "\n-----------------------------------\n";
        }
    }


    void updateDoctorDetails()
    {
        int id;

        cout << "\nEnter Doctor ID to update: ";
        cin >> id;

        for (auto &d : doctors)
        {
            if (d.id == id)
            {
                cin.ignore();

                cout << "Enter New Name: ";
                getline(cin, d.name);

                cout << "Enter New Specialization: ";
                getline(cin, d.specialization);

                cout << "Enter New Qualification: ";
                getline(cin, d.qualification);

                cout << "Enter New Phone Number: ";
                getline(cin, d.phone);

                cout << "\nDoctor details updated successfully!\n";
                return;
            }
        }

        cout << "\nDoctor not found.\n";
    }


    void deleteDoctor()
    {
        int id;

        cout << "\nEnter Doctor ID to delete: ";
        cin >> id;

        for (auto it = doctors.begin(); it != doctors.end(); ++it)
        {
            if (it->id == id)
            {
                doctors.erase(it);

                cout << "\nDoctor deleted successfully!\n";
                return;
            }
        }

        cout << "\nDoctor not found.\n";
    }


    void searchDoctor()
    {
        int id;

        cout << "\nEnter Doctor ID to search: ";
        cin >> id;

        for (const auto &d : doctors)
        {
            if (d.id == id)
            {
                cout << "\n========== DOCTOR FOUND ==========\n";
                cout << "Doctor ID: " << d.id << endl;
                cout << "Name: " << d.name << endl;
                cout << "Specialization: " << d.specialization << endl;
                cout << "Qualification: " << d.qualification << endl;
                cout << "Phone: " << d.phone << endl;

                return;
            }
        }

        cout << "\nDoctor not found.\n";
    }


    // ================= NURSE =================

    void addNurse()
    {
        Nurse n;

        cout << "\nEnter Nurse ID: ";
        cin >> n.id;

        cin.ignore();

        cout << "Enter Nurse Name: ";
        getline(cin, n.name);

        cout << "Enter Qualification: ";
        getline(cin, n.qualification);

        cout << "Enter Department: ";
        getline(cin, n.department);

        cout << "Enter Phone Number: ";
        getline(cin, n.phone);

        nurses.push_back(n);

        cout << "\nNurse added successfully!\n";
    }


    void viewNurseDetails()
    {
        if (nurses.empty())
        {
            cout << "\nNo nurse records found.\n";
            return;
        }

        cout << "\n========== NURSE DETAILS ==========\n";

        for (const auto &n : nurses)
        {
            cout << "\nNurse ID: " << n.id;
            cout << "\nName: " << n.name;
            cout << "\nQualification: " << n.qualification;
            cout << "\nDepartment: " << n.department;
            cout << "\nPhone: " << n.phone;
            cout << "\n-----------------------------------\n";
        }
    }


    void updateNurseDetails()
    {
        int id;

        cout << "\nEnter Nurse ID to update: ";
        cin >> id;

        for (auto &n : nurses)
        {
            if (n.id == id)
            {
                cin.ignore();

                cout << "Enter New Name: ";
                getline(cin, n.name);

                cout << "Enter New Qualification: ";
                getline(cin, n.qualification);

                cout << "Enter New Department: ";
                getline(cin, n.department);

                cout << "Enter New Phone Number: ";
                getline(cin, n.phone);

                cout << "\nNurse details updated successfully!\n";
                return;
            }
        }

        cout << "\nNurse not found.\n";
    }


    void deleteNurse()
    {
        int id;

        cout << "\nEnter Nurse ID to delete: ";
        cin >> id;

        for (auto it = nurses.begin(); it != nurses.end(); ++it)
        {
            if (it->id == id)
            {
                nurses.erase(it);

                cout << "\nNurse deleted successfully!\n";
                return;
            }
        }

        cout << "\nNurse not found.\n";
    }


    void searchNurse()
    {
        int id;

        cout << "\nEnter Nurse ID to search: ";
        cin >> id;

        for (const auto &n : nurses)
        {
            if (n.id == id)
            {
                cout << "\n========== NURSE FOUND ==========\n";
                cout << "Nurse ID: " << n.id << endl;
                cout << "Name: " << n.name << endl;
                cout << "Qualification: " << n.qualification << endl;
                cout << "Department: " << n.department << endl;
                cout << "Phone: " << n.phone << endl;

                return;
            }
        }

        cout << "\nNurse not found.\n";
    }


    // ================= OTHER STAFF =================

    void addStaff()
    {
        OtherStaff s;

        cout << "\nEnter Staff ID: ";
        cin >> s.id;

        cin.ignore();

        cout << "Enter Staff Name: ";
        getline(cin, s.name);

        cout << "Enter Designation: ";
        getline(cin, s.designation);

        cout << "Enter Department: ";
        getline(cin, s.department);

        cout << "Enter Phone Number: ";
        getline(cin, s.phone);

        staffMembers.push_back(s);

        cout << "\nStaff added successfully!\n";
    }


    void viewStaffDetails()
    {
        if (staffMembers.empty())
        {
            cout << "\nNo staff records found.\n";
            return;
        }

        cout << "\n========== STAFF DETAILS ==========\n";

        for (const auto &s : staffMembers)
        {
            cout << "\nStaff ID: " << s.id;
            cout << "\nName: " << s.name;
            cout << "\nDesignation: " << s.designation;
            cout << "\nDepartment: " << s.department;
            cout << "\nPhone: " << s.phone;
            cout << "\n-----------------------------------\n";
        }
    }


    void updateStaffDetails()
    {
        int id;

        cout << "\nEnter Staff ID to update: ";
        cin >> id;

        for (auto &s : staffMembers)
        {
            if (s.id == id)
            {
                cin.ignore();

                cout << "Enter New Name: ";
                getline(cin, s.name);

                cout << "Enter New Designation: ";
                getline(cin, s.designation);

                cout << "Enter New Department: ";
                getline(cin, s.department);

                cout << "Enter New Phone Number: ";
                getline(cin, s.phone);

                cout << "\nStaff details updated successfully!\n";
                return;
            }
        }

        cout << "\nStaff member not found.\n";
    }


    void deleteStaff()
    {
        int id;

        cout << "\nEnter Staff ID to delete: ";
        cin >> id;

        for (auto it = staffMembers.begin(); it != staffMembers.end(); ++it)
        {
            if (it->id == id)
            {
                staffMembers.erase(it);

                cout << "\nStaff member deleted successfully!\n";
                return;
            }
        }

        cout << "\nStaff member not found.\n";
    }


    void searchStaff()
    {
        int id;

        cout << "\nEnter Staff ID to search: ";
        cin >> id;

        for (const auto &s : staffMembers)
        {
            if (s.id == id)
            {
                cout << "\n========== STAFF FOUND ==========\n";
                cout << "Staff ID: " << s.id << endl;
                cout << "Name: " << s.name << endl;
                cout << "Designation: " << s.designation << endl;
                cout << "Department: " << s.department << endl;
                cout << "Phone: " << s.phone << endl;

                return;
            }
        }
        cout << "\nStaff member not found.\n";
    }
};
