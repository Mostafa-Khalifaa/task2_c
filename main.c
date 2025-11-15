#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "draw.h"
#include "screen.h"

int main()
{
  // Initialize input system (important for Linux)
    initInput();

    // Run the main menu
    runMainMenu();

    // Restore input settings before exit
    restoreInput();
    return 0;
}
