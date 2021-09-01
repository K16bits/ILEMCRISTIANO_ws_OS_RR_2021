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

    // printf("%s\n", file.text);
    // printf("%s is %ld bytes long.\n", file.filename, file.file_size);

    save_file(&file);

    return 0;
}