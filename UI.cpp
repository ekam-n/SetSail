//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// main.cpp
// Description:
// This module serves as the entry point for the ferry reservation system.
// It handles the main menu and orchestrates the startup/shutdown of the system.
//
// Revision History:
// Rev. 1 - 2025/07/23 - Team 12
// - Created initial version
//*******************************
#include <iostream>
#include <string>
#include <limits>
#include "main.h"
#include "ui.h"
#include "vehicle.h"
#include "reservation.h"
#include "vessel.h"
#include "sailing.h"
using namespace std;

void UserInterface::clearInput() {
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool UserInterface::init() {
  return true; // bool or void?
}

bool UserInterface::shutdown() {
  shutdown()
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
    << "[5] Print Sailing Report\n";
}

int UserInterface::getChoice() {
  int choice;
  cin >> choice;
  clearInput();
  return choice;
}

// VESSELS
void UserInterface::chooseVessel() {
  cout << "===== Vessels =====\n"
    << "[1] Create_vessel\n"
    << "[2] Delete_vessel\n";
  cout << "Enter selection: ";
  int choice = getChoice();
  if (choice == 1) {
    cout << "Enter vessel capacity for people (1-3600): ";
    int passNum = getChoice();
    cout << "Enter high ceiling lane length (1-3600): ";
    float hcll;
    cin >> hcll;
    clearInput();
    cout << "Enter low ceiling lane length (1-3600): ";
    float lcll;
    cin >> lcll;
    clearInput();
    cout << "Enter name of new vessel (1-25 characters): ";
    string vesselID;
    cin >> vesselID;
    clearInput();
    if (Vessel::createVessel(vesselID, hcll, lcll, passNum))
      cout << "Vessel successfully created.\n";
    else 
      cout << "Vessel creation failed, name may already exist.\n";
  } else if (choice == 2) {
    string vesselID;
    cout << "Enter the name of the vessel to be deleted: ";
    cin >> vesselID;
    clearInput();
    cout << "Are you sure you wish to delete the vessel, " << vesselID << "? [Y/N] ";
    char decision;
    cin >> decision;
    if (decision == 'N') {
      cout << "Vessel not deleted";
    } else if (decision == 'Y') {
      if Vessel::deleteVessel(vesselID) 
        cout << "Vessel successfully deleted.\n";
      else 
        cout << "Vessel not found.\n";
    }
  }
}

// SAILINGS
void UserInterface::chooseSailing() {
  cout << "===== Sailings =====\n"
    << "[1] Create_sailing\n"
    << "[2] Delete_sailing\n";
  cout << "Enter selection: ";
  int choice = getChoice();
  if (choice == 1) {
    string sailingID, vesselName, departTerm, departDay, departTime;
    cout << "Enter name of vessel for sailing: ";
    cin >> vesselName;
    clearInput();
    cout << "Enter sailing departure terminal: ";
    cin >> departTerm;
    clearInput();
    cout << "Enter day of departure (DD-MM-YY): ";
    cin >> departDay;
    clearInput();
    cout << "Enter time of departure in 24-hour time: ";
    cin >> departTime;
    clearInput();
    if (!(Sailing::createSailing(vesselName, departTerm, departDay, departTime))) 
      cout << "Sailing ID could not be created\n"
  } else if (choice == 2) {
    string sailingID;
    cout << "Enter sailing ID of sailing to be deleted: ";
    cin >> sailingID;
    clearInput();
    cout << "Are you sure you wish to delete the sailing, " << sailingID << "? [Y/N] ";
    char decision;
    cin >> decision;
    if (decision == 'N') {
      cout << "Sailing not deleted";
    } else if (decision == 'Y') {
      if Sailing::deleteSailing(sailingID) 
        cout << "Sailing successfully deleted.\n";
      else 
        cout << "Sailing not found or may have current reservations.\n";
    }
  }
}

// RESERVATIONS
void chooseReservation() {
  cout << "===== Reservations =====\n"
    << "[1] Create_reservation\n"
    << "[2] Cancel_reservation\n";
  cout << "Enter selection: ";
  int choice = getChoice();
  if (choice ==1) {
    string sailingID, vehicleLicense, phoneNum;
    int occupants;
    char specialVehicle;
    cout << "Enter sailing ID of the sailing to be reserved: ";
    cin >> sailingID;
    clearInput();
    cout << "Enter number of vehicle on board: ";
    cin >> occupants;
    clearInput();
    cout << "Enter vehicle license: ";
    cin >> vehicleLicense; 
    clearInput();
    cout << "Please enter a phone number (###-###-####): ";
    cin >> phoneNum;
    clearInput();
    cout << "Is your vehicle over 2 metres tall and/or longer than 7 metres? [Y/N] ";
    cin >> specialVehicle;
    clearInput();
    if (specialVehicle == "N") {
      if (Reservation::createReservation(sailingID, vehicleLicense, occupants, phoneNum)) {
        cout << "Reservation successfully created.\n"
        return;
      }
    } else if (specialVehicle == "Y") {
      float height, length;
      cout << "Enter vehicle height in metres (only the value): ";
      cin >> height;
      clearInput();
      cout << "Enter vehicle length in metres (only the value): ";
      cin >> length;
      clearInput();
      if (Reservation::createSpecialReservation(sailingID, vehicleLicense, occupants, height, length, phoneNum)) {
        cout << "Reservation successfully created.\n"
        return;
      }
    }
  } else if (choice == 2) {
    string vehicleLicense;
    cout << "Enter vehicle license: ";
    cin >> vehicleLicense;
    clearInput();
    if (Reservation::cancelReservation(vehicleLicense))
      cout << "Reservation successfully cancelled.";
    else 
      cout << "Error: reservation not cancelled."
  }
}

// CHECK-IN
void checkin() {
  cout << "===== Check-In =====\n"
  << "[1] Vehicles_on_board\n"
  << "[2] Log_arrivals\n";
  cout << "Enter selection: ";
  int choice = getChoice();
  if (choice == 1) {
    string sailingID;
    cout << "Enter sailing ID of the sailing to be viewed: "; 
    cin >> sailingID;
    Sailing::getVehicleOccupantsForReservation(sailingID); 
    // "end of report" written here or in function?
  } else if (choice == 2) {
    string sailingID;
    cout << "Enter sailing ID of the sailing to be reserved: ";
    cin >> sailingID;
    clearInput();

    string license;
    while (true) {
      cout << "Enter vehicle license (or 0 to return to main menu): ";
      cin >> license;
      clearInput();
      if (license == "0") {
        break;
      } else { 
        Reservation::checkin(sailingID, license);
        cout << "Vehicle successfully checked in."
      }
    }
  }
}

// PRINT SAILING REPORT
void printSailing() {
  printSailingReport()
}

bool interface() {
  while (true) {
    displayMainMenu();
    int choice = getChoice();
    switch (choice) {
      case 1: chooseVessel(); break;
      case 2: chooseSailing(); break;
      case 3: chooseReservation(); break;
      case 4: checkin(); break;
      case 5: printSailing(); break;
      case 0: shutdown(); return 0;
      default: cout << "Invalid selection. \n";
    }
  }
  return 1;
}



// random