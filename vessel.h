//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel.h
// CMPT 276 - Assignment 4
// Description: Header file for Vessel class. Used for fixed-length binary storage.
// Version: 1.0
// Author: group12
// History: v2.0
// - 1.0: Initial creation (2025-07-17)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef VESSEL_H
#define VESSEL_H

struct Vessel {
    char id[6];          // 5-character ID + null terminator
    int length;          // in meters
    int height;          // in meters
    int vehicleCount;    // number of vehicles onboard
};

#endif // VESSEL_H
