#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Maintenance
{
private:
    static int nextId;

    int id;
    string name;
    string address;
    long long phone;
    string email;

public:
    void addMaintenanceRecord();
    void viewMaintenanceRecord() const;
    void updateMaintenanceRecord();
    int getId() const;

    static void viewMaintenanceRecords(const vector<Maintenance>& records);
    static void updateMaintenanceRecord(vector<Maintenance>& records);
    static void deleteMaintenanceRecord(vector<Maintenance>& records);
    static void searchMaintenanceRecord(const vector<Maintenance>& records);
};

int Maintenance::nextId = 0;


// Add Record
void Maintenance::addMaintenanceRecord()
{
    id = ++nextId;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter Maintenance Name: ";
    getline(cin, name);

    cout << "Enter Maintenance Address: ";
    getline(cin, address);

    cout << "Enter Maintenance Phone: ";
    cin >> phone;

    cout << "Enter Maintenance Email: ";
    cin >> email;

    cout << "\nMaintenance record added successfully!\n";
    cout << "Maintenance ID: " << id << endl;
}


// View One Record
void Maintenance::viewMaintenanceRecord() const
{
    cout << "\n-----------------------------\n";
    cout << "Maintenance ID      : " << id << endl;
    cout << "Maintenance Name    : " << name << endl;
    cout << "Maintenance Address : " << address << endl;
    cout << "Maintenance Phone   : " << phone << endl;
    cout << "Maintenance Email   : " << email << endl;
    cout << "-----------------------------\n";

    cout << "Press Enter to continue...";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


// Get ID
int Maintenance::getId() const
{
    return id;
}


// View All Records
void Maintenance::viewMaintenanceRecords(
    const vector<Maintenance>& records)
{
    if (records.empty())
    {
        cout << "\nNo maintenance records found.\n";
        return;
    }

    cout << "\n===== Maintenance Records =====\n";

    for (const auto& record : records)
    {
        record.viewMaintenanceRecord();
    }
}


// Update Record
void Maintenance::updateMaintenanceRecord(
    vector<Maintenance>& records)
{
    if (records.empty())
    {
        cout << "\nNo maintenance records available.\n";
        return;
    }

    int searchId;

    cout << "\nEnter Maintenance ID to update: ";
    cin >> searchId;

    for (auto& record : records)
    {
        if (record.id == searchId)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter New Maintenance Name: ";
            getline(cin, record.name);

            cout << "Enter New Maintenance Address: ";
            getline(cin, record.address);

            cout << "Enter New Maintenance Phone: ";
            cin >> record.phone;

            cout << "Enter New Maintenance Email: ";
            cin >> record.email;

            cout << "\nRecord updated successfully!\n";
            return;
        }
    }

    cout << "\nMaintenance record not found.\n";
}


// Delete Record
void Maintenance::deleteMaintenanceRecord(
    vector<Maintenance>& records)
{
    if (records.empty())
    {
        cout << "\nNo maintenance records available.\n";
        return;
    }

    int searchId;

    cout << "\nEnter Maintenance ID to delete: ";
    cin >> searchId;

    for (auto it = records.begin(); it != records.end(); ++it)
    {
        if (it->id == searchId)
        {
            records.erase(it);

            cout << "\nRecord deleted successfully!\n";
            return;
        }
    }

    cout << "\nMaintenance record not found.\n";
}


// Search Record
void Maintenance::searchMaintenanceRecord(
    const vector<Maintenance>& records)
{
    if (records.empty())
    {
        cout << "\nNo maintenance records available.\n";
        return;
    }

    int searchId;

    cout << "\nEnter Maintenance ID to search: ";
    cin >> searchId;

    for (const auto& record : records)
    {
        if (record.id == searchId)
        {
            cout << "\nRecord found!\n";
            record.viewMaintenanceRecord();
            return;
        }
    }

    cout << "\nMaintenance record not found.\n";
}


// Main
int main()
{
    vector<Maintenance> records;

    int choice;

    while (true)
    {
        cout << "\n========== Maintenance Management ==========\n";
        cout << "1. Add Maintenance Record\n";
        cout << "2. View Maintenance Records\n";
        cout << "3. Update Maintenance Record\n";
        cout << "4. Delete Maintenance Record\n";
        cout << "5. Search Maintenance Record\n";
        cout << "6. Exit\n";
        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                Maintenance maintenance;

                maintenance.addMaintenanceRecord();

                records.push_back(maintenance);

                break;
            }

            case 2:
                Maintenance::viewMaintenanceRecords(records);
                break;

            case 3:
                Maintenance::updateMaintenanceRecord(records);
                break;

            case 4:
                Maintenance::deleteMaintenanceRecord(records);
                break;

            case 5:
                Maintenance::searchMaintenanceRecord(records);
                break;

            case 6:
                cout << "\nThank you!\n";
                return 0;

            default:
                cout << "\nInvalid Choice!\n";
        }
    }

    return 0;
}
