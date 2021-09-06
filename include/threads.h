#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include <pthread.h>
#include "buffer.h"

void my_thread_1(file_t *db);
void my_thread_2(file_t *db);
void my_thread_3(file_t *db);
void my_thread_4(file_t *db);

#endif /* THREADS_H_INCLUDED */