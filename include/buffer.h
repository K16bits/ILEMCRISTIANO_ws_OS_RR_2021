#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define size 600000 /* tamanho total do texto que pode ser aberto em cerca de 0.6 MB */

typedef struct
{
    char *filename;              /* Nome do arquivo. */
    char *text;                  /* Ponteiro do texto de leitura */
    unsigned int numlines;       /* Numero de linha do texto */
    unsigned long int file_size; /* Tamanho do arquivo, em bytes. */
} file_t;

void open_file(file_t *p, char *file_path);
void save_file(file_t *p);
void *nmalloc(size_t howmuch);

#endif /* BUFFER_H_INCLUDED */