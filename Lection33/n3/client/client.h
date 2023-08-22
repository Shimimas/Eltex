#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <unistd.h>
#include <curses.h>
#include <malloc.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <pthread.h>

#include "../general/list.h"
#include "../general/msgq_data.h"

#define WINDOWS_AMOUNT 5
#define INPUT_WINDOW 0
#define INPUT_SECTION 1
#define USERS_FIELD 2
#define MESSAGE_FIELD 3
#define WRITE_FIELD 4
#define WRITE 0
#define READ 1

struct user_information {
    long pid;
    WINDOW * win;
    char message[BUFFER_SIZE];
};

struct pthread_info {
    int md;
    pid_t pid;
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
void log_print(int x, int y, int x_size, int y_size);
void init_message();
void * read_pthread(void * data);
void * write_pthread(void * data);
void init_write_field();

#endif // __CLIENT_H_