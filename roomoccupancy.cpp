#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Room
{
private:

    // Room details
    struct RoomDetails
    {
        int roomNumber;
        string roomType;
        double charges;
        string status;
        int patientId;
    };

    vector<RoomDetails> rooms;
    public:

    // ================= ADD ROOM =================

    void addRoom()
    {
        RoomDetails r;

        cout << "\nEnter Room Number: ";
        cin >> r.roomNumber;

        cin.ignore();

        cout << "Enter Room Type (General/Private/ICU): ";
        getline(cin, r.roomType);

        cout << "Enter Room Charges: ";
        cin >> r.charges;

        // New room is available by default
        r.status = "Available";
        r.patientId = 0;

        rooms.push_back(r);

        cout << "\nRoom added successfully!\n";
    }
// ================= VIEW ROOMS =================

    void viewRooms()
    {
        if (rooms.empty())
        {
            cout << "\nNo room records found.\n";
            return;
        }

        cout << "\n========== ROOM DETAILS ==========\n";

        for (const auto &r : rooms)
        {
            cout << "\nRoom Number: " << r.roomNumber;
            cout << "\nRoom Type: " << r.roomType;
            cout << "\nCharges: " << r.charges;
            cout << "\nStatus: " << r.status;

            if (r.status == "Occupied")
            {
                cout << "\nPatient ID: " << r.patientId;
            }

            cout << "\n----------------------------------\n";
        }
    }
// ================= CHECK ROOM AVAILABILITY =================

    void checkRoomAvailability()
    {
        bool found = false;

        cout << "\n========== AVAILABLE ROOMS ==========\n";

        for (const auto &r : rooms)
        {
            if (r.status == "Available")
            {
                cout << "\nRoom Number: " << r.roomNumber;
                cout << "\nRoom Type: " << r.roomType;
                cout << "\nCharges: " << r.charges;
                cout << "\n----------------------------------\n";

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo room is currently available.\n";
        }
    }
// ================= ALLOCATE ROOM =================

    void allocateRoom()
    {
        int roomNumber;
        int patientId;

        cout << "\nEnter Room Number: ";
        cin >> roomNumber;

        cout << "Enter Patient ID: ";
        cin >> patientId;

        for (auto &r : rooms)
        {
            if (r.roomNumber == roomNumber)
            {
                if (r.status == "Available")
                {
                    r.status = "Occupied";
                    r.patientId = patientId;

                    cout << "\nRoom allocated successfully!\n";
                    cout << "Room Number: " << r.roomNumber << endl;
                    cout << "Patient ID: " << r.patientId << endl;

                    return;
                    }
                else
                {
                    cout << "\nRoom is already occupied.\n";
                    return;
                }
            }
        }

        cout << "\nRoom not found.\n";
    }
    // ================= VACATE ROOM =================

    void vacateRoom()
    {
        int roomNumber;

        cout << "\nEnter Room Number to vacate: ";
        cin >> roomNumber;

        for (auto &r : rooms)
        {
            if (r.roomNumber == roomNumber)
            {
                if (r.status == "Occupied")
                {
                    r.status = "Available";
                    r.patientId = 0;

                    cout << "\nRoom vacated successfully!\n";
                    return;
                }
                else
                {
                    cout << "\nRoom is already available.\n";
                    return;
                }
            }
             }

        cout << "\nRoom not found.\n";
    }
// ================= UPDATE ROOM STATUS =================

    void updateRoomStatus()
    {
        int roomNumber;
        string newStatus;

        cout << "\nEnter Room Number: ";
        cin >> roomNumber;

        for (auto &r : rooms)
        {
            if (r.roomNumber == roomNumber)
            {
                cout << "Enter New Status (Available/Occupied/Maintenance): ";
                cin >> newStatus;

                r.status = newStatus;

                if (newStatus != "Occupied")
                {
                    r.patientId = 0;
                }

                cout << "\nRoom status updated successfully!\n";
                return;
            }
        }

        cout << "\nRoom not found.\n";
}
// ================= SEARCH ROOM =================

    void searchRoom()
    {
        int roomNumber;

        cout << "\nEnter Room Number to search: ";
        cin >> roomNumber;

        for (const auto &r : rooms)
        {
            if (r.roomNumber == roomNumber)
            {
                cout << "\n========== ROOM FOUND ==========\n";

                cout << "Room Number: " << r.roomNumber << endl;
                cout << "Room Type: " << r.roomType << endl;
                cout << "Charges: " << r.charges << endl;
                cout << "Status: " << r.status << endl;

                if (r.status == "Occupied")
                {
                    cout << "Patient ID: " << r.patientId << endl;
                }

                return;
                }
        }

        cout << "\nRoom not found.\n";
    }
};