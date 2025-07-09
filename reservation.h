//*******************************
//*******************************
// reservation.h
// Description:
// This class handles all reservation operations including creation, cancellation,
// and capacity checking for ferry sailings.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to proper class with private member variables
//*******************************

#include <string>

class Reservation {
public:
    //------
    // Description:
    // Initializes the Reservation class. Returns true if successful.
    // Precondition:
    // None
    bool init();

    //------
    // Description:
    // Shuts down the Reservation class and cleans up resources.
    // Precondition:
    // Class must be initialized
    void shutdown();

    //------
    // Description:
    // Cancels an existing reservation. Returns true if successful.
    // Precondition:
    // Reservation must exist
    bool cancelReservation(
        const std::string& sailingID,  // [in] Sailing ID of reservation
        const std::string& license     // [in] Vehicle license of reservation
    );

    //------
    // Description:
    // Checks in a vehicle for a reservation. Returns true if successful.
    // Precondition:
    // Reservation must exist
    bool checkIn(
        const std::string& sailingID,  // [in] Sailing ID of reservation
        const std::string& license     // [in] Vehicle license of reservation
    );

    //------
    // Description:
    // Creates a new reservation. Returns true if successful.
    // Precondition:
    // Valid reservation data
    bool createReservation(
        const std::string& sailingID,    // [in] Associated sailing ID
        const std::string& vehicleLicense, // [in] Vehicle license plate
        float fare,                      // [in] Calculated fare amount
        unsigned int occupants           // [in] Number of people in vehicle
    );

    //------
    // Description:
    // Creates a new special vehicle reservation. Returns true if successful.
    // Precondition:
    // Valid reservation data
    bool createSpecialReservation(
        const std::string& sailingID,    // [in] Associated sailing ID
        const std::string& vehicleLicense, // [in] Vehicle license plate
        float fare,                      // [in] Calculated fare amount
        unsigned int occupants,          // [in] Number of people in vehicle
        float height,                    // [in] Vehicle height in meters
        float length                     // [in] Vehicle length in meters
    );

    //------
    // Description:
    // Logs vehicle arrivals for a specific sailing.
    // Precondition:
    // Sailing must exist
    void logArrivals(
        const std::string& sailingID  // [in] Sailing ID to log arrivals for
    );

private:
    std::string currentSailingID;      // Current sailing ID being processed
    std::string currentVehicleLicense; // Current vehicle license being processed
    float currentFare;                 // Current fare amount
    unsigned int currentOccupants;     // Current number of occupants
    float specialVehicleHeight;        // Height for special vehicles
    float specialVehicleLength;       // Length for special vehicles
};