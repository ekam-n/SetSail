//*******************************
//*******************************
// sailing.h
// Description:
// This class handles all sailing operations including creation, deletion,
// and capacity management for ferry sailings.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with private member variables
//*******************************

#include <string>

class Sailing {
public:
    //------
    // Description:
    // Initializes the Sailing class. Returns true if successful.
    // Precondition:
    // None
    bool init();

    //------
    // Description:
    // Shuts down the Sailing class and cleans up resources.
    // Precondition:
    // Class must be initialized
    void shutdown();

    //------
    // Description:
    // Adds occupants to a sailing. Returns true if successful.
    // Precondition:
    // Sailing must exist
    bool addOccupants(
        const std::string& sailingID,  // [in] Sailing ID to update
        int people,                    // [in] Number of people to add
        float vehicleLength            // [in] Vehicle length to add
    );

    //------
    // Description:
    // Checks if vessel has associated sailings. Returns true if found.
    // Precondition:
    // Vessel must exist
    bool checkVesselHasSailings(
        const std::string& vesselName  // [in] Vessel name to check
    );

    //------
    // Description:
    // Creates a new sailing. Returns true if successful.
    // Precondition:
    // Valid sailing data
    bool createSailing(
        const std::string& sailingID,      // [in] Unique sailing identifier
        const std::string& vesselName,     // [in] Name of vessel
        const std::string& departureTerm,  // [in] Departure terminal code
        const std::string& departureDay,   // [in] Departure day (DD)
        const std::string& departureTime   // [in] Departure time (HH:MM)
    );

    //------
    // Description:
    // Deletes a sailing. Returns true if successful.
    // Precondition:
    // Sailing must exist
    bool deleteSailing(
        const std::string& sailingID  // [in] Sailing ID to delete
    );

    //------
    // Description:
    // Gets people occupant count for reservation. Returns -1 if error.
    // Precondition:
    // Sailing must exist
    int getPeopleOccupantsForReservation(
        const std::string& sailingID  // [in] Sailing ID to query
    );

    //------
    // Description:
    // Gets total vehicle length occupied. Returns -1.0 if error.
    // Precondition:
    // Sailing must exist
    float getVehicleOccupants(
        const std::string& sailingID  // [in] Sailing ID to query
    );

    //------
    // Description:
    // Gets vehicle length for reservation. Returns -1.0 if error.
    // Precondition:
    // Sailing must exist
    float getVehicleOccupantsForReservation(
        const std::string& sailingID  // [in] Sailing ID to query
    );

    //------
    // Description:
    // Prints formatted sailing report to standard output.
    // Precondition:
    // System must be initialized
    void printSailingReport();

private:
    std::string currentSailingID;          // Active sailing identifier
    std::string currentVesselName;         // Associated vessel name
    std::string currentDepartureTerminal;  // Departure terminal code
    std::string currentDepartureDay;       // Departure day (DD format)
    std::string currentDepartureTime;      // Departure time (HH:MM format)
    float currentHighRemainingLength;      // Remaining high ceiling capacity
    float currentLowRemainingLength;       // Remaining low ceiling capacity
    unsigned int currentOnBoardCount;      // Current passenger count
};