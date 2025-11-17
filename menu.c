#include "menu.h"
#include "screen.h"
#include "draw.h"
#include "input.h"
#include "cursor.h"
#include <stdio.h>
#include <string.h>

#define MENU_START_X 30
#define MENU_START_Y 8

static const char* menuItems[MAX_MENU_ITEMS] = {
    "New",
    "Display",
    "Exit"
};

void initMenu(void) {
    clearScreen();
}
// Draws one button in the menu (with border and centered text)
// isSelected = 1 → highlight border color
void drawMenuButton(int x, int y, const char* text, int isSelected) {
    Color borderColor = isSelected ? BLUE : WHITE;
    Color textColor = WHITE;

    // Draw top border
    moveCursor(x, y);
    setColor(borderColor);
    printf("+");
    for (int i = 0; i < MENU_ITEM_WIDTH - 2; i++) {
        printf("-");
    }
    printf("+");
    resetColor();

    // Draw middle with text
    moveCursor(x, y + 1);
    setColor(borderColor);
    printf("| ");

    // Center the text
    setColor(textColor);
    int padding = (MENU_ITEM_WIDTH - 4 - strlen(text)) / 2;
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < MENU_ITEM_WIDTH - 4 - strlen(text) - padding; i++) printf(" ");

    setColor(borderColor);
    printf(" |");
    resetColor();

    // Draw bottom border
    moveCursor(x, y + 2);
    setColor(borderColor);
    printf("+");
    for (int i = 0; i < MENU_ITEM_WIDTH - 2; i++) {
        printf("-");
    }
    printf("+");
    resetColor();
}

void drawMenu(int selectedItem) {
    clearScreen();

    // Draw title
    drawText(MENU_START_X, 2, "=== Main Menu ===", CYAN);

    // Draw menu items
    int currentY = MENU_START_Y;
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        drawMenuButton(MENU_START_X, currentY, menuItems[i], i == selectedItem);
        currentY += MENU_ITEM_HEIGHT + 2;
    }

    // Draw instructions
    drawText(10, 22, "Use UP/DOWN arrows to navigate, Enter to select, ESC/Home to go back", YELLOW);
}

// Handles keyboard navigation (UP/DOWN/ENTER/ESC)
MenuItem handleMenuInput(void) {
int selectedItem = 0; // Default selected menu item
drawMenu(selectedItem);


while (1) {
int key = getKeyPress(); // Read key press


if (key == KEY_UP) {
selectedItem--; // Move selection up
if (selectedItem < 0) selectedItem = MAX_MENU_ITEMS - 1; // Wrap to bottom
drawMenu(selectedItem);
}
else if (key == KEY_DOWN) {
selectedItem++; // Move selection down
if (selectedItem >= MAX_MENU_ITEMS) selectedItem = 0; // Wrap to top
drawMenu(selectedItem);
}
else if (key == KEY_ENTER) {
return (MenuItem)selectedItem; // Confirm selection
}
else if (key == KEY_ESC || key == KEY_HOME) {
return MENU_EXIT; // Exit menu
}
}
}

void handleNewOption(void) {
    char message[256];

    clearScreen();
    drawText(5, 2, "=== New Message ===", CYAN);
    drawText(5, 4, "Enter your message: ", GREEN);

    moveCursor(26, 4);
    setColor(WHITE);
    fgets(message, sizeof(message), stdin); // Read user input

    // Remove newline
    //be sure the ENTER not go with text
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    clearScreen();
    drawText(5, 2, "=== Your Message ===", CYAN);
    drawText(5, 5, message, YELLOW);
    drawText(5, 8, "Press Enter to return to menu...", GREEN);
    resetColor();

    getchar();
}

void handleDisplayOption(void) {
    clearScreen();
    drawText(5, 2, "=== Display Information ===", CYAN);
    drawText(5, 5, "This is the display screen!", GREEN);
    drawText(5, 7, "Here you can show any information you want.", WHITE);
    drawText(5, 9, "Multiple lines of content can be displayed here.", YELLOW);
    drawText(5, 12, "Press Enter or ESC to return to menu...", MAGENTA);
    resetColor();
// Wait until user presses a valid exit key
    while (1) {
        int key = getKeyPress();
        if (key == KEY_ENTER || key == KEY_ESC || key == KEY_HOME) {
            break;
        }
    }
}
// Runs the menu loop until user chooses Exit
void runMainMenu(void) {
    while (1) {
        MenuItem selected = handleMenuInput();

        switch (selected) {
            case MENU_NEW:
                handleNewOption();
                break;

            case MENU_DISPLAY:
                handleDisplayOption();
                break;

            case MENU_EXIT:
                clearScreen();
                drawText(30, 10, "Goodbye!", GREEN);
                delaySeconds(1);
                clearScreen();
                return;
        }
    }
}
