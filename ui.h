//*******************************
//*******************************
// ui.h
// Description:
// This class handles all user interface operations including menu display,
// input handling, and user interaction for the ferry reservation system.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Converted to class format with initialization/shutdown
//*******************************

class UserInterface {
public:
    //------
    // Description:
    // Initializes the UserInterface class. Returns true if successful.
    // Precondition:
    // None
    bool init();

    //------
    // Description:
    // Shuts down the UserInterface class and releases resources.
    // Precondition:
    // Class must be initialized
    void shutdown();

    //------
    // Description:
    // Displays main menu
    // Precondition:
    // None
    void displayMainMenu();

    //------
    // Description:
    // Gets input when int is desired
    // Precondition:
    // None
    void getChoice();

    //------
    // Description:
    // Displays operations for handeling vessels
    // Precondition:
    // None
    void chooseVessel();

    //------
    // Description:
    // Displays operations for handeling sailings
    // Precondition:
    // None
    void chooseSailing();

    //------
    // Description:
    // Displays operations for handeling reservations
    // Precondition:
    // None
    void chooseReservation();

    //------
    // Description:
    // Displays operations for handeling check-in
    // Precondition:
    // None
    void checkin();

    //------
    // Description:
    // Displays operations for handeling printing of sailing reports
    // Precondition:
    // None
    void printSailing();

private:
    //------
    // Description:
    // clears remaining new line characters or spaces from input.
    // Precondition:
    // None
    void clearInput()
};