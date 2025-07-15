//============================================================
// sailing.h
// Version History:
//   1.0 2025-07-20  Initial version
//============================================================
#ifndef SAILING_H
#define SAILING_H

#include <string>
#include "sailing_io.h"   // Bottom-level ASM for file I/O
#include "vessel.h"       // Vessel existence checks
#include "reservation.h"  // Reservation-based occupant queries

// The SailingClass encapsulates all sailing-related scenarios.
// All methods are static; no object instantiation is needed.
class SailingClass {
public:
    static void init();
    static void createSailing();
    static void deleteSailing(const std::string& sailingID);
    static bool checkVesselHasSailings(const std::string& vesselName);
    static void addOccupants(const std::string& sailingID,
                             int peopleCount,
                             int vehicleCount);
    static int  getPeopleOccupantsForReservation(const std::string& sailingID);
    static int  getVehicleOccupantsForReservation(const std::string& sailingID);
    static void printSailingReport();
    static void shutdown();

private:
    static void validateSailingID(const std::string& sailingID);
};

#endif // SAILING_H
