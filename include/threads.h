#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

pthread_t pid_1, pid_2, pid_3, pid_4;

void my_thread_1(file_t *db);
void my_thread_2(file_t *db);
void my_thread_3(file_t *db);
void my_thread_4(file_t *db);

#endif /* THREADS_H_INCLUDED */