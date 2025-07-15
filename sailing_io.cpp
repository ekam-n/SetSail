//============================================================
// sailing_io.cpp
// Version History:
//   1.0 2025-07-20  Initial implementation
//============================================================
#include "sailing_io.h"
#include <fstream>
#include <stdexcept>

static std::fstream fileStream;

void SailingIO::open() {
    fileStream.open("sailings.dat",
                    std::ios::in | std::ios::out | std::ios::binary);
    if (!fileStream) {
        // Create if not exists
        fileStream.clear();
        fileStream.open("sailings.dat",
                        std::ios::out | std::ios::binary);
        fileStream.close();
        fileStream.open("sailings.dat",
                        std::ios::in | std::ios::out | std::ios::binary);
    }
}

void SailingIO::reset() {
    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);
}

void SailingIO::createSailing(const SailingRecord& rec) {
    fileStream.seekp(0, std::ios::end);
    fileStream.write(reinterpret_cast<const char*>(&rec), sizeof rec);
    fileStream.flush();
}

void SailingIO::deleteSailing(const std::string& sailingID) {
    // Linear search, overwrite with last record, truncate...
}

bool SailingIO::checkSailingsForVessel(const std::string& vesselName) {
    SailingRecord rec;
    reset();
    while (fileStream.read(reinterpret_cast<char*>(&rec), sizeof rec)) {
        if (rec.vesselName == vesselName) return true;
    }
    return false;
}

void SailingIO::addPeopleOccupants(const std::string& id, int count) {
    // Locate record, inc field, write back in-place...
}

int SailingIO::getPeopleOccupants(const std::string& id) {
    // Search for record, return rec.peopleOccupants
}

void SailingIO::printSailingReport() {
    SailingRecord rec;
    reset();
    while (fileStream.read(reinterpret_cast<char*>(&rec), sizeof rec)) {
        // Format and print rec data, paginate every 5 lines...
    }
}

void SailingIO::close() {
    fileStream.close();
}
