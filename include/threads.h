#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

typedef struct _rwlock_t {
    sem_t lock_1;              /* trava binaria */
    sem_t lock_2;              /* trava binaria */
    sem_t wrt;                 /* permite 1 escritor */
    int readCount;             /* n de leitores */
    pthread_mutex_t mutex;
    pthread_cond_t cond_mutex;
} rwlock_t;

typedef struct  {
    file_t *ptr_db;
    rwlock_t *ptr_semaphore;
} texteditor_t;

pthread_t new_thread_0, new_thread_1, new_thread_2, new_thread_3, new_thread_4;

int state_condition;

void my_thread_0(texteditor_t *rw);
void my_thread_1(texteditor_t *rw);
void my_thread_2(texteditor_t *rw);
void my_thread_3(texteditor_t *rw);
void my_thread_4(texteditor_t *rw);

#endif /* THREADS_H_INCLUDED */