#include "client.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

void sig_winch(int signo) {
    struct winsize size;
    log_print("FIRST_RESIZE\n");
    clear();
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    wbkgd(stdscr, COLOR_PAIR(0));
    refresh();
    if (users.size == 0) {
        set_window_size(INPUT_WINDOW);
        set_window_size(INPUT_SECTION);
    } else {
        set_window_size(USERS_FIELD);
        users_content_refresh();
    }
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
            wresize(windows[INPUT_SECTION], 1, getmaxx(windows[INPUT_WINDOW]) - 2);
            mvwin(windows[INPUT_SECTION], (getmaxy(stdscr) / 3) * 2 - 2, getmaxx(stdscr) / 3 + 1);
            break;
        case USERS_FIELD:
            wresize(windows[INPUT_SECTION], getmaxy(stdscr), getmaxx(stdscr) / 3);
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
            wclear(windows[INPUT_WINDOW]);
            wbkgd(windows[INPUT_WINDOW], COLOR_PAIR(1));
            wmove(windows[INPUT_WINDOW], 1, 1);
            wprintw(windows[INPUT_WINDOW], "%s", "Enter your nickname:");
            break;
        case INPUT_SECTION:
            wclear(windows[INPUT_SECTION]);
            wbkgd(windows[INPUT_SECTION], COLOR_PAIR(0));
            wmove(windows[INPUT_SECTION], 0, 0);
            wprintw(windows[INPUT_SECTION], "%s", nickname);
            break;
        case USERS_FIELD:
            wclear(windows[USERS_FIELD]);
            box(windows[USERS_FIELD], ACS_VLINE,ACS_HLINE);
            wbkgd(windows[USERS_FIELD], COLOR_PAIR(1));
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

void input_nickname() {
    int input;
    int i;
    int x; 
    int y;

    echo();
    curs_set(1);
    keypad(windows[INPUT_SECTION], 1);
    wmove(windows[INPUT_SECTION], 0, 0);
    i = 0;
    do {
        input = wgetch(windows[INPUT_SECTION]);
        switch (input) {
            case KEY_BACKSPACE:
                if (i > 0) {
                    getyx(windows[INPUT_SECTION], y, x);
                    mvwaddch(windows[INPUT_SECTION], y, x, ' ');
                    wrefresh(windows[INPUT_SECTION]);
                    i--;
                    nickname[i] = '\0';
                    wmove(windows[INPUT_SECTION], y, x);
                }
                break;
            case '\n':
                break;
            default:
                nickname[i++] = input;
                break;
        }
    } while(input != '\n');
    nickname[i] = '\0';
    noecho();
    curs_set(0);
}

void init_start_screen() {
    init_curses();
    signal(SIGWINCH, sig_winch);
    init_input_window();
    init_input_section();
    input_nickname();
    delwin(windows[INPUT_SECTION]);
    delwin(windows[INPUT_WINDOW]);
    clear();
    refresh();
}

void init_main_screen() {
    init_users_field();
}

void init_users_field() {
    int x;
    int y;
    int x_size;
    int y_size;

    x = 0;
    y = 0;
    x_size = getmaxx(stdscr) / 3;
    y_size = getmaxy(stdscr);

    windows[USERS_FIELD] = subwin(stdscr, y_size, x_size, y, x);
    set_content(USERS_FIELD);
    wrefresh(windows[USERS_FIELD]);
}

void add_user(char message[BUFFER_SIZE]) {
    struct user_information u_inf;

    u_inf.win = subwin(windows[USERS_FIELD], 1, getmaxx(windows[USERS_FIELD]) - 2, users.size + 1, 1);
    strcpy(u_inf.message, message);
    push_back(&users, (void *) &u_inf, sizeof(u_inf));
}

void log_print(char message[BUFFER_SIZE]) {
    FILE *mf;

    mf = fopen("log.txt", "a");
    fprintf(mf, "%s\n", message);
    fclose(mf);
}

void users_content_refresh() {
    struct list_element * head;
    struct user_information * u_inf;
    struct list_element * my_nickname = NULL;

    int counter = 0;

    head = users.head;
    while (head != NULL) {
        u_inf = (struct user_information *) head->data;
        wresize(u_inf->win, 1, getmaxx(windows[USERS_FIELD]) - 2);
        wclear(u_inf->win);
        wprintw(u_inf->win, "%s", u_inf->message);
        wrefresh(u_inf->win);
        if (strcmp(nickname, u_inf->message) == 0) {
            my_nickname = head;
        }
        head = head->next;
        counter++;
    }
    if (my_nickname != NULL) {
        u_inf = (struct user_information *) my_nickname->data;
        wclear(u_inf->win);
        wprintw(u_inf->win, "%s", u_inf->message);
        wbkgd(u_inf->win, COLOR_PAIR(0));
        wrefresh(u_inf->win);
    }
}

void sub_windows_clear() {
    struct list_element * head;
    struct user_information * u_inf;

    head = users.head;
    while (head != NULL) {
        u_inf = (struct user_information *) head->data;
        delwin(u_inf->win);
        head = head->next;
    }
}