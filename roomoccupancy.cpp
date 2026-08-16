#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Room {
public:
    struct RoomDetails {
        int roomNumber;
        string roomType;
        double charges;
        string status;
        int patientId;
    };

private:
    vector<RoomDetails> rooms;

public:
    Room();

    // Programmatic operations
    const vector<RoomDetails>& getRooms() const;
    void addRoom(const RoomDetails& r);
    bool allocateRoom(int roomNumber, int patientId);
    bool vacateRoom(int roomNumber);
    bool updateRoomStatus(int roomNumber, const string& status);

    // Interactive operations (kept for compatibility)
    void addRoom();
    void viewRooms() const;
    void checkRoomAvailability() const;
    void allocateRoom();
    void vacateRoom();
    void updateRoomStatus();
    void searchRoom() const;
};

static int room_getValidInteger(const string& prompt) {
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

static double room_getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0.0) {
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

static string room_getNonEmptyString(const string& prompt) {
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

Room::Room() {}

const vector<Room::RoomDetails>& Room::getRooms() const { return rooms; }

void Room::addRoom(const RoomDetails& r) {
    rooms.push_back(r);
}

bool Room::allocateRoom(int roomNumber, int patientId) {
    for (auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            if (r.status == "Available") {
                r.status = "Occupied";
                r.patientId = patientId;
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Room::vacateRoom(int roomNumber) {
    for (auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            if (r.status == "Occupied") {
                r.status = "Available";
                r.patientId = 0;
                return true;
            }
            return false;
        }
    }
    return false;
}

bool Room::updateRoomStatus(int roomNumber, const string& status) {
    for (auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            r.status = status;
            if (status != "Occupied") {
                r.patientId = 0;
            }
            return true;
        }
    }
    return false;
}

void Room::addRoom() {
    RoomDetails r;
    r.roomNumber = room_getValidInteger("\nEnter Room Number: ");
    r.roomType = room_getNonEmptyString("Enter Room Type (General/Private/ICU): ");
    r.charges = room_getValidDouble("Enter Room Charges: ");
    r.status = "Available";
    r.patientId = 0;
    addRoom(r);
    cout << "\nRoom added successfully!\n";
}

void Room::viewRooms() const {
    if (rooms.empty()) {
        cout << "\nNo room records found.\n";
        return;
    }
    cout << "\n========== ROOM DETAILS ==========\n";
    for (const auto &r : rooms) {
        cout << "\nRoom Number: " << r.roomNumber;
        cout << "\nRoom Type: " << r.roomType;
        cout << "\nCharges: " << r.charges;
        cout << "\nStatus: " << r.status;
        if (r.status == "Occupied") {
            cout << "\nPatient ID: " << r.patientId;
        }
        cout << "\n----------------------------------\n";
    }
}

void Room::checkRoomAvailability() const {
    bool found = false;
    cout << "\n========== AVAILABLE ROOMS ==========\n";
    for (const auto &r : rooms) {
        if (r.status == "Available") {
            cout << "\nRoom Number: " << r.roomNumber;
            cout << "\nRoom Type: " << r.roomType;
            cout << "\nCharges: " << r.charges;
            cout << "\n----------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "\nNo room is currently available.\n";
    }
}

void Room::allocateRoom() {
    int roomNumber = room_getValidInteger("\nEnter Room Number: ");
    int patientId = room_getValidInteger("Enter Patient ID: ");
    for (auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            if (r.status == "Available") {
                r.status = "Occupied";
                r.patientId = patientId;
                cout << "\nRoom allocated successfully!\n";
                cout << "Room Number: " << r.roomNumber << endl;
                cout << "Patient ID: " << r.patientId << endl;
                return;
            } else {
                cout << "\nRoom is already occupied.\n";
                return;
            }
        }
    }
    cout << "\nRoom not found.\n";
}

void Room::vacateRoom() {
    int roomNumber = room_getValidInteger("\nEnter Room Number to vacate: ");
    for (auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            if (r.status == "Occupied") {
                r.status = "Available";
                r.patientId = 0;
                cout << "\nRoom vacated successfully!\n";
                return;
            } else {
                cout << "\nRoom is already available.\n";
                return;
            }
        }
    }
    cout << "\nRoom not found.\n";
}

void Room::updateRoomStatus() {
    int roomNumber = room_getValidInteger("\nEnter Room Number: ");
    for (auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            string newStatus = room_getNonEmptyString("Enter New Status (Available/Occupied/Maintenance): ");
            r.status = newStatus;
            if (newStatus != "Occupied") {
                r.patientId = 0;
            }
            cout << "\nRoom status updated successfully!\n";
            return;
        }
    }
    cout << "\nRoom not found.\n";
}

void Room::searchRoom() const {
    int roomNumber = room_getValidInteger("\nEnter Room Number to search: ");
    for (const auto &r : rooms) {
        if (r.roomNumber == roomNumber) {
            cout << "\n========== ROOM FOUND ==========\n";
            cout << "Room Number: " << r.roomNumber << endl;
            cout << "Room Type: " << r.roomType << endl;
            cout << "Charges: " << r.charges << endl;
            cout << "Status: " << r.status << endl;
            if (r.status == "Occupied") {
                cout << "Patient ID: " << r.patientId << endl;
            }
            return;
        }
    }
    cout << "\nRoom not found.\n";
}