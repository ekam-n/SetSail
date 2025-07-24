// vessel.cpp

#include "vessel.h"
#include "vessel_io.h"
#include <iostream>
#include <cstring>

void Vessel::init() {
    if (!VesselIO::open()) {
        std::cerr << "Error: Unable to open vessel data file\n";
    } else {
        VesselIO::reset();
    }
}

void Vessel::shutdown() {
    VesselIO::close();
}

bool Vessel::createVessel(const std::string& vesselName,
                          const std::string& capacity,
                          const std::string& highLaneLength,
                          const std::string& lowLaneLength)
{
    // prevent duplicates
    if (VesselIO::checkVesselExists(vesselName.c_str())) {
        std::cerr << "Error: Vessel already exists: " << vesselName << "\n";
        return false;
    }

    // parse capacity
    int cap = 0;
    try {
        cap = std::stoi(capacity);
    } catch (...) {
        std::cerr << "Error: Invalid capacity: '" << capacity << "'\n";
        return false;
    }

    // parse high‑ceiling lane length
    float hll = 0.0f;
    try {
        hll = std::stof(highLaneLength);
    } catch (...) {
        std::cerr << "Error: Invalid highLaneLength: '" << highLaneLength << "'\n";
        return false;
    }

    // parse low‑ceiling lane length
    float lll = 0.0f;
    try {
        lll = std::stof(lowLaneLength);
    } catch (...) {
        std::cerr << "Error: Invalid lowLaneLength: '" << lowLaneLength << "'\n";
        return false;
    }

    // build record
    VesselRecord rec;
    std::strncpy(rec.vesselName, vesselName.c_str(), sizeof(rec.vesselName));
    rec.vesselName[sizeof(rec.vesselName)-1] = '\0';
    rec.maxPassengers   = cap;
    rec.highLaneLength  = hll;
    rec.lowLaneLength   = lll;

    // persist
    if (!VesselIO::createVessel(rec)) {
        std::cerr << "Error: Failed to write vessel record.\n";
        return false;
    }

    std::cout << "Vessel created successfully: " << vesselName << "\n";
    return true;
}

bool Vessel::deleteVessel(const std::string& vesselName)
{
    // ensure no sailings are scheduled for this vessel
    if (!checkVesselForSailing(vesselName)) {
        std::cerr << "Cannot delete vessel with scheduled sailings: " << vesselName << "\n";
        return false;
    }

    if (!VesselIO::deleteVessel(vesselName.c_str())) {
        std::cerr << "Error: Failed to delete vessel: " << vesselName << "\n";
        return false;
    }

    std::cout << "Vessel deleted: " << vesselName << "\n";
    return true;
}

bool Vessel::checkVesselForSailing(const std::string& vesselName)
{
    return VesselIO::checkVesselExists(vesselName.c_str());
}

bool Vessel::getLRL(const std::string& vesselName, float& outLRL)
{
    return VesselIO::getLRL(vesselName.c_str(), outLRL);
}

bool Vessel::getHRL(const std::string& vesselName, float& outHRL)
{
    return VesselIO::getHRL(vesselName.c_str(), outHRL);
}