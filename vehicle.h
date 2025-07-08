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
// Creates a new vehicle record in the system.
// Returns true if successful, false if vehicle already exists.
// Precondition:
// licensePlate must be unique
// Postcondition:
// New vehicle is added to persistent storage
bool createVehicle(
    const std::string& licensePlate,  // [in] Vehicle license plate
    const std::string& phoneNumber,   // [in] Owner's phone number
    float height,                     // [in] Vehicle height (0 for regular)
    float length                      // [in] Vehicle length (0 for regular)
);

//------
// Description:
// Creates a new special vehicle record.
// Returns true if successful, false if vehicle already exists.
// Precondition:
// licensePlate must be unique
// Postcondition:
// New special vehicle is added to persistent storage
bool createSpecialVehicle(
    const std::string& licensePlate,  // [in] Vehicle license plate
    const std::string& phoneNumber,   // [in] Owner's phone number
    float height,                     // [in] Vehicle height (>2m)
    float length                      // [in] Vehicle length (>7m)
);

//------
// Description:
// Finds a vehicle by license plate.
// Returns true if found, false otherwise.
// Precondition:
// None
// Postcondition:
// If found, outVehicle contains the vehicle data
bool findVehicle(
    const std::string& licensePlate,  // [in] Vehicle license to search for
    Vehicle& outVehicle               // [out] Found vehicle data
);

//------
// Description:
// Checks if a vehicle exists in the system.
// Returns true if exists, false otherwise.
// Precondition:
// None
// Postcondition:
// None
bool vehicleExists(
    const std::string& licensePlate  // [in] Vehicle license to check
);