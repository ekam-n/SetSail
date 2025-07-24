//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// vehicle_io.cpp
// Description:
// Implementation of the VehicleIO class which handles all file I/O operations
// for Vehicle records, providing persistent storage for vehicle data.
//
// Implementation Notes:
// - Uses fixed-length binary records for storage
// - File operations are unsorted (as per assignment requirements)
// - Implements simple linear search for record retrieval
//
// Revision History:
// Rev. 1 - 2025/07/16 - Team 12
// - Initial implementation
//*******************************

#include "vehicle_io.h"
#include <fstream>
#include <iostream>

// Private constants
const std::string VEHICLE_FILE_NAME = "vehicles.dat";
const size_t LICENSE_LENGTH = 20; // Fixed length for license plate storage
const size_t PHONE_LENGTH = 15;   // Fixed length for phone number storage

// Private file structure for binary storage
#pragma pack(push, 1) // Ensure no padding between struct members
struct VehicleRecord {
    char license[LICENSE_LENGTH]; // Fixed length string storage
    char phone[PHONE_LENGTH];    // Fixed length string storage
    float height;
    float length;
    bool isSpecial;
};
#pragma pack(pop)

// Private module variables
static std::fstream vehicleFile;
static bool fileIsOpen = false;

//------
// Description:
// Opens the vehicle data file. Returns true if successful.
// Implementation:
// Opens file in binary read/write mode, creates if doesn't exist
// Precondition:
// None
bool VehicleIO::open() {
    if (fileIsOpen) return true;
    
    vehicleFile.open(VEHICLE_FILE_NAME, 
                    std::ios::in | std::ios::out | std::ios::binary);
    
    if (!vehicleFile) {
        // File doesn't exist, create it
        vehicleFile.open(VEHICLE_FILE_NAME, 
                        std::ios::out | std::ios::binary);
        if (!vehicleFile) return false;
        vehicleFile.close();
        
        // Reopen in read/write mode
        vehicleFile.open(VEHICLE_FILE_NAME, 
                        std::ios::in | std::ios::out | std::ios::binary);
        if (!vehicleFile) return false;
    }
    
    fileIsOpen = true;
    return true;
}

//------
// Description:
// Closes the vehicle data file.
// Precondition:
// File must be open
void VehicleIO::close() {
    if (fileIsOpen) {
        vehicleFile.close();
        fileIsOpen = false;
    }
}

//------
// Description:
// Resets the file iterator to beginning of file.
// Precondition:
// File must be open
void VehicleIO::reset() {
    if (fileIsOpen) {
        vehicleFile.clear(); // Clear any error flags
        vehicleFile.seekg(0, std::ios::beg);
    }
}

//------
// Description:
// Checks if a vehicle exists in the system. Returns true if found.
// Implementation:
// Performs linear search through file for matching license
// Precondition:
// File must be open
bool VehicleIO::checkVehicleExists(const std::string& license) {
    if (!fileIsOpen || license.empty()) return false;
    
    reset();
    VehicleRecord record;
    
    // Search through all records
    while (vehicleFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if (strncmp(record.license, license.c_str(), LICENSE_LENGTH) == 0) {
            return true;
        }
    }
    
    return false;
}

//------
// Description:
// Creates a new special vehicle record. Returns true if successful.
// Implementation:
// Converts Vehicle object to fixed-length record and appends to file
// Precondition:
// Valid vehicle data and unique license
bool VehicleIO::createSpecialVehicle(const Vehicle& vehicle) {
    if (!fileIsOpen) return false;
    
    VehicleRecord record;
    memset(&record, 0, sizeof(record)); // Initialize all bytes to 0
    
    // Copy license plate (ensuring fixed length)
    strncpy(record.license, vehicle.currentLicensePlate.c_str(), LICENSE_LENGTH - 1);
    record.license[LICENSE_LENGTH - 1] = '\0';
    
    // Copy phone number (ensuring fixed length)
    strncpy(record.phone, vehicle.currentPhoneNumber.c_str(), PHONE_LENGTH - 1);
    record.phone[PHONE_LENGTH - 1] = '\0';
    
    record.height = vehicle.currentHeight;
    record.length = vehicle.currentLength;
    record.isSpecial = true;
    
    // Append to end of file
    vehicleFile.seekp(0, std::ios::end);
    vehicleFile.write(reinterpret_cast<const char*>(&record), sizeof(record));
    
    return vehicleFile.good();
}

//------
// Description:
// Creates a new standard vehicle record. Returns true if successful.
// Implementation:
// Similar to createSpecialVehicle but with isSpecial = false
// Precondition:
// Valid vehicle data and unique license
bool VehicleIO::createVehicle(const Vehicle& vehicle) {
    if (!fileIsOpen) return false;
    
    VehicleRecord record;
    memset(&record, 0, sizeof(record)); // Initialize all bytes to 0
    
    // Copy license plate (ensuring fixed length)
    strncpy(record.license, vehicle.currentLicensePlate.c_str(), LICENSE_LENGTH - 1);
    record.license[LICENSE_LENGTH - 1] = '\0';
    
    // Copy phone number (ensuring fixed length)
    strncpy(record.phone, vehicle.currentPhoneNumber.c_str(), PHONE_LENGTH - 1);
    record.phone[PHONE_LENGTH - 1] = '\0';
    
    record.height = 0.0f;
    record.length = 0.0f;
    record.isSpecial = false;
    
    // Append to end of file
    vehicleFile.seekp(0, std::ios::end);
    vehicleFile.write(reinterpret_cast<const char*>(&record), sizeof(record));
    
    return vehicleFile.good();
}