// main.cpp
#include "sailing.h"
#include "sailing_io.h"

#include <cassert>
#include <cstdio>
#include <iostream>
#include <stdexcept>

int main() {
    // 1) Remove any old data file
    std::remove("sailings.dat");

    // ── Low‑level I/O tests using SailingIO ────────────────────────────────
    using Rec = Sailing::Record;

    // a) open/reset
    SailingIO::open();
    SailingIO::reset();

    // b) write three records
    Rec r1("ID1", "VESSEL_A", 100.0f, 50.0f);
    Rec r2("ID2", "VESSEL_B", 200.0f, 75.0f);
    Rec r3("ID3", "VESSEL_C", 300.0f, 25.0f);
    SailingIO::createSailing(r1);
    SailingIO::createSailing(r2);
    SailingIO::createSailing(r3);

    // c) verify default on_board == 0
    assert(SailingIO::getPeopleOccupants("ID1") == 0);
    assert(SailingIO::getPeopleOccupants("ID2") == 0);
    assert(SailingIO::getPeopleOccupants("ID3") == 0);
    std::cout << "[PASS] SailingIO initial writes & reads OK\n";

    // d) update occupants and verify
    SailingIO::addPeopleOccupants("ID2", 5);
    assert(SailingIO::getPeopleOccupants("ID2") == 5);
    std::cout << "[PASS] SailingIO addPeopleOccupants OK\n";

    // e) delete the middle record and verify
    SailingIO::deleteSailing("ID2");
    assert(SailingIO::getPeopleOccupants("ID1") == 0);
    assert(SailingIO::getPeopleOccupants("ID3") == 0);
    assert(SailingIO::getPeopleOccupants("ID2") == -1);
    std::cout << "[PASS] SailingIO deleteSailing OK\n";

    SailingIO::close();

    // ── High‑level API tests using Sailing ─────────────────────────────────
    Sailing::init();

    // a) getPeopleOccupantsForReservation should mirror the I/O layer
    assert(Sailing::getPeopleOccupantsForReservation("ID1") == 0);
    assert(Sailing::getPeopleOccupantsForReservation("ID3") == 0);
    std::cout << "[PASS] Sailing::getPeopleOccupantsForReservation OK\n";

    // b) addOccupants (people only) via Sailing API
    Sailing::addOccupants("ID3", 7, /*vehicleCount*/0);
    assert(Sailing::getPeopleOccupantsForReservation("ID3") == 7);
    std::cout << "[PASS] Sailing::addOccupants OK\n";

    // c) deleteSailing via Sailing API and check exception on lookup
    Sailing::deleteSailing("ID3");
    std::cout << "[PASS] Sailing::deleteSailing OK\n";
    try {
        Sailing::getPeopleOccupantsForReservation("ID3");
        // if we get here, test failed
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "[PASS] Sailing::validateSailingID threw as expected: "
                  << e.what() << "\n";
    }

    // d) checkVesselHasSailings
    // "VESSEL_C" was on ID3 (deleted) → false; "VESSEL_A" still on ID1 → true
    assert(!Sailing::checkVesselHasSailings("VESSEL_C"));
    assert( Sailing::checkVesselHasSailings("VESSEL_A"));
    std::cout << "[PASS] Sailing::checkVesselHasSailings OK\n";

    // e) Final report of what's left (only ID1)
    std::cout << "\nFinal report (should show only ID1):\n";
    Sailing::printSailingReport();

    Sailing::shutdown();
    return 0;
}
