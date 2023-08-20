#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <unistd.h>
#include <curses.h>
#include <signal.h>
#include <sys/ioctl.h>

#include "../general/list.h"
#include "../general/msgq_data.h"

#define WINDOWS_AMOUNT 2
#define INPUT_WINDOW 0
#define INPUT_SECTION 1

extern WINDOW * windows[WINDOWS_AMOUNT];

void init_curses();
void init_start_screen();
void sig_winch(int signo);
void set_window_size(int window_number);
void set_content(int window_number);

#endif // __CLIENT_H_