//*******************************
//*******************************
// main.h
// Description:
// This module serves as the entry point for the ferry reservation system.
// It handles the main menu and orchestrates the startup/shutdown of the system.
//
// Revision History:
// Rev. 1 - 2025/07/05 - Team 12
// - Created initial version with startup and shutdown functions
//*******************************

//------
// Description:
// Initializes the system by opening all necessary files and loading initial data.
// Returns true if successful, false otherwise.
// Precondition:
// None
// Postcondition:
// System is ready for user interaction if return value is true
bool startup();

//------
// Description:
// Shuts down the system by saving data and closing files.
// Precondition:
// System must be in a valid state (startup was successful)
// Postcondition:
// All data is saved and resources are released
void shutdown();