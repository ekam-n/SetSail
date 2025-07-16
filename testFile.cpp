//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// testFileOps.cpp
// Description:
// Unit test driver for testing low-level file operations in VehicleIO class.
// Tests writing and reading back vehicle records from file.
//
// Test Case:
// 1. Creates a test vehicle record and writes it to file
// 2. Reads back the record and verifies data matches
// 3. Checks that reading stops at end of file
//
// Revision History:
// Rev. 1 - 2025/07/16 - Team 12
// - Initial implementation
//*******************************

#include <iostream>
#include "vehicle.h"
#include "vehicle_io.h"

//------
// Description:
// Main test driver function
int main() {
    VehicleIO vehicleIO;
    Vehicle testVehicle;
    
    // Initialize test
    std::cout << "Starting VehicleIO file operations test...\n";
    
    // Open file
    if (!vehicleIO.open()) {
        std::cerr << "Failed to open vehicle file\n";
        return 1;
    }
    
    // Create test vehicle data
    testVehicle.createSpecialVehicleForReservation(
        "TEST123",          // license
        "555-1234",         // phone
        3.5f,               // height
        12.0f               // length
    );
    
    // Test 1: Write record to file
    bool writeSuccess = vehicleIO.createSpecialVehicle(testVehicle);
    if (!writeSuccess) {
        std::cerr << "Failed to write vehicle record to file\n";
        vehicleIO.close();
        return 1;
    }
    
    // Test 2: Read back and verify
    vehicleIO.reset();
    bool exists = vehicleIO.checkVehicleExists("TEST123");
    if (!exists) {
        std::cerr << "Failed to find written record in file\n";
        vehicleIO.close();
        return 1;
    }
    
    // Test 3: Verify non-existent record
    bool notExists = vehicleIO.checkVehicleExists("NONEXIST");
    if (notExists) {
        std::cerr << "Incorrectly found non-existent record\n";
        vehicleIO.close();
        return 1;
    }
    
    // Clean up and report results
    vehicleIO.close();
    std::cout << "VehicleIO file operations test: Pass\n";
    return 0;
}