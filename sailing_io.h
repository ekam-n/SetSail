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

    /// Increment the on_board field for the record with this ID
    static void addPeopleOccupants(const std::string& sailingID, int count);

    // addvehicleoccupants

    /// Return the on_board count for the record with this ID
    static int getPeopleOccupants(const std::string& sailingID);

    /// Print all records in a paginated report (e.g., 5 per page)
    static void printSailingReport();

    /// Close the underlying file stream
    static void close();
};

#endif // SAILING_IO_H
