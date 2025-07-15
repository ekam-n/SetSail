//============================================================
// sailing.h
// Version History:
//   1.1 2025-07-20  Added Record definition with field defaults
//============================================================
#ifndef SAILING_H
#define SAILING_H

#include <string>
#include "vessel.h"       // For vessel existence checks
#include "reservation.h"  // For reservation-related queries
#include "sailing_io.h"   // Bottom-level ASM for file I/O operations

// The SailingClass encapsulates all sailing-related scenarios.
// All methods are static; no class instance is required.
class SailingClass {
public:
    // In-memory representation of a sailing record
    struct Record {
        std::string sailingID;   // Primary key
        std::string vessel_ID;   // Foreign key (Ferry/Vessel)
        float       HRL = 0.0f;  // High Return Limit
        float       LRL = 0.0f;  // Low Return Limit
        int         on_board = 0;// Current occupant count

        // Default constructor
        Record() = default;

        // Convenience constructor
        Record(const std::string& sid,
               const std::string& vid,
               float hrl_value,
               float lrl_value)
          : sailingID(sid)
          , vessel_ID(vid)
          , HRL(hrl_value)
          , LRL(lrl_value)
          , on_board(0) {}
    };

    // Initialize the sailing subsystem, opening and resetting its file.
    static void init();

    // Create a new sailing record, prompting user for required fields.
    static void createSailing();

    // Delete an existing sailing by ID. Throws if not found or not complete.
    static void deleteSailing(const std::string& sailingID);

    // Check whether a given vessel has any sailings scheduled.
    static bool checkVesselHasSailings(const std::string& vesselName);

    // Add occupant counts to an existing sailing.
    static void addOccupants(const std::string& sailingID,
                             int peopleCount,
                             int vehicleCount);

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
    static void validateSailingID(const std::string& sailingID);
};

#endif // SAILING_H
