//*******************************
//*******************************
// vessel.h
// Description:
// This class handles all ferry vessel operations including creation, deletion,
// and capacity management for the ferry reservation system.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with private member variables
//*******************************

#include <string>

class Vessel {
public:
    //------
    // Description:
    // Initializes the Vessel class. Returns true if successful.
    // Precondition:
    // None
    bool init();

    //------
    // Description:
    // Shuts down the Vessel class and releases resources.
    // Precondition:
    // Class must be initialized
    void shutdown();

    //------
    // Description:
    // Checks if vessel is valid for sailings. Returns true if valid.
    // Precondition:
    // Vessel must exist in system
    bool checkVesselForSailing(
        const std::string& vesselName  // [in] Vessel name to validate
    );

    //------
    // Description:
    // Creates a new vessel record. Returns true if successful.
    // Precondition:
    // Valid vessel data and unique name
    bool createVessel(
        const std::string& name,            // [in] Unique vessel identifier
        float highCeilingLaneLength,        // [in] High ceiling capacity in meters
        float lowCeilingLaneLength,         // [in] Low ceiling capacity in meters
        unsigned int maxPassengers          // [in] Maximum passenger capacity
    );

    //------
    // Description:
    // Deletes a vessel record. Returns true if successful.
    // Precondition:
    // Vessel must exist and have no sailings
    bool deleteVessel(
        const std::string& vesselName  // [in] Vessel name to delete
    );

private:
    std::string currentName;                // Currently processed vessel name
    float currentHighCeilingLength;         // Current high ceiling capacity
    float currentLowCeilingLength;          // Current low ceiling capacity
    unsigned int currentMaxPassengers;      // Current passenger capacity
    bool isInitialized;                     // Flag indicating initialization status
};