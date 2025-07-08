//*******************************
//*******************************
// sailing.h
// Description:
// This module handles sailing operations including creation, deletion,
// and capacity management.
//
// Revision History:
// Rev. 1 - 2025/07/06 - Team 12
// - Updated with all methods from OCD diagrams
//*******************************

#include <string>

// Sailing structure
struct Sailing {
    std::string sailingID;          // [in] Unique sailing identifier
    std::string vesselName;         // [in] Name of vessel for this sailing
    std::string departureTerminal;  // [in] Departure terminal code
    std::string departureDay;       // [in] Departure day (DD format)
    std::string departureTime;      // [in] Departure time (HH:MM format)
    float highRemainingLength;      // [in/out] Remaining high ceiling capacity
    float lowRemainingLength;       // [in/out] Remaining low ceiling capacity
    unsigned int onBoard;           // [in/out] Current passenger count
};

//------
// Description:
// Creates a new sailing with the specified parameters.
// Returns true if successful, false if vessel doesn't exist or sailingID exists.
// Precondition:
// vesselName must exist in the system
// sailingID must be unique
// Postcondition:
// New sailing is created with initial capacity values
bool createSailing(
    const std::string& sailingID,     // [in] Unique sailing identifier
    const std::string& vesselName,    // [in] Name of vessel for this sailing
    const std::string& departureTerm, // [in] Departure terminal code
    const std::string& departureDay,  // [in] Departure day (DD format)
    const std::string& departureTime  // [in] Departure time (HH:MM format)
);

//------
// Description:
// Deletes a sailing by ID.
// Returns true if successful, false if sailing doesn't exist.
// Precondition:
// None
// Postcondition:
// Sailing is removed if it existed
bool deleteSailing(
    const std::string& sailingID  // [in] Sailing ID to delete
);

//------
// Description:
// Gets sailing details including current capacity.
// Returns true if found, false otherwise.
// Precondition:
// None
// Postcondition:
// If found, outSailing contains sailing data
bool getSailingDetails(
    const std::string& sailingID,  // [in] Sailing to find
    Sailing& outSailing            // [out] Found sailing data
);

//------
// Description:
// Checks if a sailing exists.
// Returns true if exists, false otherwise.
// Precondition:
// None
// Postcondition:
// None
bool sailingExists(
    const std::string& sailingID  // [in] Sailing to check
);