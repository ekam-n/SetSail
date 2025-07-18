//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// vessel_io.h
// CMPT 276 - Assignment 4
// Description: Binary file I/O for Vessel records
// Version: 1.0
// Author: [Your Name]
// History:
// - 1.0: Initial version (2025-07-17)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#ifndef VESSEL_IO_H
#define VESSEL_IO_H

#include <fstream>
#include "vessel.h"

// Writes a Vessel to the end of the file
void writeVessel(std::fstream& file, const Vessel& v);

// Reads a Vessel from current file position
bool readVessel(std::fstream& file, Vessel& v);

// Seeks to the N-th record in the file (0-based)
void seekVessel(std::fstream& file, int index);

// Returns the number of Vessel records in file
int getVesselCount(std::fstream& file);

// Truncates the file to remove the last record
void truncateLastVessel(std::fstream& file);

#endif // VESSEL_IO_H
