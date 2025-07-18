//*******************************
//*******************************
// reservation.cpp
// Description:
// This class handles all reservation operations including creation, cancellation,
// and capacity checking for ferry sailings.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to proper class with private member variables
//*******************************

#include "reservation.h"
#include "reservation_io.h"
#include <iostream>
#include <string>

float currentFare = 0.0f;                
unsigned int currentOccupants = 0;    
float specialVehicleHeight = 0.0f;       
float specialVehicleLength = 0.0f;  

//------
// Description:
// Initializes the Reservation class. Returns true if successful.
// Precondition:
// None
bool Reservation::init() {
    return ReservationIO::open(); 
}

//------
// Description:
// Shuts down the Reservation class and cleans up resources.
// Precondition:
// Class must be initialized
void Reservation::shutdown() {
    ReservationIO::close();
}

//------
// Description:
// Cancels an existing reservation. Returns true if successful.
// Precondition:
// Reservation must exist
bool Reservation::cancelReservation(const std::string& sailingID, const std::string& license) {
    return ReservationIO::deleteReservation(sailingID, license);
}

//------
// Description:
// Checks in a vehicle for a reservation. Returns true if successful.
// Precondition:
// Reservation must exist
bool Reservation::checkIn(const std::string& sailingID,  const std::string& license) {
    std::vector<Reservation> reservations = ReservationIO::getReservationsByLicense(license);
    for (const auto& res : reservations ) {
        if (res.currentSailingID == sailingID ) {
            std::cout << "Vehicle fare:" << res.currentFare << std::endl;
            return true;
        }
    }
    return false;
}

//------
// Description:
// Creates a new reservation. Returns true if successful.
// Precondition:
// Valid reservation data
bool Reservation::createReservation(
    const std::string& sailingID,    // [in] Associated sailing ID
    const std::string& vehicleLicense, // [in] Vehicle license plate
    float fare,                      // [in] Calculated fare amount
    unsigned int occupants           // [in] Number of people in vehicle
) {
    Reservation res;
    res.currentSailingID = sailingID;
    res.currentVehicleLicense = vehicleLicense;
    res.currentFare = fare;
    res.currentOccupants = occupants;
    res.specialVehicleHeight = 0.0f;
    res.specialVehicleLength = 0.0f;

    return ReservationIO::createReservation(res);
}

//------
// Description:
// Creates a new special vehicle reservation. Returns true if successful.
// Precondition:
// Valid reservation data
bool Reservation::createSpecialReservation(
    const std::string& sailingID,    // [in] Associated sailing ID
    const std::string& vehicleLicense, // [in] Vehicle license plate
    float fare,                      // [in] Calculated fare amount
    unsigned int occupants,          // [in] Number of people in vehicle
    float height,                    // [in] Vehicle height in meters
    float length                     // [in] Vehicle length in meters
) {
    Reservation res;
    res.currentSailingID = sailingID;
    res.currentVehicleLicense = vehicleLicense;
    res.currentFare = fare;
    res.currentOccupants = occupants;
    res.specialVehicleHeight = height;
    res.specialVehicleLength = length;

    return ReservationIO::createReservation(res);
}

//------
// Description:
// Logs vehicle arrivals for a specific sailing.
// Precondition:
// Sailing must exist
void Reservation::logArrivals(const std::string& sailingID) {
    // success msg? 
}