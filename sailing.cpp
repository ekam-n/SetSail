//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// sailing.cpp
// Version History:
//   1.0 2025-07-20  Initial implementation
//============================================================
//
// Implements the SailingClass “business logic”: prompts,
// validation, and orchestration of file‑I/O calls via SailingIO.
// Throws on invalid IDs.
//
//============================================================

#include "sailing.h"    // For SailingClass interface :contentReference[oaicite:2]{index=2}
#include "sailing_io.h" // For low‑level I/O
#include "vessel.h"     // For VesselClass::checkVesselExists()

#include <iostream>
#include <stdexcept>
#include <limits>

//---------------------------------------------------------
// static void SailingClass::init()
// Initialize the sailing subsystem, opening and resetting its file.
void SailingClass::init() {
    SailingIO::open();
    SailingIO::reset();
}

//---------------------------------------------------------
// static void SailingClass::createSailing()
// Prompt user for fields, validate vessel, and persist.
void SailingClass::createSailing() {
    std::string sid, vid;
    float hrl, lrl;

    std::cout << "Enter new Sailing ID: ";
    std::getline(std::cin, sid);

    // Vessel validation
    do {
        std::cout << "Enter Vessel name for sailing: ";
        std::getline(std::cin, vid);
        if (!VesselClass::checkVesselExists(vid)) {
            std::cout << "Vessel not found. Please re-enter.\n";
        } else break;
    } while (true);

    std::cout << "Enter Low Return Limit (LRL): ";
    while (!(std::cin >> lrl)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Re-enter LRL: ";
    }

    std::cout << "Enter High Return Limit (HRL): ";
    while (!(std::cin >> hrl)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Re-enter HRL: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    SailingClass::Record rec(sid, vid, hrl, lrl);
    SailingIO::createSailing(rec);
    std::cout << "Sailing created successfully.\n";
}

//---------------------------------------------------------
// static void SailingClass::validateSailingID(const std::string& sailingID)
// Ensure the given sailingID exists; throws if not.
void SailingClass::validateSailingID(const std::string& sailingID) {
    if (SailingIO::getPeopleOccupants(sailingID) < 0) {
        throw std::runtime_error("Sailing ID not found: " + sailingID);
    }
}

//---------------------------------------------------------
// static void SailingClass::deleteSailing(const std::string& sailingID)
// Delete an existing sailing by ID. Throws if not found.
void SailingClass::deleteSailing(const std::string& sailingID) {
    validateSailingID(sailingID);
    SailingIO::deleteSailing(sailingID);
    std::cout << "Sailing deleted successfully.\n";
}

//---------------------------------------------------------
// static bool SailingClass::checkVesselHasSailings(const std::string& vesselName)
// Check whether a given vessel has any sailings scheduled.
bool SailingClass::checkVesselHasSailings(const std::string& vesselName) {
    return SailingIO::checkSailingsForVessel(vesselName);
}

//---------------------------------------------------------
// static void SailingClass::addOccupants(const std::string& sailingID,
//                                        int peopleCount,
//                                        int /*vehicleCount*/)
// Add occupant counts to an existing sailing.
void SailingClass::addOccupants(const std::string& sailingID,
                                int peopleCount,
                                int /*vehicleCount*/) {
    validateSailingID(sailingID);
    SailingIO::addPeopleOccupants(sailingID, peopleCount);
}

//---------------------------------------------------------
// static int SailingClass::getPeopleOccupantsForReservation(
//                const std::string& sailingID)
// Retrieve the number of people currently reserved on a sailing.
int SailingClass::getPeopleOccupantsForReservation(const std::string& sailingID) {
    validateSailingID(sailingID);
    return SailingIO::getPeopleOccupants(sailingID);
}

//---------------------------------------------------------
// static int SailingClass::getVehicleOccupantsForReservation(
//                const std::string& /*sailingID*/)
// Delegate to reservation system; not stored here.
int SailingClass::getVehicleOccupantsForReservation(const std::string& sailingID) {
    // Likely implemented by scanning ReservationIO; stubbed here
    return 0;
}

//---------------------------------------------------------
// static void SailingClass::printSailingReport()
// Print a paginated report of all sailings.
void SailingClass::printSailingReport() {
    SailingIO::printSailingReport();
}

//---------------------------------------------------------
// static void SailingClass::shutdown()
// Cleanly close the sailing subsystem (flush & close file).
void SailingClass::shutdown() {
    SailingIO::close();
}
