//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel.cpp
// CMPT 276 - Assignment 4
// Description: Implementation of the Vessel class.
// Version: 1.0
// Author:
// History:
// - 1.0: Initial implementation (2025-07-17)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include <cstring>      // for strncpy, strcmp
#include "vessel.h"

//------------------------------------------------------------------------------
// Default constructor: initializes all fields to zero/empty
Vessel::Vessel() {
    id[0] = '\0';
    length = 0;
    height = 0;
    vehicleCount = 0;
}

//------------------------------------------------------------------------------
// Parameterized constructor
Vessel::Vessel(const char* id_, int len, int ht, int count) {
    strncpy(id, id_, 5);
    id[5] = '\0'; // ensure null termination
    length = len;
    height = ht;
    vehicleCount = count;
}

//------------------------------------------------------------------------------
// Comparison operator (==) to check if two vessels are the same
bool Vessel::operator==(const Vessel& other) const {
    return std::strncmp(id, other.id, 6) == 0 &&
           length == other.length &&
           height == other.height &&
           vehicleCount == other.vehicleCount;
}
