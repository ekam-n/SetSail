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
// #include "vessel.h"     // For VesselClass::checkVesselExists()

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

void SailingClass::createSailing() {
    std::string sid, vid;
    float lrl, hrl;

    std::cout << "Enter new Sailing ID: ";
    std::getline(std::cin, sid);

    do {
        std::cout << "Enter Vessel name for sailing: ";
        // std::getline(std::cin, vid);
        // if (!VesselClass::checkVesselExists(vid))
        //     std::cout << "Vessel not found. Please re-enter.\n";
        // else break;
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

    Record rec(sid.c_str(), vid.c_str(), hrl, lrl);
    SailingIO::createSailing(rec);
    std::cout << "Sailing created successfully.\n";
}

void SailingClass::validateSailingID(const std::string& sailingID) {
    if (SailingIO::getPeopleOccupants(sailingID) < 0)
        throw std::runtime_error("Sailing ID not found: " + sailingID);
}

void SailingClass::deleteSailing(const std::string& sailingID) {
    validateSailingID(sailingID);
    SailingIO::deleteSailing(sailingID);
    std::cout << "Sailing deleted successfully.\n";
}

bool SailingClass::checkVesselHasSailings(const std::string& vesselName) {
    return SailingIO::checkSailingsForVessel(vesselName);
}

void SailingClass::addOccupants(const std::string& sailingID,
                                int peopleCount,
                                int /*vehicleCount*/) {
    validateSailingID(sailingID);
    SailingIO::addPeopleOccupants(sailingID, peopleCount);
}

int SailingClass::getPeopleOccupantsForReservation(const std::string& sailingID) {
    validateSailingID(sailingID);
    return SailingIO::getPeopleOccupants(sailingID);
}

int SailingClass::getVehicleOccupantsForReservation(const std::string& /*sailingID*/) {
    return 0;
}

void SailingClass::printSailingReport() {
    SailingIO::printSailingReport();
}

void SailingClass::shutdown() {
    SailingIO::close();
}