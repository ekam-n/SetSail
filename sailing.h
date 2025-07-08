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
// Initializes sailing module. Returns true if successful.
// Precondition:
// None
bool init();

//------
// Description:
// Shuts down sailing module.
// Precondition:
// Module must be initialized
void shutdown();

//------
// Description:
// Adds occupants to a sailing. Returns true if successful.
// Precondition:
// Sailing must exist
bool addOccupants(
    const std::string& sailingID,  // [in] Sailing ID
    int people,                    // [in] Number of people
    float vehicleLength            // [in] Vehicle length
);

//------
// Description:
// Checks if vessel has sailings. Returns true if sailings exist.
// Precondition:
// Vessel must exist
bool checkVesselHasSailings(
    const std::string& vesselName  // [in] Vessel name
);

//------
// Description:
// Creates a new sailing. Returns true if successful.
// Precondition:
// Valid sailing data
bool createSailing(
    const Sailing& sailing  // [in] Sailing to create
);

//------
// Description:
// Deletes a sailing. Returns true if successful.
// Precondition:
// Sailing must exist
bool deleteSailing(
    const std::string& sailingID  // [in] Sailing ID
);

//------
// Description:
// Gets people occupants for reservation. Returns count.
// Precondition:
// Sailing must exist
int getPeopleOccupantsForReservation(
    const std::string& sailingID  // [in] Sailing ID
);

//------
// Description:
// Gets vehicle occupants. Returns total length.
// Precondition:
// Sailing must exist
float getVehicleOccupants(
    const std::string& sailingID  // [in] Sailing ID
);

//------
// Description:
// Gets vehicle occupants for reservation. Returns length.
// Precondition:
// Sailing must exist
float getVehicleOccupantsForReservation(
    const std::string& sailingID  // [in] Sailing ID
);

//------
// Description:
// Prints sailing report.
// Precondition:
// File must be open
void printSailingReport();