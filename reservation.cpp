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
    const std::string& sailingID,    // [in] Associated sailing ID
    const std::string& vehicleLicense, // [in] Vehicle license plate
    unsigned int occupants,           // [in] Number of people in vehicle
    const std::string phoneNumber     // [in] Phone Number for reservation
) {

    bool highCeilingReservation = false; // true = high, false = low
    float length = 4.0f;

    if (!Sailing::checkSailingExists(sailingID)) {
        std::cout << "Sailing does not exist.\n" << endl;
        return false;
    }

    if (!Sailing::checkSailingVehicleCapacity(sailingID)) {
        cout << "Sailing does not have vehicle capacity.\n" << endl;
        return false;
    } 

    if (!Sailing::checkSailingPeopleCapacity(sailingID, occupants)) {
        cout << "Sailing does not have person capacity.\n" << endl;
        return false;
    }

    if (!Sailing::getLowRemLaneLength(sailingID, length)) {
        if (!Sailing::getHighRemLaneLength(sailingID, length)) {
            cout << "No remaining lane space for vehicles.\n" << endl;
            return false;
        } else {
            highCeilingReservation = true;
        }
    } 

    Reservation res;
    res.currentSailingID = sailingID;
    res.currentVehicleLicense = vehicleLicense;
    res.currentFare = 14.0;
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
    res.currentOccupants = occupants;
    res.specialVehicleHeight = height;
    res.specialVehicleLength = length;

    return ReservationIO::createReservation(res);
}

//------
// Description:
// Checks in a vehicle for a reservation. Returns true if successful.
// Precondition:
// Reservation must exist
bool Reservation::logArrivals(const std::string& sailingID,  const std::string& license) {
    std::vector<Reservation> reservations = ReservationIO::getReservationsByLicense(license);
    for (const auto& res : reservations ) {
        if (res.currentSailingID == sailingID ) {
            std::cout << "Vehicle's fare is: $" << res.currentFare << std::endl;
            // Sailing::updateSailingForBoard(res.specialVehicleLength, res.currentOccupants);
            return true;
        }
    }
    return false;
}