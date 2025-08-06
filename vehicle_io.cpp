//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
// Rev. 2 - 2025/08/05 - Updated to use fixed-size records for persistence

#include "vehicle_io.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Private constants
static const std::string VEHICLE_FILE_NAME = "vehicles.dat";
static const size_t LICENSE_LENGTH    = 20; // Fixed length for license plate storage
static const size_t PHONE_LENGTH      = 15; // Fixed length for phone number storage

// Private file structure for binary storage
#pragma pack(push, 1)
struct VehicleRecord {
    char   license[LICENSE_LENGTH];
    char   phone[PHONE_LENGTH];
    float  height;
    float  length;
    bool   isSpecial;
};
#pragma pack(pop)

// Private module variables
static std::fstream vehicleFile;
static bool fileIsOpen = false;

bool VehicleIO::open() {
    if (fileIsOpen) return true;
    // try open existing
    vehicleFile.open(VEHICLE_FILE_NAME,
                     std::ios::in | std::ios::out | std::ios::binary);
    if (!vehicleFile) {
        // create then reopen
        vehicleFile.open(VEHICLE_FILE_NAME,
                         std::ios::out | std::ios::binary);
        if (!vehicleFile) return false;
        vehicleFile.close();
        vehicleFile.open(VEHICLE_FILE_NAME,
                         std::ios::in | std::ios::out | std::ios::binary);
        if (!vehicleFile) return false;
    }
    fileIsOpen = true;
    return true;
}

void VehicleIO::close() {
    if (fileIsOpen) {
        vehicleFile.close();
        fileIsOpen = false;
    }
}

void VehicleIO::reset() {
    if (fileIsOpen) {
        vehicleFile.clear();
        vehicleFile.seekg(0, std::ios::beg);
    }
}

bool VehicleIO::checkVehicleExists(const std::string& license) {
    if (!fileIsOpen || license.empty()) return false;
    reset();
    VehicleRecord record;
    while (vehicleFile.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        // compare only up to null-terminator
        if (std::strncmp(record.license, license.c_str(), LICENSE_LENGTH) == 0) {
            return true;
        }
    }
    return false;
}

bool VehicleIO::checkVehicleIsSpecial(const std::string& license) {
    if (!fileIsOpen || license.empty()) return false;
    reset();
    VehicleRecord rec;
    while (vehicleFile.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (std::strncmp(rec.license, license.c_str(), LICENSE_LENGTH) == 0)
            return rec.isSpecial;
    }
    return false;
}

bool VehicleIO::getVehicleDimensions(const std::string& license,
                                     float& outHeight,
                                     float& outLength) {
    if (!fileIsOpen || license.empty()) return false;
    reset();
    VehicleRecord rec;
    while (vehicleFile.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        if (std::strncmp(rec.license, license.c_str(), LICENSE_LENGTH) == 0) {
            outHeight = rec.height;
            outLength = rec.length;
            return true;
        }
    }
    return false;
}


bool VehicleIO::createSpecialVehicle(const Vehicle& vehicle) {
    if (!fileIsOpen) return false;
    VehicleRecord record;
    std::memset(&record, 0, sizeof(record));
    // copy fields with safety
    std::strncpy(record.license, vehicle.currentLicensePlate.c_str(), LICENSE_LENGTH - 1);
    std::strncpy(record.phone, vehicle.currentPhoneNumber.c_str(), PHONE_LENGTH - 1);
    record.height    = vehicle.currentHeight;
    record.length    = vehicle.currentLength;
    record.isSpecial = true;
    vehicleFile.clear();
    vehicleFile.seekp(0, std::ios::end);
    vehicleFile.write(reinterpret_cast<const char*>(&record), sizeof(record));
    return vehicleFile.good();
}

bool VehicleIO::createVehicle(const Vehicle& vehicle) {
    if (!fileIsOpen) return false;
    VehicleRecord record;
    std::memset(&record, 0, sizeof(record));
    std::strncpy(record.license, vehicle.currentLicensePlate.c_str(), LICENSE_LENGTH - 1);
    std::strncpy(record.phone, vehicle.currentPhoneNumber.c_str(), PHONE_LENGTH - 1);
    record.height    = 0.0f;
    record.length    = 0.0f;
    record.isSpecial = false;
    vehicleFile.clear();
    vehicleFile.seekp(0, std::ios::end);
    vehicleFile.write(reinterpret_cast<const char*>(&record), sizeof(record));
    return vehicleFile.good();
}
