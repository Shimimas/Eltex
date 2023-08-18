#include "functions.h"

int actual_posision;
int menu_posision[2];
int menu_counters[2];
WINDOW * win[2];
WINDOW **items[2];
struct dirent **namelist[2];
char paths[2][BUFFER_SIZE] = {".", "."};

int main(int argc, char ** argv)
{   
    init_curses();
    wattron(stdscr, COLOR_PAIR(2) | A_BOLD);
    main_window_fill();
    refresh();
    signal(SIGWINCH, sig_winch);
    create_windows();
    output_windows_fill(LEFT);
    output_windows_fill(RIGHT);
    actual_posision = LEFT;
    menu_posision[LEFT] = 0;
    menu_posision[RIGHT] = 0;
    draw_menu(2, LEFT, menu_posision[LEFT]);
    draw_menu((getmaxx(stdscr) / 2) + 1, RIGHT, menu_posision[RIGHT]);
    wrefresh(win[RIGHT]);
    wrefresh(win[LEFT]);
    int input;
    cbreak();
    while (input = wgetch(stdscr)) {
        interface(input);
    }
}