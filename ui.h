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

private:
    // Private member variables would be declared here
    // Example:
    // bool isInitialized;
    // MenuState currentMenuState;
};