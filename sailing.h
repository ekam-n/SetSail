//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
        float LCU;                  // Lane Capacity Used
        int    ppl_on_board;            // Current People occupant count
        int    veh_on_board;            // Current Vehicle occupant count


        // Default constructor: zero-initialize
        Record() {
            std::memset(sailingID, 0, ID_LEN);
            std::memset(vessel_ID, 0, VLEN);
            HRL = 0.0f;  LRL = 0.0f; LCU = 0.0f;  ppl_on_board = 0; veh_on_board = 0;
        }

        // Convenience constructor from C-strings
        Record(const char* sid, const char* vid, float hrl_value, float lrl_value) {
            std::strncpy(sailingID, sid, ID_LEN);
            sailingID[ID_LEN - 1] = '\0';
            std::strncpy(vessel_ID, vid, VLEN);
            vessel_ID[VLEN - 1] = '\0';
            HRL = hrl_value;
            LRL = lrl_value;
            LCU = 0.0f;
            ppl_on_board = 0;
            veh_on_board = 0;
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
    static bool deleteSailing(const std::string& sailingID);

    // Check whether a given vessel has any sailings scheduled.
    static bool checkVesselHasSailings(const std::string& vesselName);


    // Retrieve the number of people currently reserved on a sailing.
    static int getPeopleOccupantsForReservation(const std::string& sailingID);

    // Retrieve the number of vehicles currently reserved on a sailing.
    static int getVehicleOccupantsForReservation(const std::string& sailingID);

    static bool checkSailingVehicleCapacity(const std::string& sailingID); 
    // which returns true if the vessel capacity can take 1 additional vehicle

    static bool checkSailingPeopleCapacity(const std::string& sailingID, unsigned int occupants); 
    // which returns true if the vessel people capacity can take on x number of occupants

    static bool getHighRemLaneLength(const std::string& sailingID, float length); 
    // which returns true if the high ceiling lane length has room for x metres in length

    static bool getLowRemLaneLength(const std::string& sailingID, float length); 
    // which returns true if the low ceiling lane length has room for x metres in length

    // updates vehicle and people occupants when a reservation checks in
    static bool updateOccupants(const std::string& sailingID,
                                int numPeople,
                                float vehicleLength);

    static void updateSailingForHigh(const std::string& sailingID, int occupants, float length); 
    // which returns nothing, just updates sailing records by subtracting x metres from high lane length and subtracing x occupants from capacity

    static void updateSailingForLow(const std::string& sailingID, int occupants, float length); 
    // which returns nothing, just updates sailing records by subtracting x metres from low lane length and subtracing x occupants from capacity

    // Print a paginated report of all sailings.
    static void printSailingReport();

    // Cleanly close the sailing subsystem (flush & close file).
    static void shutdown();

    // Ensure the given sailingID exists; throws if not.
    static bool checkSailingExists(const std::string& sailingID);

    // Print a report with info about vehicles aboard a sailing
    static void printVehicleReport(const std::string& sailingID);

private:
};

#endif // SAILING_H