#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Maintenance {
private:
    static int nextId;
    int id;
    string name;
    string address;
    long long phone;
    string email;

public:
    Maintenance();
    Maintenance(int recordId, const string& recName, const string& recAddr, long long recPhone, const string& recEmail);

    int getId() const;
    string getName() const;
    string getAddress() const;
    long long getPhone() const;
    string getEmail() const;

    void setId(int recordId);
    void setName(const string& recName);
    void setAddress(const string& recAddr);
    void setPhone(long long recPhone);
    void setEmail(const string& recEmail);

    void addMaintenanceRecord();
    void viewMaintenanceRecord() const;
    void updateMaintenanceRecord();
};

int Maintenance::nextId = 0;

static long long maint_getValidPhone(const string& prompt) {
    long long value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value > 0) {
                return value;
            }
            cout << "Phone number must be positive. Please try again.\n";
        } else {
            cout << "Invalid phone format. Please enter numbers only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

static string maint_getNonEmptyString(const string& prompt) {
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

Maintenance::Maintenance()
    : id(0), name(""), address(""), phone(0), email("") {}

Maintenance::Maintenance(int recordId, const string& recName, const string& recAddr, long long recPhone, const string& recEmail)
    : id(recordId), name(recName), address(recAddr), phone(recPhone), email(recEmail) {
    if (recordId > nextId) {
        nextId = recordId;
    }
}

int Maintenance::getId() const { return id; }
string Maintenance::getName() const { return name; }
string Maintenance::getAddress() const { return address; }
long long Maintenance::getPhone() const { return phone; }
string Maintenance::getEmail() const { return email; }

void Maintenance::setId(int recordId) { id = recordId; }
void Maintenance::setName(const string& recName) { name = recName; }
void Maintenance::setAddress(const string& recAddr) { address = recAddr; }
void Maintenance::setPhone(long long recPhone) { phone = recPhone; }
void Maintenance::setEmail(const string& recEmail) { email = recEmail; }

void Maintenance::addMaintenanceRecord() {
    id = ++nextId;
    name = maint_getNonEmptyString("\nEnter Maintenance Name: ");
    address = maint_getNonEmptyString("Enter Maintenance Address: ");
    phone = maint_getValidPhone("Enter Maintenance Phone: ");
    email = maint_getNonEmptyString("Enter Maintenance Email: ");
    cout << "\nMaintenance record added successfully!\n";
    cout << "Maintenance ID: " << id << endl;
}

void Maintenance::viewMaintenanceRecord() const {
    cout << "\n-----------------------------\n";
    cout << "Maintenance ID      : " << id << endl;
    cout << "Maintenance Name    : " << name << endl;
    cout << "Maintenance Address : " << address << endl;
    cout << "Maintenance Phone   : " << phone << endl;
    cout << "Maintenance Email   : " << email << endl;
    cout << "-----------------------------\n";
}

void Maintenance::updateMaintenanceRecord() {
    name = maint_getNonEmptyString("Enter New Maintenance Name: ");
    address = maint_getNonEmptyString("Enter New Maintenance Address: ");
    phone = maint_getValidPhone("Enter New Maintenance Phone: ");
    email = maint_getNonEmptyString("Enter New Maintenance Email: ");
    cout << "\nRecord updated successfully!\n";
}
