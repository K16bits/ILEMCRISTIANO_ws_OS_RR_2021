#include "../include/threads.h"
#include "../include/editor.h"

void my_thread_0(texteditor_t *rw) {

    state_condition = texteditor(rw);
}

void my_thread_1(texteditor_t *rw) {

    while (state_condition) {
        sem_wait(&rw->ptr_semaphore->lock_2);
        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount++;
        if (rw->ptr_semaphore->readCount == 1)
            sem_wait(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        sem_post(&rw->ptr_semaphore->lock_2);

        /* Seção Crítica */

        file_t my_file;
        open_file(&my_file, "my_thread_1.txt");

        int i;
        for (i = 0; i < rw->ptr_db->file_size; i++)
            if ((rw->ptr_db->text[i] >= 48 && rw->ptr_db->text[i] <= 57) || rw->ptr_db->text[i] == '\n')
                my_file.text[i] = rw->ptr_db->text[i];
            else
                my_file.text[i] = ' ';

        my_file.text[i] = '\0';

        save_file(&my_file);

        /* Seção Crítica */

        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount--;
        if (rw->ptr_semaphore->readCount == 0)
            sem_post(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        pthread_cond_signal(&rw->ptr_semaphore->cond_mutex);
    }
}

void my_thread_2(texteditor_t *rw) {

    while (state_condition) {
        sem_wait(&rw->ptr_semaphore->lock_2);
        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount++;
        if (rw->ptr_semaphore->readCount == 1)
            sem_wait(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        sem_post(&rw->ptr_semaphore->lock_2);

        /* Seção Crítica */

        file_t my_file;
        open_file(&my_file, "my_thread_2.txt");

        int i;
        for (i = 0; i < rw->ptr_db->file_size; i++)
            if ((rw->ptr_db->text[i] >= 65 && rw->ptr_db->text[i] <= 90) || (rw->ptr_db->text[i] >= 97 && rw->ptr_db->text[i] <= 122) || rw->ptr_db->text[i] == '\n')
                my_file.text[i] = rw->ptr_db->text[i];
            else
                my_file.text[i] = ' ';

        my_file.text[i] = '\0';

        save_file(&my_file);

        /* Seção Crítica */

        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount--;
        if (rw->ptr_semaphore->readCount == 0)
            sem_post(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        pthread_cond_signal(&rw->ptr_semaphore->cond_mutex);
    }
}

void my_thread_3(texteditor_t *rw) {

    while (state_condition) {
        sem_wait(&rw->ptr_semaphore->lock_2);
        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount++;
        if (rw->ptr_semaphore->readCount == 1)
            sem_wait(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        sem_post(&rw->ptr_semaphore->lock_2);

        /* Seção Crítica */

        file_t my_file;
        open_file(&my_file, "my_thread_3.txt");

        int i;
        for (i = 0; i < rw->ptr_db->file_size; i++)
            if ((rw->ptr_db->text[i] >= 33 && rw->ptr_db->text[i] <= 47) || (rw->ptr_db->text[i] >= 58 && rw->ptr_db->text[i] <= 64) || (rw->ptr_db->text[i] >= 91 && rw->ptr_db->text[i] <= 96) || (rw->ptr_db->text[i] >= 123 && rw->ptr_db->text[i] <= 126) || rw->ptr_db->text[i] == '\n')
                my_file.text[i] = rw->ptr_db->text[i];
            else
                my_file.text[i] = ' ';

        my_file.text[i] = '\0';

        save_file(&my_file);

        /* Seção Crítica */

        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount--;
        if (rw->ptr_semaphore->readCount == 0)
            sem_post(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        pthread_cond_signal(&rw->ptr_semaphore->cond_mutex);
    }
}

void my_thread_4(texteditor_t *rw) {

    while (state_condition) {
        sem_wait(&rw->ptr_semaphore->lock_2);
        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount++;
        if (rw->ptr_semaphore->readCount == 1)
            sem_wait(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        sem_post(&rw->ptr_semaphore->lock_2);

        /* Seção Crítica */

        file_t my_file;
        open_file(&my_file, "my_thread_4.txt");

        int count_lines = 1;
        for (int i = 0; i < rw->ptr_db->file_size; i++)
            if (rw->ptr_db->text[i] == '\n')
                count_lines++;

        sprintf(my_file.text, "%d", count_lines); // converter um valor inteiro para uma string

        save_file(&my_file);

        /* Seção Crítica */

        sem_wait(&rw->ptr_semaphore->lock_1);
        rw->ptr_semaphore->readCount--;
        if (rw->ptr_semaphore->readCount == 0)
            sem_post(&rw->ptr_semaphore->wrt);
        sem_post(&rw->ptr_semaphore->lock_1);
        pthread_cond_signal(&rw->ptr_semaphore->cond_mutex);
    }
}