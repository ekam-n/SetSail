//*******************************
//*******************************
// vehicle.h
// Description:
// This module handles vehicle operations including creation and lookup.
//
// Revision History:
// Rev. 1 - 2025/07/06 - Team 12
// - Updated with all methods from OCD diagrams
//*******************************

#include <string>

// Vehicle structure (roll-up implementation)
struct Vehicle {
    std::string licensePlate;  // [in] Vehicle license plate (primary key)
    std::string phoneNumber;   // [in] Owner's phone number
    float height;              // [in] Vehicle height in meters (0 for regular)
    float length;              // [in] Vehicle length in meters (0 for regular)
};

//------
// Description:
// Initializes vehicle module. Returns true if successful.
// Precondition:
// None
bool init();

//------
// Description:
// Shuts down vehicle module.
// Precondition:
// Module must be initialized
void shutdown();

//------
// Description:
// Checks license for reservation. Returns true if valid.
// Precondition:
// License must exist
bool checkLicenseForReservation(
    const std::string& license  // [in] Vehicle license
);

//------
// Description:
// Creates vehicle for reservation. Returns true if successful.
// Precondition:
// Valid vehicle data
bool createVehicleForReservation(
    const Vehicle& vehicle  // [in] Vehicle to create
);

//------
// Description:
// Creates special vehicle for reservation. Returns true if successful.
// Precondition:
// Valid vehicle data
bool createSpecialVehicleForReservation(
    const Vehicle& vehicle,  // [in] Vehicle data
    float height,            // [in] Vehicle height
    float length             // [in] Vehicle length
);