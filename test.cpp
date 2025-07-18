//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// testVesselFileOps.cpp
// CMPT 276 - Assignment 4
// Description: Unit test for vessel file write/read binary operations
// Version: 1.0
// Author: [Your Name]
// History:
// - 1.0: Initial test created (2025-07-18)
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

    // Step 5: Compare and report
    if (ok1 && ok2 && read1 == v1 && read2 == v2) {
        std::cout << "PASS: Vessels written and read correctly.\n";
    } else {
        std::cout << "FAIL:\n";
        if (!ok1 || !ok2)
            std::cout << "  Read error occurred.\n";
        if (!(read1 == v1))
            std::cout << "  First vessel mismatch.\n";
        if (!(read2 == v2))
            std::cout << "  Second vessel mismatch.\n";
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
