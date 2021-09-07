#include "../include/threads.h"

void my_thread_1(file_t *db) {

    file_t my_file;
    open_file(&my_file, "my_thread_01.txt");
    
    int i;
    for (i = 0; i < db->file_size; i++)
        if ((db->text[i] >= 48 && db->text[i] <= 57) || db->text[i] == '\n')
            my_file.text[i] = db->text[i];
        else
            my_file.text[i] = ' ';

    my_file.text[i] = '\0';

    save_file(&my_file);
}

void my_thread_2(file_t *db) {

    file_t my_file;
    open_file(&my_file, "my_thread_02.txt");
    
    int i;
    for (i = 0; i < db->file_size; i++)
        if ((db->text[i] >= 65 && db->text[i] <= 90) || (db->text[i] >= 97 && db->text[i] <= 122) || db->text[i] == '\n')
            my_file.text[i] = db->text[i];
        else
            my_file.text[i] = ' ';

    my_file.text[i] = '\0';

    save_file(&my_file);
}

void my_thread_3(file_t *db) {

    file_t my_file;
    open_file(&my_file, "my_thread_03.txt");
    
    int i;
    for (i = 0; i < db->file_size; i++)
        if (( db->text[i] >= 33 && db->text[i] <= 47) 
                ||(db->text[i] >= 58 && db->text[i] <= 64)
                ||(db->text[i] >= 91 && db->text[i] <= 96) 
                ||(db->text[i] >= 123 && db->text[i] <= 126) 
                || db->text[i] == '\n')
            my_file.text[i] = db->text[i];
        else
            my_file.text[i] = ' ';

    my_file.text[i] = '\0';

    save_file(&my_file);
}

void my_thread_4(file_t *db) {

    file_t my_file;
    open_file(&my_file, "my_thread_04.txt");
    
    int count_lines = 1;
    for (int i = 0; i < db->file_size; i++)
        if (db->text[i] == '\n')
            count_lines++;
        
    sprintf(my_file.text, "%d", count_lines); // converter um valor inteiro para uma string

    save_file(&my_file);
}