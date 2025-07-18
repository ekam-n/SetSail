//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// main.cpp
// Description:
// This module serves as the entry point for the ferry reservation system.
// It handles the main menu and orchestrates the startup/shutdown of the system.
//
// Revision History:
// Rev. 1 - 2025/07/17 - Team 12
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

void clearInput() {
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMainMenu() {
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

int getChoice() {
  int choice;
  cin >> choice;
  clearInput();
  return choice;
}

// VESSELS
void chooseVessel() {
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
    if (createVessel(vesselID, hcll, lcll, passNum))
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
      if deleteVessel(vesselID) 
        cout << "Vessel successfully deleted.\n";
      else 
        cout << "Vessel not found.\n";
    }
  }
}

// SAILINGS
void chooseSailing() {
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
    if (createSailing(vesselName, departTerm, departDay, departTime)) // REMOVE SAILING ID ARGUMENT + ASKING FOR IT IN CIN!!!!!
      cout << "Sailing successfully created. The sailing ID is: " //ADD FUNCTION HERE!!!!!!!!!!
    else 
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
      if deleteSailing(sailingID) 
        cout << "Sailing successfully deleted.\n";
      else 
        cout << "Sailing not found or may have current reservations.\n";
    }
  }
}

// RESERVATIONS ->> CHECK / NOT FINISHED
void chooseReservation() {
  cout << "===== Reservations =====\n"
    << "[1] Create_reservation\n"
    << "[2] Cancel_reservation\n";
  cout << "Enter selection: ";
  int choice = getChoice();
  if (choice ==1) {
    string sailingID, vehicleLicense, phoneNum;
    int occupants;
    float fare, height, length;
    char specialVehicle
    cout << "Enter sailing ID of the sailing to be reserved: ";
    cin >> sailingID;
    clearInput();
    cout << "Enter number of vehicle on board: ";
    cin >> occupants;
    clearInput();
    cout << "Enter vehicle license: ";
    cin >> vehicleLicense;
    clearInput();
    if (createReservation(sailingID, vehicleLicense, occupants, outFare)) // WHY FARE as arg?!?!?
      cout << "Reservation successfully created.";
    else 
      cout << "Reservation failed, not created.";     
  } else if (choice == 2) {
    string vehicleLicense;
    cout << "Enter vehicle license: ";
    cin >> vehicleLicense;
    clearInput();
    if (cancelReservation(vehicleLicense))
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
    getVehicleOccupantsForReservation(sailingID); // says return 0 in function sailing.cpp
    // "end of report" written here or in function?
  } else if (choice == 2) {
    string sailingID;
    cout << "Enter sailing ID of the sailing to be reserved: ";
    cin >> sailingID;
    clearInput();

// NOT SURE ABOUT THIS
    string license;
    while (true) {
      cout << "Enter vehicle license (or 0 to return to main menu): ";
      cin >> license;
      clearInput();
      if (license == "0") {
        break;
      } else {
        logArrival(license) // reservation.h says parameter is sailing ID -> then prompts need to be given in function itself, not here!
        cout << "Vehicle’s fare is: $"
        cout << "Vehicle successfully checked in."
      }
    }
  }
}

// PRINT SAILING REPORT
void printSailing() {
  printSailingReport() // control for 5 more here or there?
}

int main () {
  if (!startup()) {
    cerr << "System startup failed.\n";
    return 1;
  }
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
}