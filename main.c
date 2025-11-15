#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "input.h"
#include "menu.h"

int main() {
    // Initialize input system (important for Linux)
    initInput();

    // Run the main menu
    runMainMenu();

    // Restore input settings before exit
    restoreInput();

    return 0;
}
