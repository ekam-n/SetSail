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
                            const std::string& departTime) {
    std::string sid;
    float lrl, hrl;

    std::string termCode = departTerm.substr(0, 3);
    for (char& letter : termCode ) {
        if ( letter >= 'a' && letter <= 'z' ) {
            letter = letter - ('a' - 'A');
        }
    }

    for ( char c : departDay ) {
        if ( !isdigit(c) ) {
            std::cout << "Invalid data. Please re-enter departure day.\n";
            break;
        }
    }

    sid = termCode + "-" + departDay + "-" + departTime;

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

bool Sailing::deleteSailing(const std::string& sailingID) {
    checkSailingExists(sailingID);
    SailingIO::deleteSailing(sailingID);
    return true;
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