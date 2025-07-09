//*******************************
//*******************************
// vehicle.h
// Description:
// This class handles all vehicle operations including creation, validation,
// and management of both regular and special vehicles.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with private member variables
//*******************************

#include <string>

class Vehicle {
public:
    //------
    // Description:
    // Initializes the Vehicle class. Returns true if successful.
    // Precondition:
    // None
    bool init();

    //------
    // Description:
    // Shuts down the Vehicle class and cleans up resources.
    // Precondition:
    // Class must be initialized
    void shutdown();

    //------
    // Description:
    // Checks if license is valid for reservations. Returns true if valid.
    // Precondition:
    // License must exist in system
    bool checkLicenseForReservation(
        const std::string& license  // [in] Vehicle license to check
    );

    //------
    // Description:
    // Creates a standard vehicle for reservations. Returns true if successful.
    // Precondition:
    // Valid vehicle data and unique license
    bool createVehicleForReservation(
        const std::string& licensePlate,  // [in] Vehicle license plate
        const std::string& phoneNumber    // [in] Owner's phone number
    );

    //------
    // Description:
    // Creates a special vehicle for reservations. Returns true if successful.
    // Precondition:
    // Valid vehicle data and unique license
    bool createSpecialVehicleForReservation(
        const std::string& licensePlate,  // [in] Vehicle license plate
        const std::string& phoneNumber,   // [in] Owner's phone number
        float height,                     // [in] Vehicle height in meters
        float length                      // [in] Vehicle length in meters
    );

private:
    std::string currentLicensePlate;  // Currently processed vehicle license
    std::string currentPhoneNumber;   // Currently processed owner phone
    float currentHeight;              // Currently processed vehicle height (0 for regular)
    float currentLength;              // Currently processed vehicle length (0 for regular)
    bool isSpecialVehicle;            // Flag indicating special vehicle status
};