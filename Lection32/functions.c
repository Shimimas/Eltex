#include "functions.h"

void sig_winch(int signo) {
    struct winsize size;
    clear();
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    main_window_fill();
    refresh();
    wresize(win[LEFT], size.ws_row - 2, size.ws_col / 2);
    wresize(win[RIGHT], size.ws_row - 2, size.ws_col / 2);
    mvwin(win[RIGHT], 1, size.ws_col / 2);
    wclear(win[LEFT]);
    wclear(win[RIGHT]);
    del_menu(LEFT);
    del_menu(RIGHT);
    output_windows_fill(LEFT);
    output_windows_fill(RIGHT);
    draw_menu(2, LEFT, 0);
    draw_menu((getmaxx(stdscr) / 2) + 1, RIGHT, 0);
    wrefresh(win[RIGHT]);
    wrefresh(win[LEFT]);
}

void del_menu(int idx) {
    for (int i = 0; i < menu_counters[idx]; i++) {
        delwin(items[idx][i]);
    }
    free(items[idx]);
}

void init_curses() {

    initscr();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, 1);
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    namelist[LEFT] = NULL;
    namelist[RIGHT] = NULL;
}

void main_window_fill() {
    wbkgd(stdscr, COLOR_PAIR(2));
    move(0, 1);
    addstr("My MC Editor");
    move(0, 18);
    addstr("Tab - to switch windows");
    move(0, 47);
    addstr("ESC- to exit");
    move(0, 65);
    addstr("ENTER - to select");
    mvchgat(0, 1, 13, A_UNDERLINE, 0, NULL); 
}

void output_windows_fill(int idx) {
    box(win[idx], ACS_VLINE,ACS_HLINE);
    wbkgd(win[idx], COLOR_PAIR(1));
}

void interface(int input) {
    switch (input) {
        case ENTER:
            select_dir();
            break;
        case ESCAPE:
            escape();
            break;
        case TAB:
            actual_posision = (actual_posision == 0) ? 1 : 0;
            break;
        case KEY_UP:
            mv_up();
            break;
        case KEY_DOWN:
            mv_down();
            break;
        default:
            break;
    }
}

void escape() {
    free_name_list(LEFT);
    free_name_list(RIGHT);
    del_menu(LEFT);
    del_menu(RIGHT);
    delwin(win[LEFT]);
    delwin(win[RIGHT]);
    endwin();
    exit(EXIT_SUCCESS);
}

void select_dir() {
    if (new_dir()) {
        wclear(win[actual_posision]);
        del_menu(actual_posision);
        output_windows_fill(actual_posision);
        if (actual_posision == LEFT ) {
            draw_menu(2, LEFT, 0);
        } else {
            draw_menu((getmaxx(stdscr) / 2) + 1, RIGHT, 0);
        }
        menu_posision[actual_posision] = 0;
        wrefresh(win[actual_posision]);
    }    
}

void mv_down() {
    if (menu_posision[actual_posision] != menu_counters[actual_posision] - 1) {
        wclear(win[actual_posision]);
        del_menu(actual_posision);
        output_windows_fill(actual_posision);
        if (actual_posision == LEFT ) {
            draw_menu(2, LEFT, ++menu_posision[actual_posision]);
        } else {
            draw_menu((getmaxx(stdscr) / 2) + 1, RIGHT, ++menu_posision[actual_posision]);
        }
        wrefresh(win[actual_posision]);
    }
}

void mv_up() {
    if (menu_posision[actual_posision] != 0) {
        wclear(win[actual_posision]);
        del_menu(actual_posision);
        output_windows_fill(actual_posision);
        if (actual_posision == LEFT ) {
            draw_menu(2, LEFT, --menu_posision[actual_posision]);
        } else {
            draw_menu((getmaxx(stdscr) / 2) + 1, RIGHT, --menu_posision[actual_posision]);
        }
        wrefresh(win[actual_posision]);
    }
}

void create_windows() {
    int max_x = getmaxx(stdscr);
    int max_y = getmaxy(stdscr);
    win[LEFT] = newwin(max_y - 2, max_x / 2, 1, 1);
    win[RIGHT] = newwin(max_y - 2, max_x / 2, 1, max_x / 2);
    wattron(win[LEFT], COLOR_PAIR(1) | A_BOLD);
    wattron(win[RIGHT], COLOR_PAIR(1) | A_BOLD);
    wrefresh(win[RIGHT]);
    wrefresh(win[LEFT]);
}

void free_name_list(int idx) {
    for (int i = 0; i < menu_counters[idx]; i++) {
        free(namelist[idx][i]);
    }
    free(namelist[idx]);
}

void draw_menu(int start_col, int idx, int menu_idx) {
    int i;
    int max_x_size;

    if (namelist != NULL) {
        free_name_list(idx);
    }
    max_x_size = getmaxx(win[LEFT]);
    menu_counters[idx] = scandir(paths[idx], &namelist[idx], NULL, alphasort);
    if (menu_counters[idx] < 0)
        perror("scandir");
    else {
        items[idx] = (WINDOW **)malloc(menu_counters[idx] * sizeof(WINDOW *)); // строчка, которая обрезает вывод в пределы окна, если нужно будет, сделаю scroll
        int size = (menu_counters[idx] <= getmaxy(win[idx]) - 2) ? menu_counters[idx] : getmaxy(win[idx]) - 2;
        for (i = 0; i < size; i++) {
            items[idx][i] = subwin(win[idx], 1, max_x_size - 2, i + 2, start_col);
        }
        for (i = 0; i < size; i++) {
            wprintw(items[idx][i], "%s", namelist[idx][i]->d_name);
        }
    }
    wbkgd(items[idx][menu_idx], COLOR_PAIR(2));
}

bool new_dir() {
    if (namelist[actual_posision][menu_posision[actual_posision]]->d_name == ".") {
        return false;
    } else if (namelist[actual_posision][menu_posision[actual_posision]]->d_name == "..") {
        delete_last_dir();
    } else {
        strcat(paths[actual_posision], "/");
        strcat(paths[actual_posision], namelist[actual_posision][menu_posision[actual_posision]]->d_name);
    }
    return true;
}

void delete_last_dir() {
    bool last_dir = false;
    int last_idx = -1;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (paths[actual_posision][i] == '/') {
            last_idx = i;
            if (i <= BUFFER_SIZE - 4 && paths[actual_posision][i + 1] == '.' 
            && paths[actual_posision][i + 2] == '.' && (paths[actual_posision][i + 3] == '/' || paths[actual_posision][i + 3] == '\0'))  {
                last_dir = false;
                i += 3;
            } else {
                last_dir = true;
            }
        }
    }
    if (last_dir) {
        paths[actual_posision][last_idx] = '\0';
    } else {
        strcat(paths[actual_posision], "/..");
    }
}