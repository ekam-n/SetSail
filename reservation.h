//*******************************
//*******************************
// reservation.h
// Description:
// This module handles reservation operations including creation, cancellation,
// and capacity checking for ferry sailings.
//
// Revision History:
// Rev. 1 - 2025/07/05 - Team 12
// - Created initial version with basic reservation operations
//*******************************

#include <string>

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
    int occupants,                     // [in] Number of people in vehicle
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