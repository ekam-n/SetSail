//*******************************
//*******************************
// vessel.h
// Description:
// This module handles ferry vessel operations including creation and deletion,
// and maintains vessel capacity information.
//
// Revision History:
// Rev. 1 - 2025/07/05 - Team 12
// - Created initial version with basic vessel operations
//*******************************

#include <string>

//------
// Description:
// Creates a new ferry vessel record.
// Returns true if successful, false if vessel name exists.
// Precondition:
// vesselName must be unique
// Postcondition:
// New vessel is added to the system
bool createVessel(
    const std::string& vesselName,    // [in] Unique vessel identifier
    float highCeilingLaneLength,      // [in] High ceiling lane capacity
    float lowCeilingLaneLength,       // [in] Low ceiling lane capacity
    unsigned int maxPassengers        // [in] Maximum passenger capacity
);

//------
// Description:
// Deletes a vessel by name.
// Returns true if successful, false if vessel doesn't exist.
// Precondition:
// Vessel must have no associated sailings
// Postcondition:
// Vessel is removed from the system
bool deleteVessel(
    const std::string& vesselName  // [in] Vessel to delete
);