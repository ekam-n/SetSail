//*******************************
//*******************************
// vehicle_io.h
// Description:
// This class handles all file input/output operations for Vehicle records,
// providing persistent storage for vehicle data including special vehicles.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with all file I/O operations
//*******************************

#include "vehicle.h"

class VehicleIO {
public:
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
    // Checks if a vehicle exists in the system. Returns true if found.
    // Precondition:
    // File must be open
    bool checkVehicleExists(
        const std::string& license  // [in] Vehicle license to check
    );

    //------
    // Description:
    // Creates a new special vehicle record. Returns true if successful.
    // Precondition:
    // Valid vehicle data and unique license
    bool createSpecialVehicle(
        const Vehicle& vehicle  // [in] Special vehicle to create
    );

    //------
    // Description:
    // Creates a new standard vehicle record. Returns true if successful.
    // Precondition:
    // Valid vehicle data and unique license
    bool createVehicle(
        const Vehicle& vehicle  // [in] Vehicle to create
    );

private:
    // Private implementation details
    // std::fstream vehicleFile;
    // std::string currentFileName;
    // bool fileIsOpen;
    // size_t currentRecordPosition;
};