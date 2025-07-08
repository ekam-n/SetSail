//*******************************
//*******************************
// vessel.h
// Description:
// This module handles ferry vessel operations including creation, deletion,
// and capacity management.
//
// Revision History:
// Rev. 1 - 2025/07/06 - Team 12
// - Updated with all methods from OCD diagrams
//*******************************

#include <string>

// Vessel structure
struct Vessel {
    std::string name;               // [in] Unique vessel identifier
    float highCeilingLaneLength;    // [in] High ceiling lane capacity
    float lowCeilingLaneLength;     // [in] Low ceiling lane capacity
    unsigned int maxPassengers;     // [in] Maximum passenger capacity
};

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
// Returns true if successful, false if vessel doesn't exist or has sailings.
// Precondition:
// None
// Postcondition:
// Vessel is removed if no sailings exist for it
bool deleteVessel(
    const std::string& vesselName  // [in] Vessel to delete
);

//------
// Description:
// Checks if a vessel has any associated sailings.
// Returns true if sailings exist, false otherwise.
// Precondition:
// vesselName must exist
// Postcondition:
// None
bool vesselHasSailings(
    const std::string& vesselName  // [in] Vessel to check
);

//------
// Description:
// Finds a vessel by name.
// Returns true if found, false otherwise.
// Precondition:
// None
// Postcondition:
// If found, outVessel contains vessel data
bool findVessel(
    const std::string& vesselName,  // [in] Vessel to find
    Vessel& outVessel               // [out] Found vessel data
);