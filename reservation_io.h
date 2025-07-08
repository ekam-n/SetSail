//*******************************
//*******************************
// reservation_io.h
// Description:
// This module handles all file input/output operations for Reservation records.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Created initial version with all file I/O operations
//*******************************

#include <vector>
#include "reservation.h"

//------
// Description:
// Opens the reservation data file. Returns true if successful.
// Precondition:
// None
bool open();

//------
// Description:
// Closes the reservation data file.
// Precondition:
// File must be open
void close();

//------
// Description:
// Resets the file iterator to beginning of file.
// Precondition:
// File must be open
void reset();

//------
// Description:
// Creates a new reservation record. Returns true if successful.
// Precondition:
// Valid reservation data
bool createReservation(
    const Reservation& res  // [in] Reservation to create
);

//------
// Description:
// Deletes a reservation record. Returns true if successful.
// Precondition:
// File must be open
bool deleteReservation(
    const std::string& sailingID,  // [in] Sailing ID of reservation
    const std::string& license     // [in] Vehicle license of reservation
);

//------
// Description:
// Gets all reservations for a license plate. Returns vector of reservations.
// Precondition:
// File must be open
std::vector<Reservation> getReservationsByLicense(
    const std::string& license  // [in] Vehicle license to search
);