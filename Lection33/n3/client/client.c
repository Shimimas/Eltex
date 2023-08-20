#include "client.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

void sig_winch(int signo) {
    struct winsize size;

    clear();
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    wbkgd(stdscr, COLOR_PAIR(0));
    refresh();
    set_window_size(INPUT_WINDOW);
}

void init_curses() {
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    start_color();
    keypad(stdscr, 1);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    wattron(stdscr, COLOR_PAIR(0) | A_BOLD);
    wbkgd(stdscr, COLOR_PAIR(0));
    refresh();
}

void set_window_size(int window_number) {
    int main_window_size_y;
    int main_window_size_x;

    main_window_size_y = getmaxy(stdscr);
    main_window_size_x = getmaxx(stdscr);
    switch (window_number) {
        case INPUT_WINDOW:
            wresize(windows[INPUT_WINDOW], main_window_size_y / 3, main_window_size_x / 3);
            mvwin(windows[INPUT_WINDOW], main_window_size_y / 3, main_window_size_x / 3);
            break;
        case INPUT_SECTION:
            break;
        default:
            break;
    }
    set_content(window_number);
    wrefresh(windows[window_number]);
}

void set_content(int window_number) {
    switch (window_number) {
        case INPUT_WINDOW:
            wbkgd(windows[INPUT_WINDOW], COLOR_PAIR(1));
            wmove(windows[INPUT_WINDOW], 1, 1);
            wprintw(windows[INPUT_WINDOW], "%s", "Enter your nickname:");
            break;
        case INPUT_SECTION:
            wbkgd(windows[INPUT_SECTION], COLOR_PAIR(0));
            break;
        default:
            break;
    }
}

void init_input_window() {
    int x;
    int y;
    int x_size;
    int y_size;
    
    x = getmaxx(stdscr) / 3;
    y = getmaxy(stdscr) / 3;
    x_size = getmaxx(stdscr) / 3;
    y_size = getmaxy(stdscr) / 3;

    windows[INPUT_WINDOW] = subwin(stdscr, getmaxy(stdscr) / 3, getmaxx(stdscr) / 3, getmaxy(stdscr) / 3, getmaxx(stdscr) / 3);
    set_content(INPUT_WINDOW);
    wrefresh(windows[INPUT_WINDOW]);
}

void init_input_section() {
    int x;
    int y;
    int x_size;
    int y_size;

    x = getmaxx(stdscr) / 3 + 1;
    y = (getmaxy(stdscr) / 3) * 2 - 2;
    x_size = getmaxx(windows[INPUT_WINDOW]) - 2;
    y_size = 1;

    windows[INPUT_SECTION] = subwin(windows[INPUT_WINDOW], y_size, x_size, y, x);
    set_content(INPUT_SECTION);
    wrefresh(windows[INPUT_SECTION]);
}

void init_start_screen() {
    init_curses();
    signal(SIGWINCH, sig_winch);
    init_input_window();
    init_input_section();
    
    getch();
    delwin(windows[INPUT_SECTION]);
    delwin(windows[INPUT_WINDOW]);
    delwin(stdscr);
    endwin();
}