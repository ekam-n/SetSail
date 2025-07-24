//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// ui.h
// Description:
// This class handles all user interface operations including menu display,
// input handling, and user interaction for the ferry reservation system.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with initialization/shutdown
// Rev. 2 - 2025/07/23 - Team 12
// - Changed to static
//*******************************
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

class UserInterface {
public:
    //------
    // Description:
    // Initializes the UserInterface class. Returns true if successful.
    // Precondition:
    // None
    static bool init();

    //------
    // Description:
    // Displays main menu
    // Precondition:
    // None
    static bool shutdown();

    //------
    // Description:
    // Displays main menu
    // Precondition:
    // None
    static void displayMainMenu();

    //------
    // Description:
    // Gets input when int is desired
    // Precondition:
    // None
    static void getChoice();    
    
    //------
    // Description:
    // Displays operations for handeling vessels
    // Precondition:
    // None
    static void chooseVessel();    
    
    //------
    // Description:
    // Displays operations for handeling sailings
    // Precondition:
    // None
    static void chooseSailing();    
    
    //------
    // Description:
    // Displays operations for handeling reservations
    // Precondition:
    // None
    static void chooseReservation();    

    //------
    // Description:
    // Displays operations for handeling check-in
    // Precondition:
    // None
    static void checkin();

    //------
    // Description:
    // Displays operations for handeling printing of sailing reports
    // Precondition:
    // None
    static void printSailing();

    //------
    // Description:
    // Displays main menu
    // Precondition:
    // None
    static bool interface();

private:
    //------
    // Description:
    // clears remaining new line characters or spaces from input.
    // Precondition:
    // None
    static void clearInput();
};

#endif