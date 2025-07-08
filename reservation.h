//*******************************
//*******************************
// reservation.h
// Description:
// This module handles reservation operations including creation, cancellation,
// and capacity checking.
//
// Revision History:
// Rev. 1 - 2025/07/06 - Team 12
// - Updated with all methods from OCD diagrams
//*******************************

#include <string>

// Reservation structure
struct Reservation {
    std::string sailingID;        // [in] Associated sailing
    std::string vehicleLicense;   // [in] Vehicle making reservation
    float fare;                   // [in] Calculated fare amount
    unsigned int occupants;       // [in] Number of people in vehicle
};

//------
// Description:
// Creates a new reservation for a sailing.
// Returns true if successful, false if sailing is full or doesn't exist.
// Precondition:
// sailingID and vehicleLicense must exist
// Postcondition:
// Reservation is created if capacity allows
bool createReservation(
    const std::string& sailingID,      // [in] Sailing to reserve
    const std::string& vehicleLicense, // [in] Vehicle making reservation
    unsigned int occupants,            // [in] Number of people in vehicle
    float& outFare                     // [out] Calculated fare amount
);

//------
// Description:
// Creates a new special vehicle reservation (handles vehicle creation if needed).
// Returns true if successful, false if capacity issues.
// Precondition:
// sailingID must exist
// Postcondition:
// Reservation and possibly new vehicle are created
bool createSpecialReservation(
    const std::string& sailingID,      // [in] Sailing to reserve
    const std::string& vehicleLicense, // [in] Vehicle making reservation
    unsigned int occupants,            // [in] Number of people in vehicle
    float height,                      // [in] Vehicle height
    float length,                      // [in] Vehicle length
    const std::string& phoneNumber,    // [in] Owner's phone number
    float& outFare                     // [out] Calculated fare amount
);

//------
// Description:
// Cancels an existing reservation.
// Returns true if successful, false if reservation doesn't exist.
// Precondition:
// None
// Postcondition:
// Reservation is removed and capacity is updated
bool cancelReservation(
    const std::string& sailingID,      // [in] Sailing to cancel from
    const std::string& vehicleLicense  // [in] Vehicle to cancel
);

//------
// Description:
// Checks if a sailing has capacity for additional people.
// Returns true if capacity available, false otherwise.
// Precondition:
// sailingID must exist
// Postcondition:
// None
bool hasPeopleCapacity(
    const std::string& sailingID,  // [in] Sailing to check
    unsigned int additionalPeople   // [in] Number of people to check for
);

//------
// Description:
// Checks if a sailing has capacity for a vehicle of given dimensions.
// Returns true if capacity available, false otherwise.
// Precondition:
// sailingID must exist
// Postcondition:
// None
bool hasVehicleCapacity(
    const std::string& sailingID,  // [in] Sailing to check
    float height,                  // [in] Vehicle height
    float length                   // [in] Vehicle length
);