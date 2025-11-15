#include "input.h"
#include "platform.h"
#include <stdio.h>

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>

static struct termios oldTermios;
static struct termios newTermios;
#endif

void initInput(void) {
#ifndef _WIN32
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldTermios);

    // Copy to new settings
    newTermios = oldTermios;

    // Disable canonical mode and echo
    newTermios.c_lflag &= ~(ICANON | ECHO);

    // Set new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
#endif
}

void restoreInput(void) {
#ifndef _WIN32
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
#endif
}

int getKeyPress(void) {
#ifdef _WIN32
    #include <conio.h>
    int ch = _getch();

    // Handle special keys (arrow keys, etc.)
    if (ch == 0 || ch == 224) {
        ch = _getch();
        return ch;
    }

    return ch;
#else
    int ch = getchar();

    // Handle escape sequences for arrow keys
    if (ch == 27) {
        int next = getchar();
        if (next == '[') {
            int arrow = getchar();
            switch (arrow) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
                case 'H': return KEY_HOME;
            }
        } else {
            // Just ESC key
            return KEY_ESC;
        }
    }

    // Enter key
    if (ch == 10) return KEY_ENTER;

    return ch;
#endif
}
