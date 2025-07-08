//*******************************
//*******************************
// ui.h
// Description:
// This module handles all user interface interactions including menu display,
// input collection, and output formatting for the ferry reservation system.
//
// Revision History:
// Rev. 1 - 2025/07/06 - Team 12
// - Created initial version with all menu handling functions
//*******************************

#include <string>

//------
// Description:
// Displays the main menu and handles top-level user input.
// Returns when user selects exit option.
// Precondition:
// System must be initialized (startup completed)
// Postcondition:
// User session is complete
void displayMainMenu();

//------
// Description:
// Handles vessel management submenu (create/delete vessels).
// Precondition:
// None
// Postcondition:
// Returns to main menu when complete
void handleVesselMenu();

//------
// Description:
// Handles sailing management submenu (create/delete sailings).
// Precondition:
// None
// Postcondition:
// Returns to main menu when complete
void handleSailingMenu();

//------
// Description:
// Handles reservation management submenu (create/cancel reservations).
// Precondition:
// None
// Postcondition:
// Returns to main menu when complete
void handleReservationMenu();

//------
// Description:
// Handles check-in operations submenu (log arrivals, view capacity).
// Precondition:
// None
// Postcondition:
// Returns to main menu when complete
void handleCheckInMenu();