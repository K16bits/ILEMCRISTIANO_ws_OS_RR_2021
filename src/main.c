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

    /* Configuração para Threads */

    rwlock_t semaforo;
    sem_init(&semaforo.lock_1, 0, 1);
    sem_init(&semaforo.lock_2, 0, 1);
    sem_init(&semaforo.wrt, 0, 1);
    semaforo.readCount = 0;
    pthread_mutex_init(&semaforo.mutex, NULL);
    pthread_cond_init(&semaforo.cond_mutex, NULL);

    texteditor_t editorTexto;
    editorTexto.ptr_db = &file;
    editorTexto.ptr_semaphore = &semaforo;

    state_condition = 1;

    pthread_create(&new_thread_0, NULL, (void *)my_thread_0, (void *)&editorTexto);
    pthread_create(&new_thread_1, NULL, (void *)my_thread_1, (void *)&editorTexto);
    pthread_create(&new_thread_2, NULL, (void *)my_thread_2, (void *)&editorTexto);
    pthread_create(&new_thread_3, NULL, (void *)my_thread_3, (void *)&editorTexto);
    pthread_create(&new_thread_4, NULL, (void *)my_thread_4, (void *)&editorTexto);

    pthread_join(new_thread_0, NULL);
    pthread_join(new_thread_1, NULL);
    pthread_join(new_thread_2, NULL);
    pthread_join(new_thread_3, NULL);
    pthread_join(new_thread_4, NULL);

    refresh(); // Atualiza o curses

    endwin(); // Termina o modo curses

    return 0;
}