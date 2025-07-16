//*******************************
//*******************************
// vehicle.h
// Description:
// This class handles all vehicle operations including creation, validation,
// and management of both regular and special vehicles.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// Rev. 2 - 2025/07/16
// - Converted to class format with private member variables
//*******************************

#pragma once
#include <string>

class Vehicle {
public:

    friend class VehicleIO;
    //------
    // Description:
    // Initializes the Vehicle class. Returns true if successful.
    // Precondition:
    // None
    static bool init();

    //------
    // Description:
    // Shuts down the Vehicle class and cleans up resources.
    // Precondition:
    // Class must be initialized
    static void shutdown();

    //------
    // Description:
    // Checks if license is valid for reservations. Returns true if valid.
    // Precondition:
    // License must exist in system
    static bool checkLicenseForReservation(
        const std::string& license  // [in] Vehicle license to check
    );

    //------
    // Description:
    // Creates a standard vehicle for reservations. Returns true if successful.
    // Precondition:
    // Valid vehicle data and unique license
    static bool createVehicleForReservation(
        const std::string& licensePlate,  // [in] Vehicle license plate
        const std::string& phoneNumber    // [in] Owner's phone number
    );

    //------
    // Description:
    // Creates a special vehicle for reservations. Returns true if successful.
    // Precondition:
    // Valid vehicle data and unique license
    static bool createSpecialVehicleForReservation(
        const std::string& licensePlate,  // [in] Vehicle license plate
        const std::string& phoneNumber,   // [in] Owner's phone number
        float height,                     // [in] Vehicle height in meters
        float length                      // [in] Vehicle length in meters
    );

private:
    static std::string currentLicensePlate;  // Currently processed vehicle license
    static std::string currentPhoneNumber;   // Currently processed owner phone
    static float currentHeight;              // Currently processed vehicle height (0 for regular)
    static float currentLength;              // Currently processed vehicle length (0 for regular)
    static bool isSpecialVehicle;            // Flag indicating special vehicle status
};