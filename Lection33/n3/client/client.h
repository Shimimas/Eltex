#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <unistd.h>
#include <curses.h>
#include <malloc.h>
#include <signal.h>
#include <sys/ioctl.h>

#include "../general/list.h"
#include "../general/msgq_data.h"

#define WINDOWS_AMOUNT 5
#define INPUT_WINDOW 0
#define INPUT_SECTION 1
#define USERS_FIELD 2
#define MESSAGE_FIELD 3
#define INPUT_FIELD 4

struct user_information {
    long pid;
    WINDOW * win;
    char message[BUFFER_SIZE];
};

extern WINDOW * windows[WINDOWS_AMOUNT];
extern char nickname[BUFFER_SIZE];
extern struct list users;

void init_curses();
void init_start_screen();
void sig_winch(int signo);
void set_window_size(int window_number);
void set_content(int window_number);
void input_nickname();
void init_users_field();
void init_main_screen();
void add_user(char message[BUFFER_SIZE]);
void users_content_refresh();
void sub_windows_clear();
void log_print(char message[BUFFER_SIZE]);
void init_message();

#endif // __CLIENT_H_