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

#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
    friend class ReservationIO;
    
public:
    //------
    // Description:
    // Initializes the Reservation class. Returns true if successful.
    // Precondition:
    // None
    static bool init();

    //------
    // Description:
    // Shuts down the Reservation class and cleans up resources.
    // Precondition:
    // Class must be initialized
    static void shutdown();

    //------
    // Description:
    // Cancels an existing reservation. Returns true if successful.
    // Precondition:
    // Reservation must exist
    static bool cancelReservation(
        const std::string& sailingID,  // [in] Sailing ID of reservation
        const std::string& license     // [in] Vehicle license of reservation
    );

    //------
    // Description:
    // Checks in a vehicle for a reservation. Returns true if successful.
    // Precondition:
    // Reservation must exist
    static bool checkIn(
        const std::string& sailingID,  // [in] Sailing ID of reservation
        const std::string& license     // [in] Vehicle license of reservation
    );

    //------
    // Description:
    // Creates a new reservation. Returns true if successful.
    // Precondition:
    // Valid reservation data
    static bool createReservation(
        const std::string& sailingID,    // [in] Associated sailing ID
        const std::string& vehicleLicense, // [in] Vehicle license plate
        unsigned int occupants           // [in] Number of people in vehicle
    );

    //------
    // Description:
    // Creates a new special vehicle reservation. Returns true if successful.
    // Precondition:
    // Valid reservation data
    static bool createSpecialReservation(
        const std::string& sailingID,    // [in] Associated sailing ID
        const std::string& vehicleLicense, // [in] Vehicle license plate
        unsigned int occupants,          // [in] Number of people in vehicle
        float height,                    // [in] Vehicle height in meters
        float length                     // [in] Vehicle length in meters
    );

    //------
    // Description:
    // Logs vehicle arrivals for a specific sailing.
    // Precondition:
    // Sailing must exist
    static void logArrivals(
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

#endif // RESERVATION_H