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
// Initializes vessel module. Returns true if successful.
// Precondition:
// None
bool init();

//------
// Description:
// Shuts down vessel module.
// Precondition:
// Module must be initialized
void shutdown();

//------
// Description:
// Checks vessel for sailing. Returns true if valid.
// Precondition:
// Vessel must exist
bool checkVesselForSailing(
    const std::string& vesselName  // [in] Vessel name
);

//------
// Description:
// Creates a new vessel. Returns true if successful.
// Precondition:
// Valid vessel data
bool createVessel(
    const Vessel& vessel  // [in] Vessel to create
);

//------
// Description:
// Deletes a vessel. Returns true if successful.
// Precondition:
// Vessel must exist
bool deleteVessel(
    const std::string& vesselName  // [in] Vessel name
);