#include "../include/buffer.h"

void open_file(file_t *p, char *file_path) {

    p->filename = file_path;
    p->text = (char *)malloc(size * sizeof(char));

    int fd_to_read = open(file_path, O_RDONLY, S_IRUSR | S_IWUSR);
    if (fd_to_read != -1) {
        struct stat sb;

        if (fstat(fd_to_read, &sb) != -1)
            p->file_size = sb.st_size;

        ssize_t n = read(fd_to_read, p->text, size);
    }
    else {
        p->file_size = 0;
        p->numlines = 0;
    }

    close(fd_to_read);
}

void save_file(file_t *p) {

    int fd_to_write = open(p->filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    
    write(fd_to_write, p->text, strlen(p->text));

    close(fd_to_write);
}