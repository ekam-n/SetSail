//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// reservation_io.h
// Description:
// This class handles all file input/output operations for Reservation records,
// providing persistent storage for reservation data.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with all file I/O operations
//*******************************

#include "reservation_io.h"
#include "reservation.h"
#include "vehicle.h"
#include <fstream>
#include <iostream>

static std::fstream dataFile;
static const std::string fileName = "reservations.dat"; // changed from currentFileName to fileName
static bool isOpen = false;

//------
// Description:
// Opens the reservation data file. Returns true if successful.
// Precondition:
// None
bool ReservationIO::open() {
    if (!isOpen) {
        dataFile.open(fileName, std::ios::in | std::ios::out | std::ios::binary);

        if (!dataFile.is_open()) {
            dataFile.open(fileName, std::ios::out | std::ios::binary); 
            dataFile.close();
            dataFile.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
        }
        
        isOpen = dataFile.is_open();
    }
    return isOpen;
}

//------
// Description:
// Closes the reservation data file.
// Precondition:
// File must be open
void ReservationIO::close() {
    if (isOpen) {
        dataFile.close();
        isOpen = false;
    }
}

//------
// Description:
// Resets the file iterator to beginning of file.
// Precondition:
// File must be open
void ReservationIO::reset() {
    if (isOpen) {
        dataFile.clear();
        dataFile.seekg(0, std::ios::beg);
    }
}

//------
// Description:
// Creates a new reservation record. Returns true if successful.
// Precondition:
// Valid reservation data
bool ReservationIO::createReservation( const Reservation& res) {
    if (!isOpen) return false;
    dataFile.clear();
    dataFile.seekp(0, std::ios::end);

    dataFile.write(reinterpret_cast<const char*>(&res), sizeof(Reservation));
    return dataFile.good();
} 

//------
// Description:
// Deletes a reservation record. Returns true if successful.
// Precondition:
// File must be open
bool ReservationIO::deleteReservation(const std::string& sailingID, const std::string& license) {
    if (!isOpen) return false;

    std::vector<Reservation> allReservations;
    reset();

    Reservation temp;
    while (dataFile.read(reinterpret_cast<char*>(&temp), sizeof(Reservation))) {
        if (temp.currentSailingID != sailingID || temp.currentVehicleLicense != license) {
            allReservations.push_back(temp);
        }
    }

    // Rewrite file
    dataFile.close();
    dataFile.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);
    for (const auto& r : allReservations) {
        dataFile.write(reinterpret_cast<const char*>(&r), sizeof(Reservation));
    }

    return true;
}

//------
// Description:
// Gets all reservations for a license plate. Returns vector of reservations.
// Precondition:
// File must be open
std::vector<Reservation> ReservationIO::getReservationsByLicense(const std::string& license) {
    std::vector<Reservation> matches;
    if (!isOpen) return matches;
    reset();
    Reservation temp;
    while (dataFile.read(reinterpret_cast<char*>(&temp), sizeof(Reservation))) {
        if (temp.currentVehicleLicense == license) {
            matches.push_back(temp);
        }
    }
    return matches;
}