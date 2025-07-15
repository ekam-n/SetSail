//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// sailing_io.cpp
// Version History:
//   1.0 2025-07-20  Initial implementation
//============================================================
//
// Implements binary, random‑access I/O for Sailing records.
// Uses unsorted fixed‑length records. On deletion, rewrites
// the file without the removed record.
//
//============================================================

#include "sailing_io.h"            // For class SailingIO interface :contentReference[oaicite:0]{index=0}
#include "sailing.h"               // For SailingClass::Record :contentReference[oaicite:1]{index=1}

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

namespace {
    const std::string FILENAME = "sailings.dat";
    std::fstream      fs;

    // Alias to match the header’s expected type
    using SailingRecord = SailingClass::Record;
}

//---------------------------------------------------------
// static void SailingIO::open()
// Open (or create) the binary data file for sailings.
void SailingIO::open() {
    fs.open(FILENAME, std::ios::in | std::ios::out | std::ios::binary);
    if (!fs) {
        // File doesn’t exist yet: create it, then re-open
        fs.clear();
        std::ofstream ofs(FILENAME, std::ios::out | std::ios::binary);
        ofs.close();
        fs.open(FILENAME, std::ios::in | std::ios::out | std::ios::binary);
    }
}

//---------------------------------------------------------
// static void SailingIO::reset()
// Reset file position to beginning for reads.
void SailingIO::reset() {
    fs.clear();  // Clear EOF flag if set
    fs.seekg(0, std::ios::beg);
}

//---------------------------------------------------------
// static void SailingIO::createSailing(const SailingRecord& rec)
// Append a new SailingRecord to the end of the file.
void SailingIO::createSailing(const SailingRecord& rec) {
    fs.clear();
    fs.seekp(0, std::ios::end);
    fs.write(reinterpret_cast<const char*>(&rec), sizeof rec);
    fs.flush();
}

//---------------------------------------------------------
// static void SailingIO::deleteSailing(const std::string& sailingID)
// Remove the record matching the given sailing ID by
// reading all records, omitting the one to delete, and
// rewriting the file.
void SailingIO::deleteSailing(const std::string& sailingID) {
    // Read all records
    reset();
    std::vector<SailingRecord> all;
    SailingRecord temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (temp.sailingID != sailingID) {
            all.push_back(temp);
        }
    }

    // Rewrite file without the deleted record
    fs.close();
    std::ofstream ofs(FILENAME, std::ios::out | std::ios::binary | std::ios::trunc);
    for (const auto& r : all) {
        ofs.write(reinterpret_cast<const char*>(&r), sizeof r);
    }
    ofs.close();

    // Re-open for further operations
    open();
}

//---------------------------------------------------------
// static bool SailingIO::checkSailingsForVessel(const std::string& vesselName)
// Return true if any record’s vessel_ID matches the given name.
bool SailingIO::checkSailingsForVessel(const std::string& vesselName) {
    reset();
    SailingRecord temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (temp.vessel_ID == vesselName) {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------
// static void SailingIO::addPeopleOccupants(const std::string& id, int count)
// Increment the on_board field for the record with this ID.
void SailingIO::addPeopleOccupants(const std::string& id, int count) {
    reset();
    SailingRecord temp;
    std::streampos pos;
    while ((pos = fs.tellg()), fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (temp.sailingID == id) {
            temp.on_board += count;
            fs.clear();
            fs.seekp(pos);
            fs.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            fs.flush();
            return;
        }
    }
}

//---------------------------------------------------------
// static int SailingIO::getPeopleOccupants(const std::string& id)
// Return the on_board count for the record with this ID,
// or -1 if not found.
int SailingIO::getPeopleOccupants(const std::string& id) {
    reset();
    SailingRecord temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (temp.sailingID == id) {
            return temp.on_board;
        }
    }
    return -1;
}

//---------------------------------------------------------
// static void SailingIO::printSailingReport()
// Print all records in a paginated report (5 per page),
// with fixed‑width columns.
void SailingIO::printSailingReport() {
    reset();
    SailingRecord temp;
    const int pageSize = 5;
    int count = 0;

    // Header
    std::cout
        << std::left << std::setw(15) << "SailID"
        << std::setw(15) << "Vessel"
        << std::right << std::setw(8) << "LRL"
        << std::setw(8) << "HRL"
        << std::setw(10) << "OnBoard"
        << "\n"
        << std::string(56, '=') << "\n";

    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        std::cout
            << std::left << std::setw(15) << temp.sailingID
            << std::setw(15) << temp.vessel_ID
            << std::right << std::setw(8) << temp.LRL
            << std::setw(8) << temp.HRL
            << std::setw(10) << temp.on_board
            << "\n";

        if (++count % pageSize == 0) {
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

//---------------------------------------------------------
// static void SailingIO::close()
// Close the underlying file stream.
void SailingIO::close() {
    fs.close();
}
