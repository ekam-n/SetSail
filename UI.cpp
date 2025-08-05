// ui.cpp

#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>
#include "ui.h"
#include "vehicle.h"
#include "reservation.h"
#include "vessel.h"
#include "sailing.h"

using namespace std;

void UserInterface::clearInput() {
    // clear any error state, then drop the rest of the line
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool UserInterface::startup() {
    Vessel::init();
    Sailing::init();
    Reservation::init();
    Vehicle::init();
    return true;
}

bool UserInterface::shutdown() {
    Sailing::shutdown();
    Reservation::shutdown();
    Vehicle::shutdown();
    Vessel::shutdown();
    return true;
}

void UserInterface::displayMainMenu() {
    cout << "\n[ MAIN MENU ]\n\n"
         << "[1] Vessels\n"
         << "   -  Create_vessel\n"
         << "   -  Delete_vessel\n"
         << "[2] Sailings\n"
         << "   -  Create_sailing\n"
         << "   -  Delete_sailing\n"
         << "[3] Reservations\n"
         << "   -  Create_reservation\n"
         << "   -  Delete_reservation\n"
         << "[4] Check-In\n"
         << "   -  Vehicles_on_board\n"
         << "   -  Log_arrivals\n"
         << "[5] Print Sailing Report\n"
         << "========================\n"
         << "[0] Shutdown\n\n";
}

int UserInterface::getChoice() {
    int choice;
    while (true) {
        // prompt before every attempt
        std::cout << "Enter selection: ";
        
        if (std::cin >> choice) {
            clearInput();    // consume any leftover on the line
            return choice;
        }
        
        // failed to parse an int
        std::cout << "Invalid input. Please enter a valid number.\n";
        clearInput();       // clear error state and discard bad input
    }
}

// VESSELS
void UserInterface::chooseVessel() {
    cout << "\n===== Vessels =======\n"
         << "[1] Create_vessel\n"
         << "[2] Delete_vessel\n"
         << "=======================\n"
         << "[0] Return to main menu\n\n";

    while (true) {
        int choice = getChoice();

        if (choice == 0) {
            // back to main
            return;

        } else if (choice == 1) {
            // -- Create_vessel logic (unchanged) --
            int passNum;
            do {
                cout << "Enter vessel capacity for people (1-3600): ";
                if (!(cin >> passNum) || passNum < 1 || passNum > 3600) {
                    cout << "Invalid capacity. Please enter a number between 1 and 3600.\n";
                    clearInput();
                } else break;
            } while (true);
            clearInput();

            float hcll;
            do {
                cout << "Enter high ceiling lane length (1-3600): ";
                if (!(cin >> hcll) || hcll <= 0 || hcll > 3600) {
                    cout << "Invalid length. Please enter a value > 0 and <= 3600.\n";
                    clearInput();
                } else break;
            } while (true);
            clearInput();

            float lcll;
            do {
                cout << "Enter low ceiling lane length (1-3600): ";
                if (!(cin >> lcll) || lcll <= 0 || lcll > 3600) {
                    cout << "Invalid length. Please enter a value > 0 and <= 3600.\n";
                    clearInput();
                } else break;
            } while (true);
            clearInput();

            string vesselID;
            do {
                cout << "Enter name of new vessel (1-25 characters): ";
                getline(cin, vesselID);
                if (vesselID.empty() || vesselID.size() > 25) {
                    cout << "Invalid name. Please enter between 1 and 25 characters.\n";
                } else break;
            } while (true);

            if (Vessel::createVessel(vesselID, passNum, hcll, lcll))
                cout << "Vessel successfully created.\n";
            else
                cout << "Vessel creation failed, name may already exist.\n";

            return;  // done

        } else if (choice == 2) {
            // -- Delete_vessel logic (unchanged) --
            string vesselID;
            cout << "Enter the name of the vessel to be deleted: ";
            getline(cin, vesselID);
            if (vesselID.empty()) {
                cout << "Invalid vessel name.\n";
                return;
            }
            cout << "Are you sure you wish to delete the vessel, " << vesselID << "? [Y/N] ";
            char decision;
            cin >> decision;
            clearInput();
            if (decision == 'N' || decision == 'n') {
                cout << "Vessel not deleted.\n";
            } else if (decision == 'Y' || decision == 'y') {
                if (Vessel::deleteVessel(vesselID)) {
                    cout << "Vessel successfully deleted.\n";
                } else {
                    cout << "Vessel not found.\n";
                }
            } else {
                cout << "Invalid choice. Returning to menu.\n";
            }

            return;  // done

        } else {
            cout << "Invalid selection. Please enter 1, 2, or 0 to return.\n";
        }
    }
}


// SAILINGS
void UserInterface::chooseSailing() {
    cout << "\n===== Sailings ========\n"
         << "[1] Create_sailing\n"
         << "[2] Delete_sailing\n"
         << "=======================\n"
         << "[0] Return to main menu\n\n";

    while (true) {
        int choice = getChoice();

        if (choice == 0) {
            return;

        } else if (choice == 1) {
            // -- Create_sailing logic (unchanged) --
            string departTerm;
            do {
                cout << "Enter sailing departure terminal: ";
                getline(cin, departTerm);
                if (departTerm.empty()) cout << "Invalid terminal.\n";
                else break;
            } while (true);

            string departDay;
            do {
                cout << "Enter day of departure (DD): ";
                getline(cin, departDay);
                if (departDay.size() != 2 || !isdigit(departDay[0]) || !isdigit(departDay[1]))
                    cout << "Invalid day format. Use DD.\n";
                else break;
            } while (true);

            string departTime;
            do {
                cout << "Enter time of departure in 24-hour time (HH): ";
                getline(cin, departTime);
                if (departTime.size() != 2 || !isdigit(departTime[0]) || !isdigit(departTime[1]))
                    cout << "Invalid time format. Use HH.\n";
                else break;
            } while (true);

            string vesselName;
            do {
                cout << "Enter name of vessel for sailing: ";
                getline(cin, vesselName);
                if (vesselName.empty()) cout << "Invalid vessel name.\n";
                else break;
            } while (true);

            if (!Sailing::createSailing(vesselName, departTerm, departDay, departTime))
                cout << "Sailing ID could not be created.\n";

            return;

        } else if (choice == 2) {
            // -- Delete_sailing logic (unchanged) --
            string sailingID;
            cout << "Enter sailing ID of sailing to be deleted: ";
            getline(cin, sailingID);
            if (sailingID.empty()) {
                cout << "Invalid sailing ID.\n";
                return;
            }
            cout << "Are you sure you wish to delete the sailing, " << sailingID << "? [Y/N] ";
            char decision;
            cin >> decision;
            clearInput();
            if (decision == 'N' || decision == 'n') {
                cout << "Sailing not deleted.\n";
            } else if (decision == 'Y' || decision == 'y') {
                if (Sailing::deleteSailing(sailingID))
                    cout << "Sailing successfully deleted.\n";
                else
                    cout << "Sailing not found or may have current reservations.\n";
            } else {
                cout << "Invalid choice. Returning to menu.\n";
            }

            return;

        } else {
            cout << "Invalid selection. Please enter 1, 2, or 0 to return.\n";
        }
    }
}

// RESERVATIONS
void UserInterface::chooseReservation() {
    cout << "\n===== Reservations ====\n"
         << "[1] Create_reservation\n"
         << "[2] Cancel_reservation\n"
         << "=======================\n"
         << "[0] Return to main menu\n\n";

    while (true) {
        int choice = getChoice();

        if (choice == 0) {
            return;

        } else if (choice == 1) {
            // -- Create_reservation logic (unchanged) --
            string sailingID;
            do {
                cout << "Enter sailing ID of the sailing to be reserved: ";
                getline(cin, sailingID);
                if (sailingID.empty()) cout << "Invalid sailing ID.\n";
                else break;
            } while (true);

            unsigned int occupants;
            do {
                cout << "Enter number of occupants: ";
                if (!(cin >> occupants) || occupants == 0) {
                    cout << "Invalid number. Must be > 0.\n";
                    clearInput();
                } else break;
            } while (true);
            clearInput();

            char specialVehicle;
            do {
                cout << "Is your vehicle over 2 metres tall and/or longer than 7 metres? [Y/N] ";
                cin >> specialVehicle;
                clearInput();
                if (specialVehicle=='Y' || specialVehicle=='N' || specialVehicle == 'y' || specialVehicle == 'n') break;
                else cout << "Invalid choice. Enter Y or N.\n";
            } while (true);

            string vehicleLicense;
            do {
                cout << "Enter vehicle license: ";
                getline(cin, vehicleLicense);
                if (vehicleLicense.empty()) cout << "Invalid license.\n";
                else break;
            } while (true);

            string phoneNum;
            do {
                cout << "Please enter a phone number (###-###-####): ";
                getline(cin, phoneNum);
                if (phoneNum.size() != 12 || phoneNum[3]!='-' || phoneNum[7]!= '-')
                    cout << "Invalid format. Use ###-###-####.\n";
                else break;
            } while (true);

            bool success = false;
            if (specialVehicle == 'N' || specialVehicle == 'n') {
                success = Reservation::createReservation(sailingID, vehicleLicense, occupants, phoneNum);
            } else {
                float height;
                do {
                    cout << "Enter vehicle height in metres (only the value): ";
                    if (!(cin >> height) || height <= 2.0f) {
                        cout << "Invalid height. Must be > 2 metres.\n";
                        clearInput();
                    } else break;
                } while (true);
                clearInput();

                float length;
                do {
                    cout << "Enter vehicle length in metres (only the value): ";
                    if (!(cin >> length) || length <= 7.0f) {
                        cout << "Invalid length. Must be > 7 metres.\n";
                        clearInput();
                    } else break;
                } while (true);
                clearInput();

                success = Reservation::createSpecialReservation(
                             sailingID, vehicleLicense, occupants,
                             phoneNum, height, length);
            }

            cout << (success
                      ? "Reservation successfully created.\n"
                      : "Reservation creation failed.\n");
            return;

        } else if (choice == 2) {
            // -- Cancel_reservation logic (unchanged) --
            string vehicleLicense;
            do {
                cout << "Enter vehicle license: ";
                getline(cin, vehicleLicense);
                if (vehicleLicense.empty()) cout << "Invalid license.\n";
                else break;
            } while (true);

            string sailingID;
            do {
                cout << "Enter the sailing ID: ";
                getline(cin, sailingID);
                if (sailingID.empty()) cout << "Invalid sailing ID.\n";
                else break;
            } while (true);

            cout << "Are you sure you wish to delete the reservation for "
                 << sailingID << "? [Y/N] ";
            char decision;
            cin >> decision;
            clearInput();
            if (decision == 'N' || decision == 'n') {
                cout << "Reservation not deleted.\n";
            } else if (decision == 'Y' || decision == 'y') {
                if (Reservation::cancelReservation(sailingID, vehicleLicense)) {
                    cout << "Reservation successfully cancelled.\n";
                } else {
                    cout << "Error: reservation not cancelled.\n";
                }
            } else {
                cout << "Invalid choice.\n";
            }
            return;

        } else {
            cout << "Invalid selection. Please enter 1, 2, or 0 to return.\n";
        }
    }
}

// CHECK-IN
void UserInterface::checkin() {
    cout << "\n===== Check-In ========\n"
         << "[1] Vehicles_on_board\n"
         << "[2] Log_arrivals\n"
         << "=======================\n"
         << "[0] Return to main menu\n\n";

    while (true) {
        int choice = getChoice();

        if (choice == 0) {
            return;

        } else if (choice == 1) {
            // -- Vehicles_on_board logic (unchanged) --
            string sailingID;
            do {
                cout << "Enter sailing ID of the sailing to be viewed: ";
                getline(cin, sailingID);
                if (sailingID.empty()) cout << "Invalid sailing ID.\n";
                else break;
            } while (true);
            Sailing::printVehicleReport(sailingID);
            return;

        } else if (choice == 2) {
            // -- Log_arrivals logic (unchanged) --
            string sailingID;
            do {
                cout << "Enter sailing ID of the sailing to be reserved: ";
                getline(cin, sailingID);
                if (sailingID.empty()) cout << "Invalid sailing ID.\n";
                else break;
            } while (true);

            string license;
            while (true) {
                cout << "Enter vehicle license (or 0 to return to main menu): ";
                getline(cin, license);
                if (license == "0") {
                    break;
                } else if (license.empty()) {
                    cout << "Invalid license.\n";
                } else {
                    if (Reservation::logArrivals(sailingID, license)) {
                        cout << "Vehicle successfully checked in.\n";
                    } else {
                        cout << "Error: Reservation not found\n";
                    }
                }
            }
            return;

        } else {
            cout << "Invalid selection. Please enter 1, 2, or 0 to return.\n";
        }
    }
}

// PRINT SAILING REPORT
void UserInterface::printSailing() {
    cout << "\n===== Sailing Report ============================================================================================\n";
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    cout << put_time(localTime, "%B %d %H:%M %Z\n\n");
    Sailing::printSailingReport();
}

bool UserInterface::interface() {
    while (true) {
        displayMainMenu();
        int choice = getChoice();
        switch (choice) {
            case 1: chooseVessel(); break;
            case 2: chooseSailing(); break;
            case 3: chooseReservation(); break;
            case 4: checkin(); break;
            case 5: printSailing(); break;
            case 0: shutdown(); return true;
            default: cout << "Invalid selection. Please choose a valid menu option.\n";
        }
    }
}
