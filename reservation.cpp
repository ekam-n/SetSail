//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
#include "sailing.h"
#include "vehicle_io.h"
#include "vehicle.h"
#include <iostream>
#include <string>

float currentFare = 0.0f;                
unsigned int currentOccupants = 0;    
float specialVehicleHeight = 0.0f;       
float specialVehicleLength = 0.0f;  

using namespace std;

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
    float height = 0.0f;
    float length = 0.0f;
    std::vector<Reservation> reservations = ReservationIO::getReservationsByLicense(license);
    for (const auto& res : reservations ) {
        if (res.currentSailingID == sailingID ) {
            height = res.specialVehicleHeight;
            length = res.specialVehicleLength;
        }
    }
    int people = Sailing::getPeopleOccupantsForReservation(sailingID);
    if (height > 2.0 ) Sailing::updateSailingForHigh(sailingID, people, length);
    else Sailing::updateSailingForLow(sailingID, people, length);

    return ReservationIO::deleteReservation(sailingID, license);
}

//------
// Description:
// Creates a new reservation. Returns true if successful.
// Precondition:
// Valid reservation data
bool Reservation::createReservation(
    const std::string& sailingID,      // [in] Associated sailing ID
    const std::string& vehicleLicense, // [in] Vehicle license plate
    unsigned int occupants,            // [in] Number of people in vehicle
    const std::string phoneNumber      // [in] Phone Number for reservation
) {
    // standard vehicle length (metres)
    constexpr float vehicleLength = 4.0f;

    // 1) Sailing must exist
    if (!Sailing::checkSailingExists(sailingID)) {
        std::cout << "Sailing does not exist.\n";
        return false;
    }

    // 2) Must have vehicle capacity (any free lane)
    if (!Sailing::checkSailingVehicleCapacity(sailingID)) {
        std::cout << "Sailing does not have vehicle capacity.\n";
        return false;
    }

    // 3) Must have people capacity
    if (!Sailing::checkSailingPeopleCapacity(sailingID, occupants)) {
        std::cout << "Sailing does not have person capacity.\n";
        return false;
    }

    // 4) Try to fit into low-ceiling lane first
    if (Sailing::getLowRemLaneLength(sailingID, vehicleLength)) {
        Sailing::updateSailingForLow(sailingID, occupants, vehicleLength);

    // 5) Otherwise try high-ceiling lane
    } else if (Sailing::getHighRemLaneLength(sailingID, vehicleLength)) {
        Sailing::updateSailingForHigh(sailingID, occupants, vehicleLength);

    // 6) No room anywhere
    } else {
        std::cout << "No remaining lane space for vehicles.\n";
        return false;
    }

    // 7) Build and persist the reservation record
    Reservation res;
    res.currentSailingID       = sailingID;
    res.currentVehicleLicense  = vehicleLicense;
    res.currentFare            = 14.0f;  
    res.currentPeopleOccupants       = occupants;
    res.specialVehicleHeight   = 0.0f;
    res.specialVehicleLength   = 0.0f;

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
    unsigned int occupants,          // [in] Number of people in vehicle
    const std::string& phoneNumber,     // [in] Phone Number for reservation
    float height,                    // [in] Vehicle height in meters
    float length                     // [in] Vehicle length in meters
) {
    bool highCeilingReservation = false; // true = high, false = low
    float fare = 0.0f;

    if (!Sailing::checkSailingExists(sailingID)) {
        return false;
    }

    if (!Sailing::checkSailingVehicleCapacity(sailingID)) {
        return false;
    } 

    if (!Sailing::checkSailingPeopleCapacity(sailingID, occupants)) {
        return false;
    }

    if (!VehicleIO::checkVehicleExists(vehicleLicense)) {
        if ( height > 2.0 || length > 7.0 ) 
            Vehicle::createSpecialVehicleForReservation(vehicleLicense, phoneNumber, height, length);
        else
            Vehicle::createVehicleForReservation(vehicleLicense, phoneNumber);
    }

    if ( height > 2.0 ) {
        if (!Sailing::getHighRemLaneLength(sailingID, length)) {
            return false;
        }
        else {
            Sailing::updateSailingForHigh(sailingID, occupants, length);
            fare = length * 3.0;
        }
    } else {
        if (!Sailing::getLowRemLaneLength(sailingID, length)) {
            if (!Sailing::getHighRemLaneLength(sailingID, length)) {
                return false;
            } else {
                highCeilingReservation = true;
            }
        } else {
            if (highCeilingReservation) {
                Sailing::updateSailingForHigh(sailingID, occupants, length);
            } else {
                Sailing::updateSailingForLow(sailingID, occupants, length);
            }
            fare = length * 2.0;
        }

        return true;
    }
 
    Reservation res;
    res.currentSailingID = sailingID;
    res.currentVehicleLicense = vehicleLicense;
    res.currentFare = fare;
    res.currentPeopleOccupants = occupants;
    res.specialVehicleHeight = height;
    res.specialVehicleLength = length;

    return ReservationIO::createReservation(res);
}

//------
// Description:
// Checks in a vehicle for a reservation. Returns true if successful.
// Precondition:
// Reservation must exist
// In reservation.cpp

bool Reservation::logArrivals(const std::string& sailingID,
                              const std::string& license)
{
    // Get all reservations under this license
    std::vector<Reservation> reservations =
        ReservationIO::getReservationsByLicense(license);

    // Standard vehicle length when not a special reservation
    constexpr float defaultVehicleLength = 4.0f;

    for (const auto& res : reservations) {
        if (res.currentSailingID == sailingID) {
            // Print the fare
            std::cout << "Vehicle's fare is: $"
                      << res.currentFare << std::endl;

            // Determine length: use the special length if > 0, otherwise default
            float length = (res.specialVehicleLength > 0.0f)
                               ? res.specialVehicleLength
                               : defaultVehicleLength;

            // Update both people and vehicle space in one call
            return Sailing::updateOccupants(sailingID,
                                     res.currentPeopleOccupants,
                                     length);
        }
    }

    // No matching reservation found
    return false;
}
