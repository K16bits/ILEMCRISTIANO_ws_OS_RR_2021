#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

#include <ncurses.h>
#include "buffer.h"

#define _KEY_ENTER 0xA
#define _KEY_SAVE 0xF
#define _KEY_EXIT 0x18

int maxchars;
int maxrows, maxcols;
int startrow, startcol;
int displayrows;
bool ins;

void boot_screen();
void menu_window();
int texteditor(file_t *p);
char *left(char *string, const int length);
void die(const char *msg);

#endif /* EDITOR_H_INCLUDED */