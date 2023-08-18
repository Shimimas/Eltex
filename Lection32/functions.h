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
#include <dirent.h>
#include <string.h>

#define BUFFER_SIZE 255
#define LEFT 0
#define RIGHT 1
#define TAB 9
#define ENTER 10
#define ESCAPE 27

extern WINDOW * win[2];
extern WINDOW **items[2];
extern int menu_counters[2];
extern int menu_posision[2];
extern int actual_posision;
extern struct dirent **namelist[2];
extern char paths[2][BUFFER_SIZE];

void sig_winch(int signo);
void interface(int input);
void mv_down();
void mv_up();
void create_windows();
void main_window_fill();
void output_windows_fill(int idx);
void init_curses();
void draw_menu(int startcol, int idx, int menu_idx);
void del_menu(int idx);
void escape();
void free_name_list(int idx);
bool new_dir();
void select_dir();
void delete_last_dir();

#endif // __FUNCTIONS_H_