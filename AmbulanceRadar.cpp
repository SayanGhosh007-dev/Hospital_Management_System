#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ambulanceRadar
{
private:
    int ambulanceId;
    int patientCount;
    double latitude;
    double longitude;
    string ambulanceNumber;
    string driverName;
    string driverContact;
    string currentLocation;
    string destination;
    string status;
    bool available;

public:
    ambulanceRadar(
        int id,
        string number,
        string driver,
        string contact,
        string location,
        string destination,
        double lat,
        double lon);
    void updateAmbulanceDetails(
        string driver,
        string contact,
        string location,
        string destination,
        double lat,
        double lon);

    void updateLocation(
        string location,
        double lat,
        double lon);
    void assignAmbulance();
    void releaseAmbulance();
    void updateStatus(string newStatus);
    bool checkAvailability();
    void displayLocation();
    void displayAmbulanceDetails();
    double getLatitude();
    double getLongitude();
    int getPatientCount();
    int getAmbulanceId();
    string getAmbulanceNumber();
    string getStatus();
    string getCurrentLocation();
    string getDestination();
    string getDriverName();
    string getDriverContact();
};

// Constructor

ambulanceRadar::ambulanceRadar(
    int id,
    string number,
    string driver,
    string contact,
    string location,
    string dest,
    double lat,
    double lon)
{
    ambulanceId = id;
    ambulanceNumber = number;

    driverName = driver;
    driverContact = contact;

    currentLocation = location;
    destination = dest;

    latitude = lat;
    longitude = lon;

    status = "Available";
    available = true;

    patientCount = 0;
}

// Update Ambulance Details

void ambulanceRadar::updateAmbulanceDetails(
    string driver,
    string contact,
    string location,
    string dest,
    double lat,
    double lon)
{
    driverName = driver;
    driverContact = contact;

    currentLocation = location;
    destination = dest;

    latitude = lat;
    longitude = lon;
}

// Update Ambulance Location

void ambulanceRadar::updateLocation(
    string location,
    double lat,
    double lon)
{
    currentLocation = location;

    latitude = lat;
    longitude = lon;
}

// Assign Ambulance

void ambulanceRadar::assignAmbulance()
{
    if (available)
    {
        available = false;
        status = "Assigned";

        patientCount++;
    }
}

// Release Ambulance

void ambulanceRadar::releaseAmbulance()
{
    if (!available)
    {
        available = true;
        status = "Available";
    }
}

// Update Ambulance Status

void ambulanceRadar::updateStatus(string newStatus)
{
    if (newStatus == "Available" ||
        newStatus == "available")
    {
        status = "Available";
        available = true;
    }
    else if (newStatus == "Assigned" ||
             newStatus == "assigned")
    {
        status = "Assigned";
        available = false;
    }
}

// Check Availability

bool ambulanceRadar::checkAvailability()
{
    return available;
}

// Display Location

void ambulanceRadar::displayLocation()
{
    cout << "Ambulance Number : " << ambulanceNumber << endl;
    cout << "Current Location : " << currentLocation << endl;
    cout << "Latitude         : " << latitude << endl;
    cout << "Longitude        : " << longitude << endl;
}

// Display Ambulance Details

void ambulanceRadar::displayAmbulanceDetails()
{
    cout << "Ambulance ID      : " << ambulanceId << endl;
    cout << "Ambulance Number  : " << ambulanceNumber << endl;

    cout << "Driver Name       : " << driverName << endl;
    cout << "Driver Contact    : " << driverContact << endl;

    cout << "Current Location  : " << currentLocation << endl;
    cout << "Destination       : " << destination << endl;

    cout << "Latitude          : " << latitude << endl;
    cout << "Longitude         : " << longitude << endl;

    cout << "Status            : " << status << endl;

    cout << "Available         : "
         << (available ? "Yes" : "No")
         << endl;

    cout << "Patient Count     : "
         << patientCount
         << endl;
}

// Getter Functions

int ambulanceRadar::getAmbulanceId()
{
    return ambulanceId;
}

string ambulanceRadar::getAmbulanceNumber()
{
    return ambulanceNumber;
}

string ambulanceRadar::getStatus()
{
    return status;
}

string ambulanceRadar::getCurrentLocation()
{
    return currentLocation;
}

string ambulanceRadar::getDestination()
{
    return destination;
}

string ambulanceRadar::getDriverName()
{
    return driverName;
}

string ambulanceRadar::getDriverContact()
{
    return driverContact;
}

double ambulanceRadar::getLatitude()
{
    return latitude;
}

double ambulanceRadar::getLongitude()
{
    return longitude;
}

int ambulanceRadar::getPatientCount()
{
    return patientCount;
}