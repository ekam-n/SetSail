// VesselIO.cpp

#include "vessel_io.h"
#include <iostream>
#include <vector>
#include <cstring>

/// Path to the binary vessel file
static constexpr const char* kVesselFileName = "vessels.dat";

/// Define the static file stream
std::fstream VesselIO::fs;

bool VesselIO::open() {
    // Try to open existing file
    fs.open(kVesselFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!fs.is_open()) {
        // If it doesn't exist yet, create it
        fs.clear();
        fs.open(kVesselFileName, std::ios::out | std::ios::binary);
        if (!fs) {
            std::cerr << "VesselIO::open — failed to create file " << kVesselFileName << "\n";
            return false;
        }
        fs.close();
        // Reopen for read/write
        fs.open(kVesselFileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!fs) {
            std::cerr << "VesselIO::open — failed to reopen file " << kVesselFileName << "\n";
            return false;
        }
    }
    reset();
    return true;
}

void VesselIO::reset() {
    fs.clear();
    fs.seekg(0, std::ios::beg);
    fs.seekp(0, std::ios::beg);
}

void VesselIO::close() {
    if (fs.is_open()) fs.close();
}

bool VesselIO::createVessel(const VesselRecord& rec) {
    fs.clear();
    fs.seekp(0, std::ios::end);
    fs.write(reinterpret_cast<const char*>(&rec), sizeof rec);
    if (!fs) {
        std::cerr << "VesselIO::createVessel — write failed\n";
        return false;
    }
    fs.flush();
    if (!fs) {
        std::cerr << "VesselIO::createVessel — flush failed\n";
        return false;
    }
    return true;
}

bool VesselIO::readVessel(const char* vesselName, VesselRecord& rec) {
    fs.clear();
    fs.seekg(0, std::ios::beg);
    while (fs.read(reinterpret_cast<char*>(&rec), sizeof rec)) {
        if (std::strncmp(rec.vesselName, vesselName, sizeof rec.vesselName) == 0) {
            return true;
        }
    }
    return false;
}

bool VesselIO::checkVesselExists(const char* vesselName) {
    VesselRecord tmp;
    return readVessel(vesselName, tmp);
}

bool VesselIO::deleteVessel(const char* vesselName) {
    // Read all records except the one to delete
    fs.clear();
    fs.seekg(0, std::ios::beg);
    std::vector<VesselRecord> all;
    VesselRecord rec;
    bool found = false;

    while (fs.read(reinterpret_cast<char*>(&rec), sizeof rec)) {
        if (std::strncmp(rec.vesselName, vesselName, sizeof rec.vesselName) == 0) {
            found = true;
            continue;
        }
        all.push_back(rec);
    }
    if (!found) return false;

    // Truncate and rewrite
    fs.close();
    fs.open(kVesselFileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!fs) {
        std::cerr << "VesselIO::deleteVessel — truncate failed\n";
        return false;
    }
    for (const auto& r : all) {
        fs.write(reinterpret_cast<const char*>(&r), sizeof r);
        if (!fs) {
            std::cerr << "VesselIO::deleteVessel — write failed during rewrite\n";
            return false;
        }
    }
    fs.flush();
    fs.close();

    // Reopen for regular use
    fs.open(kVesselFileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!fs) {
        std::cerr << "VesselIO::deleteVessel — reopen failed\n";
        return false;
    }
    reset();
    return true;
}

bool VesselIO::getLRL(const char* vesselName, float& outLRL) {
    VesselRecord rec;
    if (!readVessel(vesselName, rec)) return false;
    outLRL = rec.lowLaneLength;
    return true;
}

bool VesselIO::getHRL(const char* vesselName, float& outHRL) {
    VesselRecord rec;
    if (!readVessel(vesselName, rec)) return false;
    outHRL = rec.highLaneLength;
    return true;
}