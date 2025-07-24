//============================================================
// sailing.h
// Version History:
//   1.1 2025-07-20  Added Record definition with field defaults
//============================================================
#ifndef SAILING_H
#define SAILING_H

#include <string>
// #include "vessel.h"       // For vessel existence checks
// #include "reservation.h"  // For reservation-related queries
#include <cstddef>

// The Sailing Class encapsulates all sailing-related scenarios.
// All methods are static; no class instance is required.
class Sailing {
public:
    // Fixed sizes for C-string fields
    static const size_t ID_LEN = 32;
    static const size_t VLEN   = 32;

    // In-memory representation of a sailing record
    struct Record {
        char   sailingID[ID_LEN];   // Primary key, fixed-length C-string
        char   vessel_ID[VLEN];     // Foreign key, fixed-length C-string
        float  HRL;                 // High Remaining Length
        float  LRL;                 // Low Remaining Length
        int    on_board;            // Current occupant count

        // Default constructor: zero-initialize
        Record() {
            std::memset(sailingID, 0, ID_LEN);
            std::memset(vessel_ID, 0, VLEN);
            HRL = 0.0f;  LRL = 0.0f;  on_board = 0;
        }

        // Convenience constructor from C-strings
        Record(const char* sid, const char* vid, float hrl_value, float lrl_value) {
            std::strncpy(sailingID, sid, ID_LEN);
            sailingID[ID_LEN - 1] = '\0';
            std::strncpy(vessel_ID, vid, VLEN);
            vessel_ID[VLEN - 1] = '\0';
            HRL = hrl_value;
            LRL = lrl_value;
            on_board = 0;
        }
    };

    // Initialize the sailing subsystem, opening and resetting its file.
    static void init();

    // Create a new sailing record, prompting user for required fields.
    static bool createSailing(const std::string& vesselName,
                            const std::string& departTerm,
                            const std::string& departDay,
                            const std::string& departTime);
    // add arguments, print sailing ID: "sailing successfully created..."

    // Delete an existing sailing by ID. Throws if not found.
    static void deleteSailing(const std::string& sailingID);

    // Check whether a given vessel has any sailings scheduled.
    static bool checkVesselHasSailings(const std::string& vesselName);


    // Retrieve the number of people currently reserved on a sailing.
    static int getPeopleOccupantsForReservation(const std::string& sailingID);

    // Retrieve the number of vehicles currently reserved on a sailing.
    static int getVehicleOccupantsForReservation(const std::string& sailingID);

    

    // Print a paginated report of all sailings.
    static void printSailingReport();

    // Cleanly close the sailing subsystem (flush & close file).
    static void shutdown();

private:
    // Ensure the given sailingID exists; throws if not.
    static void checkSailingExists(const std::string& sailingID);
};

#endif // SAILING_H
