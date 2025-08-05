//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
#include <iomanip>

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
                            const std::string& departTime)
{
    // 1) Build the sailing ID
    std::string termCode = departTerm.substr(0, 3);
    for (auto& c : termCode) {
        c = static_cast<char>(toupper(c));
    }
    std::string sid = termCode + "-" + departDay + "-" + departTime;

    // 2) Reject duplicates
    if (checkSailingExists(sid)) {
        std::cerr << "Error: Sailing already exists: " << sid << "\n";
        return false;
    }

    // 3) Verify vessel exists
    if (!Vessel::checkVesselForSailing(vesselName)) {
        std::cerr << "Error: Vessel not found: " << vesselName << "\n";
        return false;
    }

    // 4) Pull the current LRL/HRL off the vessel
    float lrl = 0.0f, hrl = 0.0f;
    if (!Vessel::getLRL(vesselName, lrl) ||
        !Vessel::getHRL(vesselName, hrl))
    {
        std::cerr << "Error: Unable to fetch lane lengths for vessel: "
                  << vesselName << "\n";
        return false;
    }

    // 5) Create & persist
    Record rec(sid.c_str(), vesselName.c_str(), hrl, lrl);
    if (!SailingIO::createSailing(rec)) {
        std::cerr << "Error: Failed to write new sailing record.\n";
        return false;
    }

    std::cout << "Sailing created successfully. ID: " << sid << "\n";
    return true;
}

bool Sailing::deleteSailing(const std::string& sailingID) {
    if (!checkSailingExists(sailingID)) return false;
    else return SailingIO::deleteSailing(sailingID);
}

bool Sailing::checkVesselHasSailings(const std::string& vesselName) {
    return SailingIO::checkSailingsForVessel(vesselName);
}

bool Sailing::checkSailingVehicleCapacity(const std::string& sailingID) {
    return SailingIO::checkSailingVehicleCapacity(sailingID);
}

bool Sailing::checkSailingPeopleCapacity(const std::string& sailingID,
                                          unsigned int occupants)
{
    return SailingIO::checkSailingPeopleCapacity(sailingID, occupants);
}

bool Sailing::getHighRemLaneLength(const std::string& sailingID, float length) {
    return SailingIO::getHighRemLaneLength(sailingID, length);
}

bool Sailing::getLowRemLaneLength(const std::string& sailingID, float length) {
    return SailingIO::getLowRemLaneLength(sailingID, length);
}

bool Sailing::updateOccupants(const std::string& sailingID,
                                int numPeople,
                                float vehicleLength) 
{
    return SailingIO::updateOccupants(sailingID,
                                numPeople,
                                vehicleLength);
}

void Sailing::updateSailingForHigh(const std::string& sailingID,
                                   int occupants,
                                   float length)
{
    SailingIO::updateSailingForHigh(sailingID, length);
}

void Sailing::updateSailingForLow(const std::string& sailingID,
                                  int occupants,
                                  float length)
{
    SailingIO::updateSailingForLow(sailingID, length);
}

int Sailing::getPeopleOccupantsForReservation(const std::string& sailingID) {
    checkSailingExists(sailingID);
    return SailingIO::getPeopleOccupants(sailingID);
}

int Sailing::getVehicleOccupantsForReservation(const std::string& sailingID) {
    return SailingIO::getVehicleOccupants(sailingID);
}

bool Sailing::checkSailingExists(const std::string& sailingID) {

    return SailingIO::checkSailingExists(sailingID);
}

void Sailing::printSailingReport() {
    SailingIO::printSailingReport();
}

void Sailing::shutdown() {
    SailingIO::close();
}

void Sailing::printVehicleReport(const std::string& sailingID) {
    char choice;
    SailingIO::printCheckVehicles(sailingID);
    std::cout << "End of Report. Enter <0> to return to the main menu.\n";
    std::cin >> choice;
    if ( choice == '0' ) return;
}