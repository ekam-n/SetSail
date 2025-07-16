// main.cpp
#include "sailing.h"
#include "sailing_io.h"

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

int main() {
    // 1) Remove any old test file
    std::remove("sailings.dat");

    // 2) Open and reset
    SailingIO::open();
    SailingIO::reset();

    using Rec = Sailing::Record;

    // 3) Write three test records
    Rec r1("ID1", "VESSEL_A", 100.0f, 50.0f);
    Rec r2("ID2", "VESSEL_B", 200.0f, 75.0f);
    Rec r3("ID3", "VESSEL_C", 300.0f, 25.0f);

    SailingIO::createSailing(r1);
    SailingIO::createSailing(r2);
    SailingIO::createSailing(r3);

    // 4) Read back and verify count via on_board default = 0
    assert(SailingIO::getPeopleOccupants("ID1") == 0);
    assert(SailingIO::getPeopleOccupants("ID2") == 0);
    assert(SailingIO::getPeopleOccupants("ID3") == 0);

    std::cout << "[PASS] Initial writes OK\n";

    // 5) Add occupants to ID2, then verify
    SailingIO::addPeopleOccupants("ID2", 5);
    assert(SailingIO::getPeopleOccupants("ID2") == 5);
    std::cout << "[PASS] addPeopleOccupants OK\n";

    // 6) Delete the middle record ("ID2")
    SailingIO::deleteSailing("ID2");

    // Now ID1 and ID3 should still exist; ID2 should return -1
    assert(SailingIO::getPeopleOccupants("ID1") == 0);
    assert(SailingIO::getPeopleOccupants("ID3") == 0);
    assert(SailingIO::getPeopleOccupants("ID2") == -1);
    std::cout << "[PASS] deleteSailing OK\n";

    // 7) Print the remaining records
    std::cout << "\nRemaining records:\n";
    SailingIO::printSailingReport();

    SailingIO::close();
    return 0;
}
