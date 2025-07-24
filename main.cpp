// main_interactive.cpp
#include "sailing.h"
#include "vessel.h"
#include <iostream>
#include <cstdio>

int main() {
    // Start fresh
    std::remove("sailings.dat");

    // Initialize the subsystem
    Sailing::init();
    Vessel::init();

    // Let’s create two sailings interactively

    Vessel::createVessel("Maria", "750", "150", "150");
    std::cout << "=== Create first sailing ===\n";
    Sailing::createSailing("Maria", "WIN", "24", "15");

    // std::cout << "\n=== Create second sailing ===\n";
    // Sailing::createSailing();

    // // Show what we have so far
    // std::cout << "\n=== Current sailings ===\n";
    // Sailing::printSailingReport();

    Sailing::shutdown();
    Vessel::shutdown();
    return 0;
}
