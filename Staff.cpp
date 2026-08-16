#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Staff {
public:
    struct Doctor {
        int id;
        string name;
        string specialization;
        string qualification;
        string phone;
    };

    struct Nurse {
        int id;
        string name;
        string qualification;
        string department;
        string phone;
    };

    struct OtherStaff {
        int id;
        string name;
        string designation;
        string department;
        string phone;
    };

private:
    vector<Doctor> doctors;
    vector<Nurse> nurses;
    vector<OtherStaff> staffMembers;

public:
    Staff();

    // Programmatic CRUD
    const vector<Doctor>& getDoctors() const;
    const vector<Nurse>& getNurses() const;
    const vector<OtherStaff>& getStaffMembers() const;

    void addDoctor(const Doctor& d);
    bool updateDoctor(int id, const Doctor& newD);
    bool deleteDoctor(int id);

    void addNurse(const Nurse& n);
    bool updateNurse(int id, const Nurse& newN);
    bool deleteNurse(int id);

    void addOtherStaff(const OtherStaff& s);
    bool updateOtherStaff(int id, const OtherStaff& newS);
    bool deleteOtherStaff(int id);

    // Interactive operations (kept for compatibility)
    void addDoctor();
    void viewDoctorDetails() const;
    void updateDoctorDetails();
    void deleteDoctor();
    void searchDoctor() const;

    void addNurse();
    void viewNurseDetails() const;
    void updateNurseDetails();
    void deleteNurse();
    void searchNurse() const;

    void addStaff();
    void viewStaffDetails() const;
    void updateStaffDetails();
    void deleteStaff();
    void searchStaff() const;
};

static int staff_getValidInteger(const string& prompt) {
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

static string staff_getNonEmptyString(const string& prompt) {
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

Staff::Staff() {}

const vector<Staff::Doctor>& Staff::getDoctors() const { return doctors; }
const vector<Staff::Nurse>& Staff::getNurses() const { return nurses; }
const vector<Staff::OtherStaff>& Staff::getStaffMembers() const { return staffMembers; }

void Staff::addDoctor(const Doctor& d) { doctors.push_back(d); }
bool Staff::updateDoctor(int id, const Doctor& newD) {
    for (auto& d : doctors) {
        if (d.id == id) {
            d = newD;
            d.id = id; // Ensure ID remains invariant
            return true;
        }
    }
    return false;
}
bool Staff::deleteDoctor(int id) {
    for (auto it = doctors.begin(); it != doctors.end(); ++it) {
        if (it->id == id) {
            doctors.erase(it);
            return true;
        }
    }
    return false;
}

void Staff::addNurse(const Nurse& n) { nurses.push_back(n); }
bool Staff::updateNurse(int id, const Nurse& newN) {
    for (auto& n : nurses) {
        if (n.id == id) {
            n = newN;
            n.id = id;
            return true;
        }
    }
    return false;
}
bool Staff::deleteNurse(int id) {
    for (auto it = nurses.begin(); it != nurses.end(); ++it) {
        if (it->id == id) {
            nurses.erase(it);
            return true;
        }
    }
    return false;
}

void Staff::addOtherStaff(const OtherStaff& s) { staffMembers.push_back(s); }
bool Staff::updateOtherStaff(int id, const OtherStaff& newS) {
    for (auto& s : staffMembers) {
        if (s.id == id) {
            s = newS;
            s.id = id;
            return true;
        }
    }
    return false;
}
bool Staff::deleteOtherStaff(int id) {
    for (auto it = staffMembers.begin(); it != staffMembers.end(); ++it) {
        if (it->id == id) {
            staffMembers.erase(it);
            return true;
        }
    }
    return false;
}

// Interactive Doctors
void Staff::addDoctor() {
    Doctor d;
    d.id = staff_getValidInteger("\nEnter Doctor ID: ");
    d.name = staff_getNonEmptyString("Enter Doctor Name: ");
    d.specialization = staff_getNonEmptyString("Enter Specialization: ");
    d.qualification = staff_getNonEmptyString("Enter Qualification: ");
    d.phone = staff_getNonEmptyString("Enter Phone Number: ");
    addDoctor(d);
    cout << "\nDoctor added successfully!\n";
}

void Staff::viewDoctorDetails() const {
    if (doctors.empty()) {
        cout << "\nNo doctor records found.\n";
        return;
    }
    cout << "\n========== DOCTOR DETAILS ==========\n";
    for (const auto &d : doctors) {
        cout << "\nDoctor ID: " << d.id;
        cout << "\nName: " << d.name;
        cout << "\nSpecialization: " << d.specialization;
        cout << "\nQualification: " << d.qualification;
        cout << "\nPhone: " << d.phone;
        cout << "\n-----------------------------------\n";
    }
}

void Staff::updateDoctorDetails() {
    int id = staff_getValidInteger("\nEnter Doctor ID to update: ");
    Doctor d;
    d.name = staff_getNonEmptyString("Enter New Name: ");
    d.specialization = staff_getNonEmptyString("Enter New Specialization: ");
    d.qualification = staff_getNonEmptyString("Enter New Qualification: ");
    d.phone = staff_getNonEmptyString("Enter New Phone Number: ");
    if (updateDoctor(id, d)) {
        cout << "\nDoctor details updated successfully!\n";
    } else {
        cout << "\nDoctor not found.\n";
    }
}

void Staff::deleteDoctor() {
    int id = staff_getValidInteger("\nEnter Doctor ID to delete: ");
    if (deleteDoctor(id)) {
        cout << "\nDoctor deleted successfully!\n";
    } else {
        cout << "\nDoctor not found.\n";
    }
}

void Staff::searchDoctor() const {
    int id = staff_getValidInteger("\nEnter Doctor ID to search: ");
    for (const auto &d : doctors) {
        if (d.id == id) {
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

// Interactive Nurses
void Staff::addNurse() {
    Nurse n;
    n.id = staff_getValidInteger("\nEnter Nurse ID: ");
    n.name = staff_getNonEmptyString("Enter Nurse Name: ");
    n.qualification = staff_getNonEmptyString("Enter Qualification: ");
    n.department = staff_getNonEmptyString("Enter Department: ");
    n.phone = staff_getNonEmptyString("Enter Phone Number: ");
    addNurse(n);
    cout << "\nNurse added successfully!\n";
}

void Staff::viewNurseDetails() const {
    if (nurses.empty()) {
        cout << "\nNo nurse records found.\n";
        return;
    }
    cout << "\n========== NURSE DETAILS ==========\n";
    for (const auto &n : nurses) {
        cout << "\nNurse ID: " << n.id;
        cout << "\nName: " << n.name;
        cout << "\nQualification: " << n.qualification;
        cout << "\nDepartment: " << n.department;
        cout << "\nPhone: " << n.phone;
        cout << "\n-----------------------------------\n";
    }
}

void Staff::updateNurseDetails() {
    int id = staff_getValidInteger("\nEnter Nurse ID to update: ");
    Nurse n;
    n.name = staff_getNonEmptyString("Enter New Name: ");
    n.qualification = staff_getNonEmptyString("Enter New Qualification: ");
    n.department = staff_getNonEmptyString("Enter New Department: ");
    n.phone = staff_getNonEmptyString("Enter New Phone Number: ");
    if (updateNurse(id, n)) {
        cout << "\nNurse details updated successfully!\n";
    } else {
        cout << "\nNurse not found.\n";
    }
}

void Staff::deleteNurse() {
    int id = staff_getValidInteger("\nEnter Nurse ID to delete: ");
    if (deleteNurse(id)) {
        cout << "\nNurse deleted successfully!\n";
    } else {
        cout << "\nNurse not found.\n";
    }
}

void Staff::searchNurse() const {
    int id = staff_getValidInteger("\nEnter Nurse ID to search: ");
    for (const auto &n : nurses) {
        if (n.id == id) {
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

// Interactive Other Staff
void Staff::addStaff() {
    OtherStaff s;
    s.id = staff_getValidInteger("\nEnter Staff ID: ");
    s.name = staff_getNonEmptyString("Enter Staff Name: ");
    s.designation = staff_getNonEmptyString("Enter Designation: ");
    s.department = staff_getNonEmptyString("Enter Department: ");
    s.phone = staff_getNonEmptyString("Enter Phone Number: ");
    addOtherStaff(s);
    cout << "\nStaff added successfully!\n";
}

void Staff::viewStaffDetails() const {
    if (staffMembers.empty()) {
        cout << "\nNo staff records found.\n";
        return;
    }
    cout << "\n========== STAFF DETAILS ==========\n";
    for (const auto &s : staffMembers) {
        cout << "\nStaff ID: " << s.id;
        cout << "\nName: " << s.name;
        cout << "\nDesignation: " << s.designation;
        cout << "\nDepartment: " << s.department;
        cout << "\nPhone: " << s.phone;
        cout << "\n-----------------------------------\n";
    }
}

void Staff::updateStaffDetails() {
    int id = staff_getValidInteger("\nEnter Staff ID to update: ");
    OtherStaff s;
    s.name = staff_getNonEmptyString("Enter New Name: ");
    s.designation = staff_getNonEmptyString("Enter New Designation: ");
    s.department = staff_getNonEmptyString("Enter New Department: ");
    s.phone = staff_getNonEmptyString("Enter New Phone Number: ");
    if (updateOtherStaff(id, s)) {
        cout << "\nStaff details updated successfully!\n";
    } else {
        cout << "\nStaff member not found.\n";
    }
}

void Staff::deleteStaff() {
    int id = staff_getValidInteger("\nEnter Staff ID to delete: ");
    if (deleteOtherStaff(id)) {
        cout << "\nStaff member deleted successfully!\n";
    } else {
        cout << "\nStaff member not found.\n";
    }
}

void Staff::searchStaff() const {
    int id = staff_getValidInteger("\nEnter Staff ID to search: ");
    for (const auto &s : staffMembers) {
        if (s.id == id) {
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
