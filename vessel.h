//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel.h
// CMPT 276 - Assignment 4
// Description: Header file for Vessel class. Used for fixed-length binary storage.
// Version: 1.0
// Author: [Your Name]
// History:
// - 1.0: Initial creation (2025-07-17)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef VESSEL_H
#define VESSEL_H

class Vessel {
public:
    char id[6];          // fixed-length ID string (e.g., "VS123")
    int length;          // in meters
    int height;          // in meters
    int vehicleCount;    // number of vehicles loaded

    Vessel(); // default constructor
    Vessel(const char* id_, int len, int ht, int count);

    bool operator==(const Vessel& other) const;
};

#endif // VESSEL_H

