//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel.h
// CMPT 276 - Assignment 4
// Description: Header file for Vessel class. Used for fixed-length binary storage.
// Version: 2.0
// Author: group12
// History:
// - 1.0: Initial creation (2025-07-17)
// - 2.0: 	class → struct; Removed: constructors + operator (2025-07-23)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef VESSEL_H
#define VESSEL_H

#include <cstddef>
#include <cstring>

class Vessel {
public:
    // Fixed sizes for C-string fields
    static const size_t ID_LEN = 6;

    // Vessel Record definition (used for file storage)
    struct Record {
        char vesselID[ID_LEN];  // Primary key
        int length;
        int height;
        int vehicleCount;

        // Default constructor: zero-initialize
        Record() {
            std::memset(vesselID, 0, ID_LEN);
            length = 0;
            height = 0;
            vehicleCount = 0;
        }

        // Convenience constructor
        Record(const char* id, int len, int ht, int count) {
            std::strncpy(vesselID, id, ID_LEN);
            vesselID[ID_LEN - 1] = '\0';
            length = len;
            height = ht;
            vehicleCount = count;
        }
    };

    // (Optional) Add static interface functions here like:
    // static void init();
    // static void createVessel();
};

#endif // VESSEL_H
