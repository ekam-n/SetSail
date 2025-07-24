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
    std::string sid;
    float lrl, hrl;

    sid = departTerm+"-"+departDay+"-"+departTime;

    do {
        if (!Vessel::checkVesselForSailing(vesselName))
            std::cout << "Vessel not found. Please re-enter.\n";
        else break;
        return false;
    } while (true);

    Vessel::getLRL(vesselName, lrl);
    Vessel::getHRL(vesselName, hrl);

    Record rec(sid.c_str(), vesselName.c_str(), hrl, lrl);
    SailingIO::createSailing(rec);
    std::cout << "Sailing created successfully. The sailing ID is: "+sid+"\n";
    return true;
}

// void Sailing::checkSailingExists(const std::string& sailingID) {
//     if (SailingIO::getPeopleOccupants(sailingID) < 0)
//         throw std::runtime_error("Sailing ID not found: " + sailingID);
// }

void Sailing::deleteSailing(const std::string& sailingID) {
    checkSailingExists(sailingID);
    SailingIO::deleteSailing(sailingID);
    std::cout << "Sailing deleted successfully.\n";
}

bool Sailing::checkVesselHasSailings(const std::string& vesselName) {
    return SailingIO::checkSailingsForVessel(vesselName);
}

void Sailing::addPeopleOccupants(const std::string& sailingID,
                                int peopleCount) {
    checkSailingExists(sailingID);
    SailingIO::addPeopleOccupants(sailingID, peopleCount);
    // SailingIO::addVehicleOccupants(sailingID, vehicleCount);
}

int Sailing::getPeopleOccupantsForReservation(const std::string& sailingID) {
    checkSailingExists(sailingID);
    return SailingIO::getPeopleOccupants(sailingID);
}

int Sailing::getVehicleOccupantsForReservation(const std::string& sailingID) {
    return SailingIO::getVehicleOccupants(sailingID);
}

bool checkSailingExists(const std::string& sailingID) {

    return SailingIO::checkSailingExists(sailingID);
}

void Sailing::printSailingReport() {
    SailingIO::printSailingReport();
}

void Sailing::shutdown() {
    SailingIO::close();
}