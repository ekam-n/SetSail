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
// Initializes reservation module. Returns true if successful.
// Precondition:
// None
bool init();

//------
// Description:
// Shuts down reservation module.
// Precondition:
// Module must be initialized
void shutdown();

//------
// Description:
// Cancels a reservation. Returns true if successful.
// Precondition:
// Reservation must exist
bool cancelReservation(
    const std::string& sailingID,  // [in] Sailing ID
    const std::string& license     // [in] Vehicle license
);

//------
// Description:
// Checks in a reservation. Returns true if successful.
// Precondition:
// Reservation must exist
bool checkIn(
    const std::string& sailingID,  // [in] Sailing ID
    const std::string& license     // [in] Vehicle license
);

//------
// Description:
// Creates a new reservation. Returns true if successful.
// Precondition:
// Valid reservation data
bool createReservation(
    const Reservation& res  // [in] Reservation to create
);

//------
// Description:
// Creates a new special reservation. Returns true if successful.
// Precondition:
// Valid reservation data
bool createSpecialReservation(
    const Reservation& res,  // [in] Reservation data
    float height,            // [in] Vehicle height
    float length             // [in] Vehicle length
);

//------
// Description:
// Logs vehicle arrivals for a sailing.
// Precondition:
// Sailing must exist
void logArrivals(
    const std::string& sailingID  // [in] Sailing ID
);