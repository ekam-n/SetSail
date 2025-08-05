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
// Deletes a reservation record. Returns true if successful, false if reservationd doesn't exist
bool ReservationIO::deleteReservation(const std::string& sailingID,
                                       const std::string& license)
{
    if (!isOpen) return false;

    std::vector<Reservation> allReservations;
    bool found = false;

    reset();
    Reservation temp;
    while (dataFile.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        // if this record matches the one to delete, skip it and mark "found"
        if (temp.currentSailingID == sailingID
         && temp.currentVehicleLicense == license) {
            found = true;
            continue;
        }
        allReservations.push_back(temp);
    }

    if (!found) return false;

    // rewrite file without the deleted record
    dataFile.close();
    isOpen = false;

    // reopen in read/write mode, truncating
    dataFile.open(fileName,
                  std::ios::in | std::ios::out    // << add input mode
                | std::ios::trunc | std::ios::binary);
    isOpen = dataFile.is_open();

    if (!isOpen) return false;

    for (const auto& r : allReservations) {
        dataFile.write(reinterpret_cast<const char*>(&r), sizeof r);
    }
    dataFile.flush();

    // reposition for future reads
    dataFile.clear();
    dataFile.seekg(0, std::ios::beg);

    return dataFile.good();
}

bool ReservationIO::markCheckedIn(const std::string& sailingID,
                                  const std::string& license)
{
    reset();
    Reservation temp;
    std::streamoff pos;
    while ((pos = dataFile.tellg()), dataFile.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (temp.currentSailingID == sailingID
         && temp.currentVehicleLicense == license) {
            temp.checkedIn = true;
            dataFile.clear();
            dataFile.seekp(pos);
            dataFile.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            dataFile.flush();
            return true;
        }
    }
    return false;
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