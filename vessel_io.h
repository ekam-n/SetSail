//*******************************
//*******************************
// vessel_io.h
// Description:
// This module handles all file input/output operations for Vessel records.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Created initial version with all file I/O operations
//*******************************

#include "vessel.h"

//------
// Description:
// Opens the vessel data file. Returns true if successful.
// Precondition:
// None
bool open();

//------
// Description:
// Closes the vessel data file.
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
// Checks if a vessel exists. Returns true if exists.
// Precondition:
// File must be open
bool checkVesselExists(
    const std::string& vesselName  // [in] Vessel name to check
);

//------
// Description:
// Creates a new vessel record. Returns true if successful.
// Precondition:
// Valid vessel data
bool createVessel(
    const Vessel& vessel  // [in] Vessel to create
);

//------
// Description:
// Deletes a vessel record. Returns true if successful.
// Precondition:
// File must be open
bool deleteVessel(
    const std::string& vesselName  // [in] Vessel name to delete
);