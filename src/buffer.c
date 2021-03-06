#include "../include/buffer.h"
#include "../include/editor.h"

void open_file(file_t *p, char *file_path) {

    p->filename = file_path;
    p->text = (char *)nmalloc(size * sizeof(char));

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

    int fd_to_write = creat(p->filename, S_IRUSR | S_IWUSR);
    
    write(fd_to_write, p->text, strlen(p->text));

    close(fd_to_write);
}

void *nmalloc(size_t howmuch) {

    void *r = malloc(howmuch);

    if (howmuch == 0)
        die("Alocando zero bytes. Por favor, relate um bug.");

    if (r == NULL)
        die("Editor de texto está sem memória!");

    return r;
}