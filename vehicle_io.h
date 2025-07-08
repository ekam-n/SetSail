//*******************************
//*******************************
// vehicle_io.h
// Description:
// This module handles all file input/output operations for Vehicle records.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Created initial version with all file I/O operations
//*******************************

#include "vehicle.h"

//------
// Description:
// Opens the vehicle data file. Returns true if successful.
// Precondition:
// None
bool open();

//------
// Description:
// Closes the vehicle data file.
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
// Checks if a vehicle exists. Returns true if exists.
// Precondition:
// File must be open
bool checkVehicleExists(
    const std::string& license  // [in] Vehicle license to check
);

//------
// Description:
// Creates a new special vehicle record. Returns true if successful.
// Precondition:
// Valid vehicle data
bool createSpecialVehicle(
    const Vehicle& vehicle  // [in] Special vehicle to create
);

//------
// Description:
// Creates a new vehicle record. Returns true if successful.
// Precondition:
// Valid vehicle data
bool createVehicle(
    const Vehicle& vehicle  // [in] Vehicle to create
);