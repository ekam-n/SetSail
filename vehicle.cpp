//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// vehicle.cpp
// Description:
// Implementation of the Vehicle class which handles vehicle operations
// including creation, validation, and management of regular/special vehicles.
//
// Revision History:
// Rev. 1 - 2025/07/16 - Team 12
// - Initial implementation
//*******************************

#include "vehicle.h"
#include <string>

// Define all static members
std::string Vehicle::currentLicensePlate;
std::string Vehicle::currentPhoneNumber;
float Vehicle::currentHeight = 0.0f;
float Vehicle::currentLength = 0.0f;
bool Vehicle::isSpecialVehicle = false;

//------
// Description:
// Initializes the Vehicle class. Returns true if successful.
// Precondition:
// None
bool Vehicle::init() {
    currentLicensePlate = "";
    currentPhoneNumber = "";
    currentHeight = 0.0f;
    currentLength = 0.0f;
    isSpecialVehicle = false;
    return true;
}

//------
// Description:
// Shuts down the Vehicle class and cleans up resources.
// Precondition:
// Class must be initialized
void Vehicle::shutdown() {
    // Currently no resources to clean up
}

//------
// Description:
// Checks if license is valid for reservations. Returns true if valid.
// Implementation:
// Currently just checks if license string is not empty (placeholder)
// Precondition:
// License must exist in system
bool Vehicle::checkLicenseForReservation(const std::string& license) {
    return !license.empty(); // Simple placeholder validation
}

//------
// Description:
// Creates a standard vehicle for reservations. Returns true if successful.
// Implementation:
// Stores the provided data in member variables for later processing
// Precondition:
// Valid vehicle data and unique license
bool Vehicle::createVehicleForReservation(
    const std::string& licensePlate,
    const std::string& phoneNumber
) {
    currentLicensePlate = licensePlate;
    currentPhoneNumber = phoneNumber;
    currentHeight = 0.0f;
    currentLength = 0.0f;
    isSpecialVehicle = false;
    return true;
}

//------
// Description:
// Creates a special vehicle for reservations. Returns true if successful.
// Implementation:
// Stores the provided data in member variables for later processing
// Precondition:
// Valid vehicle data and unique license
bool Vehicle::createSpecialVehicleForReservation(
    const std::string& licensePlate,
    const std::string& phoneNumber,
    float height,
    float length
) {
    currentLicensePlate = licensePlate;
    currentPhoneNumber = phoneNumber;
    currentHeight = height;
    currentLength = length;
    isSpecialVehicle = true;
    return true;
}