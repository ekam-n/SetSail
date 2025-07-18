//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//*******************************
// main.cpp
// Description:
// This module serves as the entry point for the ferry reservation system.
// It handles the startup/shutdown of the system.
//
// Revision History:
// Rev. 1 - 2025/07/07 - Team 12
// - Created initial version
//*******************************

#include <iostream>
#include "main.h"
// #include "ui.h"

//------
// Description:
// Main calls UI and handles startup and shutdown functions
int main() {
  // if (!startup()) {
    // std::cerr << "System failed to start up.\n";
  // } 
  // displayMainMenu(); 
  shutdown();
  return 0;
}

void shutdown() {
    std::cout << "System shutting down...\n";
}

/* CODING CONVENTIONS
- Each file should begin with a comment stating the module name and a description 
  of the module's purpose.
- Followed by a version history, listing the most recent changes first.
- This section will be encased in a set of line segments, as follows:
//*******************************
- Before each function, a dividing line will be inserted, as follows:
//------
- Following the line, each function will contain a comment explaining what it does, 
  the return values, and any constraints (pre or post conditions)
- Function prototypes will have one parameter per line and comments to right.
- Parameters will be labeled [in], [in/out], or [out], denoted by the square brakets.
- Indentation will follow the default settings of VSCode.
- Function + Class names: camelCase starting with lowercase.
- Constants: ALL_CAPS_WITH_UNDERSCORES.
- Braces: opening braces go on the same line as function or control statement. 
  Closing braces go on their own line.
- For all classes, public members will be first, followed by private members
*/

/* The above conventions are used in an example:
//*******************************
// mathOps.h
// Description:
// This module provides a functions for basic the mathematical
// operations. 
//
// Revision History:
// Rev. 1 - 2025/07/05 - Team 12
//     - Created initial version with calculateAverage function.
//*******************************

//------
// Description:
// Calculates the average of two integers. Returns value as a double.
// Precondition:
// Both integers must be within the valid range of `int`.
double calculateAverage(
    int a,   // [in] first integer input
    int b    // [in] second integer input
);
*/
