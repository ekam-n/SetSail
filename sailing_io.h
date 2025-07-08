//*******************************
//*******************************
// sailing_io.h
// Description:
// This module handles all file input/output operations for Sailing records.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Created initial version with all file I/O operations
//*******************************

#include <vector>
#include "sailing.h"

//------
// Description:
// Opens the sailing data file. Returns true if successful.
// Precondition:
// None
bool open();

//------
// Description:
// Closes the sailing data file.
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
// Adds people occupants to a sailing. Returns true if successful.
// Precondition:
// Sailing must exist
bool addPeopleOccupants(
    const std::string& sailingID,  // [in] Sailing ID to update
    int count                      // [in] Number of people to add
);

//------
// Description:
// Adds vehicle occupants to a sailing. Returns true if successful.
// Precondition:
// Sailing must exist
bool addVehicleOccupants(
    const std::string& sailingID,  // [in] Sailing ID to update
    float length                   // [in] Vehicle length to add
);

//------
// Description:
// Checks if sailings exist for a vessel. Returns true if sailings exist.
// Precondition:
// Vessel must exist
bool checkSailingsForVessel(
    const std::string& vesselName  // [in] Vessel name to check
);

//------
// Description:
// Creates a new sailing record. Returns true if successful.
// Precondition:
// Valid sailing data
bool createSailing(
    const Sailing& sailing  // [in] Sailing to create
);

//------
// Description:
// Deletes a sailing record. Returns true if successful.
// Precondition:
// File must be open
bool deleteSailing(
    const std::string& sailingID  // [in] Sailing ID to delete
);

//------
// Description:
// Gets people occupants for a sailing. Returns occupant count.
// Precondition:
// Sailing must exist
int getPeopleOccupants(
    const std::string& sailingID  // [in] Sailing ID to query
);

//------
// Description:
// Gets vehicle occupants for a sailing. Returns total vehicle length.
// Precondition:
// Sailing must exist
float getVehicleOccupants(
    const std::string& sailingID  // [in] Sailing ID to query
);

//------
// Description:
// Prints sailing report.
// Precondition:
// File must be open
void printSailingReport();