//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
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
#include "vessel.h"
#include "vessel_io.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <limits>

namespace {
    const std::string FILENAME = "sailings.dat";
    std::fstream fs;
    using Record = Sailing::Record;
}

static constexpr float vehicleBuf = 0.5f;

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
// In sailing_io.cpp

bool SailingIO::updateOccupants(const std::string& sailingID,
                                int numPeople,
                                float vehicleLength)
{
    reset();
    Record temp;
    std::streamoff pos;
    while ((pos = fs.tellg()), fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            // 1) Adjust cumulative vehicle‐metres + buffer
            float buf = (vehicleLength > 0 ? vehicleBuf : -vehicleBuf);
            temp.LCU += (vehicleLength + buf);

            // 2) Adjust people count
            temp.ppl_on_board += numPeople;

            // 3) Adjust vehicle count (+1 on create, –1 on cancel)
            temp.veh_on_board += (vehicleLength > 0 ? 1 : -1);

            // write back
            fs.clear();
            fs.seekp(pos, std::ios::beg);
            fs.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            fs.flush();
            return true;
        }
    }
    std::cerr << "Error: Sailing ID not found: " << sailingID << "\n";
    return false;
}




// — checkSailingVehicleCapacity —
// returns true if *either* lane has any room left
bool SailingIO::checkSailingVehicleCapacity(const std::string& sailingID) {
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            // if either remaining‑high or remaining‑low length is > 0
            return (temp.HRL > 0.0f) || (temp.LRL > 0.0f);
        }
    }
    return false;
}

// — checkSailingPeopleCapacity —
// returns true if we can add `occupants` more without exceeding vessel's passenger cap
bool SailingIO::checkSailingPeopleCapacity(const std::string& sailingID,
                                           unsigned int occupants)
{
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            // read vessel's max passenger capacity
            VesselRecord vRec;
            if (!VesselIO::readVessel(temp.vessel_ID, vRec))
                return false;
            return (static_cast<unsigned>(temp.ppl_on_board) + occupants)
                   <= static_cast<unsigned>(vRec.maxPassengers);
        }
    }
    return false;
}

// — getHighRemLaneLength —
// returns true if the high‑ceiling lane has at least `length` metres free
bool SailingIO::getHighRemLaneLength(const std::string& sailingID, float length) {
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            return temp.HRL >= ( length + vehicleBuf );
        }
    }
    return false;
}

// — getLowRemLaneLength —
// returns true if the low‑ceiling lane has at least `length` metres free
bool SailingIO::getLowRemLaneLength(const std::string& sailingID, float length) {
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            return temp.LRL >= ( length + vehicleBuf );
        }
    }
    return false;
}

// — updateSailingForHigh —
// subtract `length` metres from HRL and add `occupants` to on_board
void SailingIO::updateSailingForHigh(const std::string& sailingID,
                                     float length)
{
    reset();
    Record temp;
    std::streamoff pos;
    while ((pos = fs.tellg()), fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            float buf = (length > 0 ? vehicleBuf : -vehicleBuf);
            temp.HRL -= (length + buf);
            fs.clear();
            fs.seekp(pos, std::ios::beg);
            fs.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            fs.flush();
            return;
        }
    }
}

void SailingIO::updateSailingForLow(const std::string& sailingID,
                                    float length)
{
    reset();
    Record temp;
    std::streamoff pos;
    while ((pos = fs.tellg()), fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            float buf = (length > 0 ? vehicleBuf : -vehicleBuf);
            temp.LRL -= (length + buf);
            fs.clear();
            fs.seekp(pos, std::ios::beg);
            fs.write(reinterpret_cast<const char*>(&temp), sizeof temp);
            fs.flush();
            return;
        }
    }
}


int SailingIO::getPeopleOccupants(const std::string& sailingID) {
    reset();
    Record temp;
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID)
            return temp.ppl_on_board;
    }
    return -1;
}

int SailingIO::getVehicleOccupants(const std::string& sailingID) {
    reset();                        // rewind to file start
    Record temp;
    // scan for the matching sailingID
    while (fs.read(reinterpret_cast<char*>(&temp), sizeof temp)) {
        if (std::string(temp.sailingID) == sailingID) {
            return temp.veh_on_board;   // return occupant count
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
    // 1) Read all records
    reset();
    std::vector<Record> recs;
    Record tmp;
    while (fs.read(reinterpret_cast<char*>(&tmp), sizeof tmp)) {
        recs.push_back(tmp);
    }

    // 2) Chronological sort by DD then HH parsed out of sailingID = "TER-DD-HH"
    auto parse_dt = [](const std::string &sid) {
        size_t p1 = sid.find('-');
        size_t p2 = sid.find('-', p1 + 1);
        int day  = std::stoi(sid.substr(p1 + 1, p2 - p1 - 1));
        int hour = std::stoi(sid.substr(p2 + 1));
        return std::make_pair(day, hour);
    };
    std::sort(recs.begin(), recs.end(),
        [&](auto &a, auto &b) {
            auto da = parse_dt(a.sailingID);
            auto db = parse_dt(b.sailingID);
            if (da.first != db.first) return da.first < db.first;
            return da.second < db.second;
        }
    );

    // 3) Print header once
    const int w1 = 11,  w2 = 25,
              w3 = 8,   w4 = 9,
              w5 = 15,  w6 = 15,
              w7 = 15,  w8 = 15;
    std::cout << std::left
              << std::setw(w1) << "SailingID"
              << std::setw(w2) << "VesselName"
              << std::setw(w3) << "LRL"
              << std::setw(w4) << "HRL"
              << std::setw(w5) << "TotalVehicles"
              << std::setw(w6) << "%VehiclesUsed"
              << std::setw(w7) << "TotalPeople"
              << std::setw(w8) << "%PeopleUsed"
              << "\n"
              << std::string(w1+w2+w3+w4+w5+w6+w7+w8, '=') << "\n";

    // 4) Print rows with pagination
    const int pageSize = 5;
    int printed = 0;
    char choice;

    for (auto &r : recs) {
        // fetch live metrics
        int totalVehicles = getVehicleOccupants(r.sailingID);
        int totalPeople   = getPeopleOccupants(r.sailingID);

        // get vessel capacities to compute “% used”
        VesselRecord vRec{};
        float vehPct = 0.0f, pplPct = 0.0f;
        if (VesselIO::readVessel(r.vessel_ID, vRec)) {
            float totalLane = vRec.highLaneLength + vRec.lowLaneLength;
            float usedLane  = r.LCU;
            vehPct = totalLane > 0
                     ? (usedLane / totalLane) * 100.0f
                     : 0.0f;
            pplPct = vRec.maxPassengers > 0
                     ? (static_cast<float>(totalPeople) / vRec.maxPassengers) * 100.0f
                     : 0.0f;
        }

        // format floats to 2 decimals and append '%'
        std::ostringstream ssLRL, ssHRL, ssVehPct, ssPplPct;
        ssLRL   << std::fixed << std::setprecision(2) << r.LRL;
        ssHRL   << std::fixed << std::setprecision(2) << r.HRL;
        ssVehPct<< std::fixed << std::setprecision(2) << vehPct << '%';
        ssPplPct<< std::fixed << std::setprecision(2) << pplPct << '%';

        // row output
        std::cout << std::left
                  << std::setw(w1) << r.sailingID
                  << std::setw(w2) << r.vessel_ID
                  << std::setw(w3) << ssLRL.str()
                  << std::setw(w4) << ssHRL.str()
                  << std::setw(w5) << totalVehicles
                  << std::setw(w6) << ssVehPct.str()
                  << std::setw(w7) << totalPeople
                  << std::setw(w8) << ssPplPct.str()
                  << "\n";

        // paginate every pageSize rows
        if (++printed % pageSize == 0 && printed < (int)recs.size()) {
            std::cout << "\nEnd of Page—press 'm' for more or '0' to quit: ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choice == '0') break;
        }
    }
}

void SailingIO::close() {
    fs.close();
}

void SailingIO::printCheckVehicles(const std::string& sailingID) {
    if (!checkSailingExists(sailingID)) {
        std::cout << "Sailing ID " << sailingID << " not found.\n";
        return;
    }

    // Get sailing record
    Record sailingRec;
    SailingIO::reset();
    while (fs.read(reinterpret_cast<char*>(&sailingRec), sizeof(sailingRec))) {
        if (std::string(sailingRec.sailingID) == sailingID) {
            break;
        }
    }

    // Get vessel information
    VesselRecord vesselRec;
    if (!VesselIO::readVessel(sailingRec.vessel_ID, vesselRec)) {
        std::cerr << "Error: Could not read vessel record for " << sailingRec.vessel_ID << "\n";
        return;
    }

    // Calculate metrics
    float totalLaneLength = vesselRec.highLaneLength + vesselRec.lowLaneLength;
    float usedLaneLength = sailingRec.LCU;
    float lanePercentFull = (totalLaneLength > 0) ? 
                          (usedLaneLength / totalLaneLength) * 100 : 0;
    
    float peoplePercentFull = (vesselRec.maxPassengers > 0) ?
                            (static_cast<float>(sailingRec.ppl_on_board) / vesselRec.maxPassengers) * 100 : 0;

    // Print report
    std::cout << "===== Vehicles on Board =====\n";
    std::cout << std::left << std::setw(25) << "Sailing ID:" << sailingRec.sailingID << "\n";
    std::cout << std::left << std::setw(25) << "Vessel Name:" << sailingRec.vessel_ID << "\n";
    std::cout << std::left << std::setw(25) << "Low Remaining Length:" 
              << std::fixed << std::setprecision(2) << sailingRec.LRL << " metres\n";
    std::cout << std::left << std::setw(25) << "High Remaining Length:" 
              << sailingRec.HRL << " metres\n";
    std::cout << std::left << std::setw(25) << "Vehicles On Board:" 
              << sailingRec.veh_on_board << "\n";
    std::cout << std::left << std::setw(25) << "Lane Capacity Used:" 
              << lanePercentFull << "%\n";
    std::cout << std::left << std::setw(25) << "Passenger Capacity Used:" 
              << peoplePercentFull << "%\n";
}