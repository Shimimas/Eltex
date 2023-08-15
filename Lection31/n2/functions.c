#include "functions.h"

void sig_winch(int signo) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}

int len(int number) {
    int linelen = COLS - 1;
    while (linelen >= 0 && mvinch (number, linelen) == ' ') {
        linelen--;
    }
    return linelen + 1;
}

void write_to_file(char buffer[BUFFER_SIZE]) {
    int n, l, i, idx = 0;
    int fd = open(buffer, O_WRONLY);
    char output_buffer[LINES * COLS + 1];
    for (l = 1; l < LINES - 1; l++) {
        n = len(l);
        for (i = 0; i < n; i++) {
            output_buffer[idx++] = mvinch(l, i);
        }
        output_buffer[idx++] = '\n';
    }
    output_buffer[idx] = '\0';
    write(fd, output_buffer, idx);
    close(fd);
}

void interface(int input, char buffer[BUFFER_SIZE]) {
    switch (input) {
        case KEY_F(1):
            printw("Enter the filename\n");
            get_filename(stdscr, buffer, BUFFER_SIZE);
            open_file(buffer);
            break;
        case KEY_F(2):
            write_to_file(buffer);
            break;
        case KEY_F(3):
            endwin();
            exit(EXIT_SUCCESS);
            break;
        case KEY_UP:
            mv_up(stdscr);
            break;
        case KEY_DOWN:
            mv_down(stdscr);
            break;
        case KEY_LEFT:
            mv_left(stdscr);
            break;
        case KEY_RIGHT:
            mv_right(stdscr);
            break;
        case KEY_BACKSPACE:
            backspace(stdscr);
            break;
        default:
            break;
    }
}

void backspace(WINDOW * win) {
    int x, y;
    getyx(win, y, x);
    mvwaddch(win, y, x, ' ');
    wrefresh(win);
    if (x >= 0) {
        wmove(win, y, x);
    }
}

void mv_down(WINDOW * win) {
    int x, y;
    getyx(win, y, x);
    wmove(win, y + 1, x);
}

void mv_up(WINDOW * win) {
    int x, y;
    getyx(win, y, x);
    wmove(win, y - 1, x);
}

void mv_left(WINDOW * win) {
    int x, y;
    getyx(win, y, x);
    wmove(win, y, x - 1);
}

void mv_right(WINDOW * win) {
    int x, y;
    getyx(win, y, x);
    wmove(win, y, x + 1);
}

void get_filename(WINDOW * win, char buffer[BUFFER_SIZE], int max_len) {
    int i = 0;
    int ch;
    while (((ch = wgetch(win)) != 10) && (i < max_len-1)) {
        if (ch == KEY_BACKSPACE) {
            int x, y;
            if (i == 0) continue;
            getyx(win, y, x);
            mvwaddch(win, y, x, ' ');
            wrefresh(win);
            if (x >= 0) {
                wmove(win, y, x);
                i--;
            }
            continue;
        }
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}


void open_file(const char buffer[BUFFER_SIZE]) {
    char * file_buffer;
    off_t size;
    struct stat st;
    int fd;

    fd = open(buffer, O_RDONLY | O_CREAT, 0700);
    stat(buffer, &st);
    size = st.st_size;
    file_buffer = malloc(size);
    read(fd, file_buffer, size);
    move(1, 0);
    printw("%s", file_buffer);
    free(file_buffer);
}