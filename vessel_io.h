// VesselIO.h
#ifndef VESSEL_IO_H
#define VESSEL_IO_H

#include <fstream>

/// Fixed‑length binary record layout for a vessel.
struct VesselRecord {
    char   vesselName[30];
    int    maxPassengers;
    float  highLaneLength;
    float  lowLaneLength;
};

class VesselIO {
public:
    static bool open();
    static void reset();
    static void close();

    static bool createVessel(const VesselRecord& rec);
    static bool deleteVessel(const char* vesselName);
    static bool checkVesselExists(const char* vesselName);
    static bool readVessel(const char* vesselName, VesselRecord& rec);

    // just declarations here:
    static bool getLRL(const char* vesselName, float& outLRL);
    static bool getHRL(const char* vesselName, float& outHRL);

private:
    static std::fstream fs;
};

#endif // VESSELIO_H
