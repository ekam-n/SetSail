//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//============================================================
// sailing_io.h
// Version History:
//   1.0 2025-07-20  Initial implementation
//============================================================
#ifndef SAILING_IO_H
#define SAILING_IO_H

#include <string>
#include "sailing.h"   // for SailingRecord

class SailingIO {
public:
    /// Open (or create) the binary data file for sailings
    static void open();

    /// Reset file position to beginning for reads
    static void reset();

    /// Append a new SailingRecord to the end of the file
    static bool createSailing(const Sailing::Record& rec);

    /// Delete the record matching the given sailing ID
    static void deleteSailing(const std::string& sailingID);

    /// Return true if any record’s vessel_ID matches the given name
    static bool checkSailingsForVessel(const std::string& vesselName);

    // update occupants on a sailing
    static bool updateOccupants(const std::string& sailingID,
                                unsigned int numPeople,
                                float vehicleLength);

    /// Returns true if there is room for one more vehicle
    static bool checkSailingVehicleCapacity(const std::string& sailingID);

    /// Returns true if there is room for `occupants` more people
    static bool checkSailingPeopleCapacity(const std::string& sailingID,
                                           unsigned int occupants);

    /// Returns true if high‑ceiling lane has ≥ `length` metres free
    static bool getHighRemLaneLength(const std::string& sailingID,
                                     float length);

    /// Returns true if low‑ceiling lane has ≥ `length` metres free
    static bool getLowRemLaneLength(const std::string& sailingID,
                                    float length);

    /**
     * Subtract `length` metres from the high‑ceiling lane and
     * remove `occupants` from on_board count for the given sailing.
     */
    static void updateSailingForHigh(const std::string& sailingID,
                                     unsigned int occupants,
                                     float length);

    /**
     * Subtract `length` metres from the low‑ceiling lane and
     * remove `occupants` from on_board count for the given sailing.
     */
    static void updateSailingForLow(const std::string& sailingID,
                                    unsigned int occupants,
                                    float length);


    /// Undo a high-lane reservation: add back lane-space + buffer, remove people
    static bool revertSailingForHigh(const std::string& sailingID,
                                   unsigned int occupants,
                                   float length);

    /// Undo a low-lane reservation: add back lane-space + buffer, remove people
    static bool revertSailingForLow(const std::string& sailingID,
                                  unsigned int occupants,
                                  float length);


    /// Return the on_board count for the record with this ID
    static int getPeopleOccupants(const std::string& sailingID);

    static int getVehicleOccupants(const std::string& sailingID);

    // checkSailingExists
    static bool checkSailingExists(const std::string& sailingID);

    /// Print all records in a paginated report (e.g., 5 per page)
    static void printSailingReport();

    // Print a report with info about vehicles aboard a sailing
    static void printCheckVehicles(const std::string& sailingID);

    /// Close the underlying file stream
    static void close();
};

#endif // SAILING_IO_H