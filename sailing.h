//*******************************
//*******************************
// sailing.h
// Description:
// This module handles sailing operations including creation, deletion,
// and capacity management for ferry sailings.
//
// Revision History:
// Rev. 1 - 2025/07/05 - Team 12
// - Created initial version with basic sailing operations
//*******************************

#include <string>

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