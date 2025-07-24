//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// sailing.cpp
// Version History:
//   1.0 2025-07-20  Initial implementation
//============================================================
//
// Implements the Sailing “business logic”: prompts,
// validation, and orchestration of file‑I/O calls via SailingIO.
// Throws on invalid IDs.
//
//============================================================

#include "sailing.h"    // For Sailing interface :contentReference[oaicite:2]{index=2}
#include "sailing_io.h" // For low‑level I/O
#include "vessel.h"
#include <iostream>
#include <stdexcept>
#include <limits>

//---------------------------------------------------------
// static void Sailing::init()
// Initialize the sailing subsystem, opening and resetting its file.
void Sailing::init() {
    SailingIO::open();
    SailingIO::reset();
}

bool Sailing::createSailing(const std::string& vesselName,
                            const std::string& departTerm,
                            const std::string& departDay,
                            const std::string& departTime) {
    std::string sid, vid;
    float lrl, hrl;

    sid = departTerm+"-"+departDay+"-"+departTime;

    do {
        if (!Vessel::checkVesselForSailing(vesselName))
            std::cout << "Vessel not found. Please re-enter.\n";
        else break;
        break;
    } while (true);

    Vessel::getLRL(vesselName, lrl);
    Vessel::getHRL(vesselName, hrl);

    Record rec(sid.c_str(), vid.c_str(), hrl, lrl);
    SailingIO::createSailing(rec);
    std::cout << "Sailing created successfully. The sailing ID is: "+sid+"\n";
}

void Sailing::validateSailingID(const std::string& sailingID) {
    if (SailingIO::getPeopleOccupants(sailingID) < 0)
        throw std::runtime_error("Sailing ID not found: " + sailingID);
}

void Sailing::deleteSailing(const std::string& sailingID) {
    validateSailingID(sailingID);
    SailingIO::deleteSailing(sailingID);
    std::cout << "Sailing deleted successfully.\n";
}

bool Sailing::checkVesselHasSailings(const std::string& vesselName) {
    return SailingIO::checkSailingsForVessel(vesselName);
}

void Sailing::addOccupants(const std::string& sailingID,
                                int peopleCount,
                                int /*vehicleCount*/) {
    validateSailingID(sailingID);
    SailingIO::addPeopleOccupants(sailingID, peopleCount);
}

int Sailing::getPeopleOccupantsForReservation(const std::string& sailingID) {
    validateSailingID(sailingID);
    return SailingIO::getPeopleOccupants(sailingID);
}

int Sailing::getVehicleOccupantsForReservation(const std::string& /*sailingID*/) {
    return 0;
}

void Sailing::printSailingReport() {
    SailingIO::printSailingReport();
}

void Sailing::shutdown() {
    SailingIO::close();
}