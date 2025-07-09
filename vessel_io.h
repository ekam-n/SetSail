//*******************************
//*******************************
// vessel_io.h
// Description:
// This class handles all file input/output operations for Vessel records,
// providing persistent storage for ferry vessel data.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with all file I/O operations
//*******************************

#include "vessel.h"

class VesselIO {
public:
    //------
    // Description:
    // Opens the vessel data file for reading/writing.
    // Returns true if successful, false on error.
    // Precondition:
    // None
    bool open();

    //------
    // Description:
    // Closes the vessel data file and releases resources.
    // Precondition:
    // File must be open
    void close();

    //------
    // Description:
    // Resets the file position indicator to start of file.
    // Precondition:
    // File must be open
    void reset();

    //------
    // Description:
    // Checks if a vessel exists in the system. Returns true if found.
    // Precondition:
    // File must be open
    bool checkVesselExists(
        const std::string& vesselName  // [in] Vessel name to search for
    );

    //------
    // Description:
    // Creates a new vessel record in persistent storage.
    // Returns true if successful, false if vessel exists.
    // Precondition:
    // Valid vessel data
    bool createVessel(
        const Vessel& vessel  // [in] Vessel data to store
    );

    //------
    // Description:
    // Deletes a vessel record from persistent storage.
    // Returns true if successful, false if vessel not found.
    // Precondition:
    // File must be open
    bool deleteVessel(
        const std::string& vesselName  // [in] Vessel name to delete
    );

private:
    // Private implementation details
    // std::fstream vesselFile;
    // std::string filename = "vessels.dat";
    // bool isOpen = false;
    // size_t recordSize = sizeof(Vessel);
};