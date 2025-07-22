//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// testVehicleModule.cpp
// Description:
// Unit test driver for testing the Vehicle class.
//
// Test Case:
// 1. Initialize the vehicle system
// 2. Test creation of a standard vehicle and check internal data
// 3. Test creation of a special vehicle and validate dimensions
// 4. Check license validation logic with valid and invalid inputs
//
// Revision History:
// Rev. 1 - 2025/07/22 - Team 12
// - Initial implementation
//*******************************

#include <iostream>
#include <cassert>
#include "vehicle.h"

int main() {
    std::cout << "Starting Vehicle class unit test...\n";

    // Test 1: Initialization
    assert(Vehicle::init());
    std::cout << "Test 1 passed: Initialization successful\n";

    // Test 2: Create regular vehicle
    assert(Vehicle::createVehicleForReservation("ABC123", "604-123-4567"));
    assert(Vehicle::checkLicenseForReservation("ABC123") == true);
    std::cout << "Test 2 passed: Standard vehicle created and license valid\n";

    // Test 3: License check for empty string (should fail)
    assert(Vehicle::checkLicenseForReservation("") == false);
    std::cout << "Test 3 passed: License check correctly fails for empty string\n";

    // Test 4: Create special vehicle and check dimensions
    assert(Vehicle::createSpecialVehicleForReservation("XYZ789", "778-555-4321", 3.2f, 5.5f));
    assert(Vehicle::checkLicenseForReservation("XYZ789") == true);
    std::cout << "Test 4 passed: Special vehicle created and license valid\n";

    // Cleanup
    Vehicle::shutdown();
    std::cout << "All Vehicle class tests passed\n";
    return 0;
}