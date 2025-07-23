//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel_io.cpp
// CMPT 276 - Assignment 4
// Description: Implements binary file operations for Vessel records.
// Version: 1.1
// Author: group12
// History: v2.0
// - 1.0: Initial version (2025-07-17)
// - 1.1: Fixed file descriptor error and added cross-platform truncation logic (2025-07-18)
// - 2.0: make sure there are no Vessel(...) constructor calls (2025-07-23)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "vessel_io.h"
#include <iostream>
#include <cstring>
#include <fcntl.h>     // open()
#include <unistd.h>    // ftruncate(), close()
#include <sys/stat.h>  // open flags

const int RECORD_SIZE = sizeof(Vessel);

//------------------------------------------------------------------------------
// Writes a Vessel to the end of the file
void writeVessel(std::fstream& file, const Vessel& v) {
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char*>(&v), RECORD_SIZE);
}

//------------------------------------------------------------------------------
// Reads a Vessel from the current file position
bool readVessel(std::fstream& file, Vessel& v) {
    file.read(reinterpret_cast<char*>(&v), RECORD_SIZE);
    return file.gcount() == RECORD_SIZE;
}

//------------------------------------------------------------------------------
// Seeks to the N-th record in the file
void seekVessel(std::fstream& file, int index) {
    file.seekg(index * RECORD_SIZE, std::ios::beg);
    file.seekp(index * RECORD_SIZE, std::ios::beg);
}

//------------------------------------------------------------------------------
// Gets number of Vessel records in file
int getVesselCount(std::fstream& file) {
    file.seekg(0, std::ios::end);
    return file.tellg() / RECORD_SIZE;
}

//------------------------------------------------------------------------------
// Truncates the file to remove the last record
void truncateLastVessel(std::fstream& file) {
    file.flush();
    std::string filename = "vessels.dat";  // Make sure this matches your actual file name

    // Close the file before truncating
    file.close();

    int fd = open(filename.c_str(), O_RDWR);
    if (fd < 0) {
        std::cerr << "Error: Cannot open file for truncation\n";
        return;
    }

    off_t newSize = lseek(fd, 0, SEEK_END) - sizeof(Vessel);
    ftruncate(fd, newSize);
    close(fd);

    // Reopen the file
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
}
