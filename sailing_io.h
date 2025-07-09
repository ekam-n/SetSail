//*******************************
//*******************************
// sailing_io.h
// Description:
// This class handles all file input/output operations for Sailing records,
// providing persistent storage for sailing data and capacity management.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with all file I/O operations
//*******************************

#include <vector>
#include "sailing.h"

class SailingIO {
public:
    //------
    // Description:
    // Opens the sailing data file. Returns true if successful.
    // Precondition:
    // None
    bool open();

    //------
    // Description:
    // Closes the sailing data file.
    // Precondition:
    // File must be open
    void close();

    //------
    // Description:
    // Resets the file iterator to beginning of file.
    // Precondition:
    // File must be open
    void reset();

    //------
    // Description:
    // Adds people occupants to a sailing record. Returns true if successful.
    // Precondition:
    // Sailing must exist
    bool addPeopleOccupants(
        const std::string& sailingID,  // [in] Sailing ID to update
        int count                      // [in] Number of people to add
    );

    //------
    // Description:
    // Adds vehicle length to sailing's occupied space. Returns true if successful.
    // Precondition:
    // Sailing must exist
    bool addVehicleOccupants(
        const std::string& sailingID,  // [in] Sailing ID to update
        float length                   // [in] Vehicle length to add
    );

    //------
    // Description:
    // Checks if any sailings exist for a vessel. Returns true if found.
    // Precondition:
    // Vessel must exist
    bool checkSailingsForVessel(
        const std::string& vesselName  // [in] Vessel name to check
    );

    //------
    // Description:
    // Creates a new sailing record. Returns true if successful.
    // Precondition:
    // Valid sailing data
    bool createSailing(
        const Sailing& sailing  // [in] Sailing data to create
    );

    //------
    // Description:
    // Deletes a sailing record. Returns true if successful.
    // Precondition:
    // File must be open
    bool deleteSailing(
        const std::string& sailingID  // [in] Sailing ID to delete
    );

    //------
    // Description:
    // Gets current people occupant count. Returns -1 if error.
    // Precondition:
    // Sailing must exist
    int getPeopleOccupants(
        const std::string& sailingID  // [in] Sailing ID to query
    );

    //------
    // Description:
    // Gets total vehicle length occupied. Returns -1.0 if error.
    // Precondition:
    // Sailing must exist
    float getVehicleOccupants(
        const std::string& sailingID  // [in] Sailing ID to query
    );

    //------
    // Description:
    // Prints formatted sailing report to standard output.
    // Precondition:
    // File must be open
    void printSailingReport();

private:
    // Private implementation details would be declared here
    // Example:
    // std::fstream sailingFile;
    // std::string currentFileName;
    // bool fileIsOpen;
};