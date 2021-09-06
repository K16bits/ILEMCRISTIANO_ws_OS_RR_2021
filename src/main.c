#include <stdio.h>
#include <stdlib.h>

#include "../include/editor.h"

int main(int argc, char *argv[]) {

    file_t file;

    if (argc >= 2) {

        char *file_path = argv[1];

        open_file(&file, file_path);
    }
    else
        return 1;

    boot_screen();

    menu_window();
    
    texteditor(&file);

    refresh(); // Atualiza o curses

    endwin(); // Termina o modo curses

    return 0;
}