//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// testVesselFileOps.cpp
// CMPT 276 - Assignment 4
// Description: Unit test for vessel file write/read binary operations
// Version: 2.0
// Author: group12
// History:
// - 1.0: Initial test created (2025-07-18)
// - 2.0: Constructor usage → replaced with brace initializer； operator → replaced with vesselsMatch() function（2025-07-23）
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <iostream>
#include <fstream>
#include <cassert>
#include "vessel.h"
#include "vessel_io.h"

int main() {
    std::string filename = "vessels.dat";

    // Step 1: Open file and clear it (truncate to zero)
    std::fstream file(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    file.close();

    // Step 2: Reopen file in in/out mode
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    // Step 3: Create test vessels
    Vessel v1("VS101", 100, 30, 25);
    Vessel v2("VS102", 120, 28, 40);

    writeVessel(file, v1);
    writeVessel(file, v2);

    // Step 4: Seek and read them back
    seekVessel(file, 0);
    Vessel read1, read2;

    bool ok1 = readVessel(file, read1);
    bool ok2 = readVessel(file, read2);

   // Field-by-field comparison
bool vesselsMatch(const Vessel& a, const Vessel& b) {
    return std::strncmp(a.id, b.id, 6) == 0 &&
           a.length == b.length &&
           a.height == b.height &&
           a.vehicleCount == b.vehicleCount;
}

if (ok1 && ok2 && vesselsMatch(read1, v1) && vesselsMatch(read2, v2)) {
    std::cout << "PASS: Vessels written and read correctly.\n";
}

    // Optional: test EOF
    Vessel dummy;
    if (!readVessel(file, dummy)) {
        std::cout << "PASS: EOF reached after expected records.\n";
    } else {
        std::cout << "FAIL: Unexpected extra data.\n";
    }

    file.close();
    return 0;
}
