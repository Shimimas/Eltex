#include "functions.h"

int main(int argc, char ** argv)
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1) | A_BOLD);
    signal(SIGWINCH, sig_winch);
    keypad(stdscr, 1);
    printw("Press F1 button to create or open file\tPress F2 button to save changes\tPress F3 button to exit\n");
    refresh();
    int input;
    cbreak();
    char buffer[BUFFER_SIZE];
    while (input = wgetch(stdscr)) {
        interface(input, buffer);
    }
}