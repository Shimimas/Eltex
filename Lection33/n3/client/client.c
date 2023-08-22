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
    if (users.size == 0) {
        set_window_size(INPUT_WINDOW);
        set_window_size(INPUT_SECTION);
    } else {
        set_window_size(USERS_FIELD);
        users_content_refresh();
        set_window_size(MESSAGE_FIELD);
        set_window_size(WRITE_FIELD);
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
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    wattron(stdscr, COLOR_PAIR(0) | A_BOLD);
    wbkgd(stdscr, COLOR_PAIR(0));
    refresh();
}

void set_window_size(int window_number) {
    switch (window_number) {
        case INPUT_WINDOW:
            wresize(windows[INPUT_WINDOW], getmaxy(stdscr) / 3, getmaxx(stdscr) / 3);
            mvwin(windows[INPUT_WINDOW], getmaxy(stdscr) / 3, getmaxx(stdscr) / 3);
            break;
        case INPUT_SECTION:
            wresize(windows[INPUT_SECTION], 1, getmaxx(windows[INPUT_WINDOW]) - 2);
            mvwin(windows[INPUT_SECTION], (getmaxy(stdscr) / 3) * 2 - 2, getmaxx(stdscr) / 3 + 1);
            break;
        case USERS_FIELD:
            wresize(windows[USERS_FIELD], getmaxy(stdscr), getmaxx(stdscr) / 3);
            break;
        case MESSAGE_FIELD:
            wresize(windows[MESSAGE_FIELD], (getmaxy(stdscr) / 5) * 4, getmaxx(stdscr) - getmaxx(windows[USERS_FIELD]));
            mvwin(windows[MESSAGE_FIELD], 0, getmaxx(windows[USERS_FIELD]));
            break;
        case WRITE_FIELD:
            wresize(windows[WRITE_FIELD], getmaxy(stdscr) - getmaxy(windows[MESSAGE_FIELD]), getmaxx(stdscr) - getmaxx(windows[USERS_FIELD]));
            mvwin(windows[WRITE_FIELD], getmaxy(windows[MESSAGE_FIELD]), getmaxx(windows[USERS_FIELD]));
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
        case MESSAGE_FIELD:
            wclear(windows[MESSAGE_FIELD]);
            box(windows[MESSAGE_FIELD], ACS_VLINE, ACS_HLINE);
            wbkgd(windows[MESSAGE_FIELD], COLOR_PAIR(1));
            break;
        case WRITE_FIELD:
            wclear(windows[WRITE_FIELD]);
            box(windows[WRITE_FIELD], ACS_VLINE, ACS_HLINE);
            wbkgd(windows[WRITE_FIELD], COLOR_PAIR(2));
            break;
        default:
            break;
    }
}

void init_input_window() {
    windows[INPUT_WINDOW] = subwin(stdscr, getmaxy(stdscr) / 3, getmaxx(stdscr) / 3, getmaxy(stdscr) / 3, getmaxx(stdscr) / 3);
    set_content(INPUT_WINDOW);
    wrefresh(windows[INPUT_WINDOW]);
}

void init_input_section() {
    windows[INPUT_SECTION] = subwin(windows[INPUT_WINDOW], 1, getmaxx(windows[INPUT_WINDOW]) - 2, (getmaxy(stdscr) / 3) * 2 - 2, getmaxx(stdscr) / 3 + 1);
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
    init_message();
    init_write_field();
}

void init_write_field() {
    windows[WRITE_FIELD] = newwin(getmaxy(stdscr) - getmaxy(windows[MESSAGE_FIELD]),
        getmaxx(stdscr) - getmaxx(windows[USERS_FIELD]), getmaxy(windows[MESSAGE_FIELD]),
        getmaxx(windows[USERS_FIELD]));
    set_content(WRITE_FIELD);
    wrefresh(windows[WRITE_FIELD]);
}

void init_message() {
    windows[MESSAGE_FIELD] = newwin((getmaxy(stdscr) / 5) * 4, getmaxx(stdscr) - getmaxx(windows[USERS_FIELD]), 0, getmaxx(windows[USERS_FIELD]));
    set_content(MESSAGE_FIELD);
    wrefresh(windows[MESSAGE_FIELD]);
}

void init_users_field() {
    windows[USERS_FIELD] = newwin(getmaxy(stdscr), getmaxx(stdscr) / 3, 0, 0);
    set_content(USERS_FIELD);
    wrefresh(windows[USERS_FIELD]);
}

void add_user(char message[BUFFER_SIZE]) {
    struct user_information u_inf;

    u_inf.win = subwin(windows[USERS_FIELD], 1, getmaxx(windows[USERS_FIELD]) - 2, users.size + 1, 1);
    strcpy(u_inf.message, message);
    push_back(&users, (void *) &u_inf, sizeof(u_inf));
}

void log_print(int x, int y, int x_size, int y_size) {
    FILE *mf;

    mf = fopen("log.txt", "a");
    fprintf(mf, "x = %d y = %d x_size = %d y_size = %d\n", x, y, x_size, y_size);
    fclose(mf);
}

void users_content_refresh() {
    struct list_element * head;
    struct user_information * u_inf;
    struct list_element * my_nickname = NULL;

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

void * write_pthread(void * data) {

}

void * read_pthread(void * data) {
    struct pthread_info * p_info;
    struct msgbuf message;

    p_info = (struct pthread_info *) data;
    while(1) {
        msgrcv(p_info->md, (void *) &message, sizeof(struct data), p_info->pid, 0);
        switch (message.data.type) {
            case REGISTATION:
                break;
            case DELETE:
                break;
            case ADD_NEW_USER:
                add_user(message.data.mtext);
                users_content_refresh();
                break;
            default:
                break;
        } 
    }
}