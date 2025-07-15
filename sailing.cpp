//============================================================
// sailing.cpp
// Version History:
//   1.0 2025-07-20  Initial implementation
//============================================================
#include "sailing.h"
#include <iostream>

void SailingClass::init() {
    SailingIO::open();
    SailingIO::reset();
}

void SailingClass::createSailing() {
    std::string id, vessel;
    // (prompt user for ID & vessel, validate vessel)
    std::cout << "Enter new Sailing ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter vessel name: ";
    std::getline(std::cin, vessel);

    if (!VesselClass::checkVesselExists(vessel)) {
        throw std::runtime_error("Vessel does not exist.");
    }

    // Build record (fields omitted for brevity)...
    SailingRecord rec{ /* id, vessel, 0 occupants */ };

    SailingIO::createSailing(rec);
}

void SailingClass::deleteSailing(const std::string& sailingID) {
    validateSailingID(sailingID);
    SailingIO::deleteSailing(sailingID);
}

bool SailingClass::checkVesselHasSailings(const std::string& vesselName) {
    SailingIO::reset();
    return SailingIO::checkSailingsForVessel(vesselName);
}

void SailingClass::addOccupants(const std::string& sailingID,
                                int peopleCount,
                                int vehicleCount) {
    validateSailingID(sailingID);
    SailingIO::addPeopleOccupants(sailingID, peopleCount);
    SailingIO::addVehicleOccupants(sailingID, vehicleCount);
}

int SailingClass::getPeopleOccupantsForReservation(const std::string& sailingID) {
    validateSailingID(sailingID);
    SailingIO::reset();
    return SailingIO::getPeopleOccupants(sailingID);
}

int SailingClass::getVehicleOccupantsForReservation(const std::string& sailingID) {
    validateSailingID(sailingID);
    SailingIO::reset();
    return SailingIO::getVehicleOccupants(sailingID);
}

void SailingClass::printSailingReport() {
    SailingIO::reset();
    SailingIO::printSailingReport();
}

void SailingClass::shutdown() {
    SailingIO::close();
}

void SailingClass::validateSailingID(const std::string& sailingID) {
    SailingIO::reset();
    if (!SailingIO::isSailingExists(sailingID)) {
        throw std::runtime_error("Sailing ID not found.");
    }
}
