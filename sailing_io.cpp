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
    std::fstream fs;
    using Record = Sailing::Record;
}

void SailingIO::open() {
    fs.open(FILENAME, std::ios::in | std::ios::out | std::ios::binary);
    if (!fs) {
        std::ofstream ofs(FILENAME, std::ios::out | std::ios::binary);
        ofs.close();
        fs.open(FILENAME, std::ios::in | std::ios::out | std::ios::binary);
    }
}

void SailingIO::reset() {
    fs.clear();
    fs.seekg(0, std::ios::beg);
}

bool SailingIO::createSailing(const Record& rec) {
    // clear any stale error bits, position at end
    fs.clear();
    fs.seekp(0, std::ios::end);

    // write the record
    fs.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
    if (!fs) {
        std::cerr << "SailingIO::createSailing — write failed\n";
        return false;
    }

    // flush to disk
    fs.flush();
    if (!fs) {
        std::cerr << "SailingIO::createSailing — flush failed\n";
        return false;
    }

    return true;
}


void SailingIO::deleteSailing(const std::string& sailingID) {
    // Determine file size and record count
    fs.clear(); fs.seekg(0, std::ios::end);
    std::streamoff fileSize = fs.tellg();
    size_t recSize = sizeof(Record);
    if (fileSize < recSize) return;
    size_t count = fileSize / recSize;

    // Read last record
    Record last;
    fs.seekg((count - 1) * recSize, std::ios::beg);
    fs.read(reinterpret_cast<char*>(&last), recSize);

    // Find record to delete
    fs.seekg(0, std::ios::beg);
    Record temp;
    std::streamoff posToDelete = -1;
    for (size_t i = 0; i < count; ++i) {
        fs.read(reinterpret_cast<char*>(&temp), recSize);
        if (std::string(temp.sailingID) == sailingID) {
            posToDelete = static_cast<std::streamoff>(fs.tellg()) - recSize;
            break;
        }
    }
    if (posToDelete < 0) return;

    // Overwrite target with last record
    fs.clear();
    fs.seekp(posToDelete, std::ios::beg);
    fs.write(reinterpret_cast<const char*>(&last), recSize);
    fs.flush(); fs.close();

    // Truncate file by one record
    std::filesystem::resize_file(FILENAME, fileSize - recSize);
    open();
}

bool SailingIO::checkSailingsForVessel(const std::string& vesselName) {
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.vessel_ID) == vesselName)
            return true;
    }
    return false;
}

void SailingIO::addPeopleOccupants(const std::string& sailingID, int count) {
    reset();
    Record temp;
    std::streamoff pos;
    while ((pos = fs.tellg()), fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            temp.on_board += count;
            fs.clear(); fs.seekp(pos);
            fs.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            fs.flush();
            return;
        }
    }
}

void SailingIO::addVehicleOccupants(const std::string& sailingID, int count) {
    // 1) rewind to start
    reset();

    Record temp;
    std::streamoff pos;

    // 2) scan until we find the matching sailingID
    while ((pos = fs.tellg()), fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            // 3) bump the vehicle count field
            temp.vehicles_on_board += count;

            // 4) overwrite the record in‑place
            fs.clear();                  // clear eof/fail bits
            fs.seekp(pos, std::ios::beg);
            fs.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            fs.flush();
            return;
        }
    }

    // if we get here, no matching sailingID was found
    std::cerr << "SailingIO::addVehicleOccupants — no record for ID " 
              << sailingID << "\n";
}


int SailingIO::getPeopleOccupants(const std::string& sailingID) {
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID)
            return temp.on_board;
    }
    return -1;
}

int SailingIO::getVehicleOccupants(const std::string& sailingID) {
    reset();                        // rewind to file start
    Record temp;
    // scan for the matching sailingID
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            return temp.on_board;   // return occupant count
        }
    }
    return -1;                      // not found
}

bool SailingIO::checkSailingExists(const std::string& sailingID) {
    reset();                        // rewind to file start
    Record temp;
    // scan for the matching sailingID
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            return true;
        }
    }
    return false;                   // not found
}

void SailingIO::printSailingReport() {
    reset();
    Record temp;
    const int pageSize = 5;
    int printed = 0;

    std::cout << std::left << std::setw(32) << "SailingID"
              << std::setw(32) << "VesselID"
              << std::right << std::setw(8) << "LRL"
              << std::setw(8) << "HRL"
              << std::setw(10) << "OnBoard\n"
              << std::string(90, '=') << "\n";

    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        std::cout << std::left << std::setw(32) << temp.sailingID
                  << std::setw(32) << temp.vessel_ID
                  << std::right << std::setw(8) << temp.LRL
                  << std::setw(8) << temp.HRL
                  << std::setw(10) << temp.on_board << "\n";
        if (++printed % pageSize == 0) {
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void SailingIO::close() {
    fs.close();
}