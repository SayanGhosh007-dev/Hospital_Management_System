#include <iostream>
#include <string>

using namespace std;

class AmbulanceRadar {
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
    AmbulanceRadar();
    AmbulanceRadar(
        int id,
        const string& number,
        const string& driver,
        const string& contact,
        const string& location,
        const string& destination,
        double lat,
        double lon);

    void updateAmbulanceDetails(
        const string& driver,
        const string& contact,
        const string& location,
        const string& destination,
        double lat,
        double lon);

    void updateLocation(
        const string& location,
        double lat,
        double lon);

    void assignAmbulance();
    void releaseAmbulance();
    void updateStatus(const string& newStatus);
    
    bool checkAvailability() const;
    void displayLocation() const;
    void displayAmbulanceDetails() const;
    
    double getLatitude() const;
    double getLongitude() const;
    int getPatientCount() const;
    int getAmbulanceId() const;
    string getAmbulanceNumber() const;
    string getStatus() const;
    string getCurrentLocation() const;
    string getDestination() const;
    string getDriverName() const;
    string getDriverContact() const;
};

AmbulanceRadar::AmbulanceRadar()
    : ambulanceId(0), patientCount(0), latitude(0.0), longitude(0.0),
      ambulanceNumber(""), driverName(""), driverContact(""),
      currentLocation(""), destination(""), status("Available"), available(true) {}

AmbulanceRadar::AmbulanceRadar(
    int id,
    const string& number,
    const string& driver,
    const string& contact,
    const string& location,
    const string& dest,
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

void AmbulanceRadar::updateAmbulanceDetails(
    const string& driver,
    const string& contact,
    const string& location,
    const string& dest,
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

void AmbulanceRadar::updateLocation(
    const string& location,
    double lat,
    double lon)
{
    currentLocation = location;
    latitude = lat;
    longitude = lon;
}

void AmbulanceRadar::assignAmbulance()
{
    if (available)
    {
        available = false;
        status = "Assigned";
        patientCount++;
    }
}

void AmbulanceRadar::releaseAmbulance()
{
    if (!available)
    {
        available = true;
        status = "Available";
    }
}

void AmbulanceRadar::updateStatus(const string& newStatus)
{
    if (newStatus == "Available" || newStatus == "available")
    {
        status = "Available";
        available = true;
    }
    else if (newStatus == "Assigned" || newStatus == "assigned")
    {
        status = "Assigned";
        available = false;
    }
}

bool AmbulanceRadar::checkAvailability() const
{
    return available;
}

void AmbulanceRadar::displayLocation() const
{
    cout << "Ambulance Number : " << ambulanceNumber << endl;
    cout << "Current Location : " << currentLocation << endl;
    cout << "Latitude         : " << latitude << endl;
    cout << "Longitude        : " << longitude << endl;
}

void AmbulanceRadar::displayAmbulanceDetails() const
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
    cout << "Available         : " << (available ? "Yes" : "No") << endl;
    cout << "Patient Count     : " << patientCount << endl;
}

double AmbulanceRadar::getLatitude() const { return latitude; }
double AmbulanceRadar::getLongitude() const { return longitude; }
int AmbulanceRadar::getPatientCount() const { return patientCount; }
int AmbulanceRadar::getAmbulanceId() const { return ambulanceId; }
string AmbulanceRadar::getAmbulanceNumber() const { return ambulanceNumber; }
string AmbulanceRadar::getStatus() const { return status; }
string AmbulanceRadar::getCurrentLocation() const { return currentLocation; }
string AmbulanceRadar::getDestination() const { return destination; }
string AmbulanceRadar::getDriverName() const { return driverName; }
string AmbulanceRadar::getDriverContact() const { return driverContact; }