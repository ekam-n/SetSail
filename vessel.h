// vessel.h
#ifndef VESSEL_H
#define VESSEL_H

#include <string>

/// Domain‐level API for ferry vessels.
class Vessel {
public:
    /// Open underlying storage (called during startup).
    static void init();

    /// Close underlying storage (called during shutdown).
    static void shutdown();

    /**
     * Create a new vessel record.
     * @param vesselName      Unique name/ID of the vessel.
     * @param capacity        Maximum passenger capacity (as string).
     * @param highLaneLength  High‑ceiling lane length (as string).
     * @param lowLaneLength   Low‑ceiling lane length (as string).
     * @return true if creation succeeded.
     */
    static bool createVessel(const std::string& vesselName,
                             const std::string& capacity,
                             const std::string& highLaneLength,
                             const std::string& lowLaneLength);

    /**
     * Delete an existing vessel.
     * @param vesselName  Name/ID of the vessel to delete.
     * @return true if deletion succeeded.
     */
    static bool deleteVessel(const std::string& vesselName);

    /**
     * Check whether the given vessel has any scheduled sailings.
     * @param vesselName  Name/ID of the vessel to check.
     * @return true if the vessel has NO sailings (i.e. safe to delete).
     */
    static bool checkVesselForSailing(const std::string& vesselName);

    /**
     * Get the Low‑ceiling Lane Length (LRL) specification for a vessel.
     * @param vesselName  Name/ID to lookup.
     * @param outLRL      [out] the low‑ceiling lane length.
     * @return true if vessel exists and outLRL is set.
     */
    static bool getLRL(const std::string& vesselName, float& outLRL);

    /**
     * Get the High‑ceiling Lane Length (HRL) specification for a vessel.
     * @param vesselName  Name/ID to lookup.
     * @param outHRL      [out] the high‑ceiling lane length.
     * @return true if vessel exists and outHRL is set.
     */
    static bool getHRL(const std::string& vesselName, float& outHRL);
};

#endif // VESSEL_H