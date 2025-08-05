//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel.cpp

#include "vessel.h"
#include "vessel_io.h"
#include "sailing.h"
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
                          const int capacity,
                          const float highLaneLength,
                          const float lowLaneLength)
{
    // prevent duplicates
    if (VesselIO::checkVesselExists(vesselName.c_str())) {
        return false;
    }

    // validate capacity
    if (capacity <= 0) {
        std::cerr << "Error: Invalid capacity: " << capacity << "\n";
        return false;
    }

    // validate high-ceiling lane length
    if (highLaneLength <= 0.0f) {
        std::cerr << "Error: Invalid highLaneLength: " << highLaneLength << "\n";
        return false;
    }

    // validate low-ceiling lane length
    if (lowLaneLength <= 0.0f) {
        std::cerr << "Error: Invalid lowLaneLength: " << lowLaneLength << "\n";
        return false;
    }

    // build record
    VesselRecord rec;
    std::strncpy(rec.vesselName, vesselName.c_str(), sizeof(rec.vesselName));
    rec.vesselName[sizeof(rec.vesselName)-1] = '\0';
    rec.maxPassengers   = capacity;  // Directly use the parameter
    rec.highLaneLength  = highLaneLength;  // Directly use the parameter
    rec.lowLaneLength   = lowLaneLength;  // Directly use the parameter

    // persist
    if (!VesselIO::createVessel(rec)) {
        std::cerr << "Error: Failed to write vessel record.\n";
        return false;
    }

    return true;
}

bool Vessel::deleteVessel(const std::string& vesselName)
{
    // 1) refuse if there are ANY sailings for this vessel
    if (Sailing::checkVesselHasSailings(vesselName)) {
        std::cerr << "Cannot delete vessel with scheduled sailings: "
                  << vesselName << "\n";
        return false;
    }

    // 2) otherwise, proceed to delete from the vessels file
    if (!VesselIO::deleteVessel(vesselName.c_str())) {
        std::cerr << "Error: Failed to delete vessel: " << vesselName << "\n";
        return false;
    }

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