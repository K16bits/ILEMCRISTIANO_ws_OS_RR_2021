#include <stdio.h>
#include <stdlib.h>

#include "../include/editor.h"

int main(int argc, char *argv[]) {

    if (argc >= 2) {

        char *file_path = argv[1];
        printf("%s\n", file_path);
    }

    return 0;
}