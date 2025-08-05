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
bool Reservation::cancelReservation(const std::string& sailingID,
                                    const std::string& license)
{
    auto all = ReservationIO::getReservationsByLicense(license);
    for (const auto& res : all) {
        if (res.currentSailingID == sailingID) {
            float length = res.specialVehicleLength > 0.0f
                               ? res.specialVehicleLength
                               : 7.0f;
            if (res.usedHighLane)
               Sailing::updateSailingForHigh(sailingID, 0, -length);
             else
               Sailing::updateSailingForLow(sailingID, 0, -length);
           // only “undo” occupants if previously checked in
           if (res.checkedIn) {
             int   people = static_cast<int>(res.currentPeopleOccupants);
             Sailing::updateOccupants(sailingID, -people, -length);
           }
            break;
        }
    }
    // now remove the record itself
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
    
    bool usedHigh = false;

    // standard vehicle length (metres)
    constexpr float vehicleLength = 7.0f;

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
        usedHigh = false;

    // 5) Otherwise try high-ceiling lane
    } else if (Sailing::getHighRemLaneLength(sailingID, vehicleLength)) {
        Sailing::updateSailingForHigh(sailingID, occupants, vehicleLength);
        usedHigh = true;

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
    res.usedHighLane = usedHigh;

    return ReservationIO::createReservation(res);
}

//------
// Description:
// Creates a new special vehicle reservation. Returns true if successful.
// Precondition:
// Valid reservation data
bool Reservation::createSpecialReservation(
    const std::string& sailingID,
    const std::string& vehicleLicense,
    unsigned int       occupants,
    const std::string& phoneNumber,
    float              height,
    float              length
) {
    // 1. Basic checks (same as before)
    if (!Sailing::checkSailingExists(sailingID)
     || !Sailing::checkSailingVehicleCapacity(sailingID)
     || !Sailing::checkSailingPeopleCapacity(sailingID, occupants))
    {
        return false;
    }

    // 2. Register the vehicle if needed
    if (!VehicleIO::checkVehicleExists(vehicleLicense)) {
        if (height > 2.0f || length > 7.0f)
            Vehicle::createSpecialVehicleForReservation(
                vehicleLicense, phoneNumber, height, length);
        else
            Vehicle::createVehicleForReservation(
                vehicleLicense, phoneNumber);
    }

    // 3. Choose lane & compute fare
    bool usedHigh = false;
    float fare;
    // if it's tall, must go high
    if (height > 2.0f) {
        if (!Sailing::getHighRemLaneLength(sailingID, length))
            return false;
        Sailing::updateSailingForHigh(sailingID, occupants, length);
        usedHigh = true;
        fare = length * 3.0f;

    } else {
        // first try low
        if (Sailing::getLowRemLaneLength(sailingID, length)) {
            Sailing::updateSailingForLow(sailingID, occupants, length);
            fare = length * 2.0f;
            usedHigh = false;
        }
        // otherwise fall back to high
        else if (Sailing::getHighRemLaneLength(sailingID, length)) {
            Sailing::updateSailingForHigh(sailingID, occupants, length);
            usedHigh = true;
            fare = length * 3.0f;
        }
        else {
            return false; // no space anywhere
        }
    }

    // 4. Build and persist the reservation record
    Reservation res;
    res.currentSailingID         = sailingID;
    res.currentVehicleLicense    = vehicleLicense;
    res.currentFare              = fare;
    res.currentPeopleOccupants   = occupants;
    res.specialVehicleHeight     = height;
    res.specialVehicleLength     = length;
    res.usedHighLane = usedHigh;

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
    auto reservations = ReservationIO::getReservationsByLicense(license);
    for (const auto& res : reservations) {
        if (res.currentSailingID == sailingID) {
            std::cout << "Vehicle's fare is: $" << res.currentFare << std::endl;

            float length = (res.specialVehicleLength > 0.0f)
                                 ? res.specialVehicleLength
                                 : 7.0f;

            // 1) Perform the seating/count update
            bool ok = Sailing::updateOccupants(sailingID,
                                               res.currentPeopleOccupants,
                                               length);
            if (!ok) return false;

            // 2) Now mark this reservation as checked-in
            ReservationIO::markCheckedIn(sailingID, license);
            return true;
        }
    }
    return false;
}

