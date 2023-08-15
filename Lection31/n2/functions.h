#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 255

void sig_winch(int signo);
void interface(int input, char buffer[BUFFER_SIZE]);
void open_file(const char buffer[BUFFER_SIZE]);
void mv_down(WINDOW * win);
void mv_up(WINDOW * win);
void mv_left(WINDOW * win);
void mv_right(WINDOW * win);
void backspace(WINDOW * win);
void get_filename(WINDOW * win, char buffer[BUFFER_SIZE], int max_len);
void write_to_file(char buffer[BUFFER_SIZE]);

#endif // __FUNCTIONS_H_