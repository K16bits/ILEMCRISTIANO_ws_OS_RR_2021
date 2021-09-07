#include "../include/editor.h"
#include "../include/buffer.h"
#include "../include/threads.h"

void boot_screen() {

    initscr(); // Inicia o modo curses
    noecho();  // entrada de caracter
    cbreak();  // Remove buffer e printa imediatamente na tela o caracter.

    keypad(stdscr, true); //  autoriza a entrada de KEYS.

    maxchars = size;
    maxcols = COLS;
    maxrows = maxchars / maxcols;

    startrow = 0;
    startcol = 0;

    displayrows = LINES - 3;

    ins = false;
}

void menu_window() {

    move(LINES - 2, 0);
    hline(ACS_CKBOARD, COLS);
    mvaddstr(LINES - 2, (COLS / 2) - 16, "[ Bem-vindo ao editor de texto ]");

    mvaddstr(LINES - 1, 0, "^X Sair");
    mvaddstr(LINES - 1, 25, "^O Gravar");
}

int texteditor(file_t *p) {

    int ky, position = 0, row, col, scrollstart = 0, x = 0, y = 0;
    char *where, **display;
    bool exitflag = false;

    /* modos de entrada do texto: inserir e substituir o texto */
    if (ins)
        mvaddstr(LINES - 1, COLS - 14, "Modo: Inserir");
    else
        mvaddstr(LINES - 1, COLS - 14, "Modo: Normal ");

    /* abaixo iremos alocar memória para o display, sendo que a matriz dinâmica foi representada com um vetor de ponteiros */
    display = nmalloc(maxrows * sizeof(char *));

    for (ky = 0; ky < maxrows; ky++)
        display[ky] = nmalloc((maxcols + 1) * sizeof(char));

    while (!exitflag){

        int counter;

        do {
            counter = 0;
            where = p->text;

            for (row = 0; row < maxrows; row++) {
                display[row][0] = 127;
                display[row][1] = '\0';
            }

            row = 0;
            while ((strlen(where) > maxcols || strchr(where, '\n') != NULL) && (display[maxrows - 1][0] == 127 || display[maxrows - 1][0] == '\n')) {
                
                strncpy(display[row], where, maxcols);
                display[row][maxcols] = '\0';

                if (strchr(display[row], '\n') != NULL)
                    left(display[row], strchr(display[row], '\n') - display[row]);
                else
                    left(display[row], strrchr(display[row], ' ') - display[row]);

                if (display[maxrows - 1][0] == 127 || display[maxrows - 1][0] == '\n') {
                    where += strlen(display[row]);
                    if (where[0] == '\n' || where[0] == ' ' || where[0] == '\0')
                        where++;
                    row++;
                }
            }

            if (row == maxrows - 1 && strlen(where) > maxcols) {
                if (ky == 127) /*KEY_BACKSPACE*/
                    position++;
                counter = 1;
            }
        } while (counter);

        strcpy(display[row], where); // agora copie o texto restante de onde exibir a linha

        ky = 0;
        if (strchr(display[maxrows - 1], '\n') != NULL)
            if (strchr(display[maxrows - 1], '\n')[1] != '\0')
                ky = 127; /*KEY_BACKSPACE*/

        col = position;
        row = 0;
        counter = 0;
        while (col > strlen(display[row])) { //continue percorrendo se a coluna for maior que o número de colunas na linha atual

            col -= strlen(display[row]);
            counter += strlen(display[row]);
            if (p->text[counter] == ' ' || p->text[counter] == '\n' || p->text[counter] == '\0') {
                col--;
                counter++;
            }
            row++;
        }

        if (col > maxcols - 1) {
            row++;
            col = 0;
        }

        if (!ky) {
            if (row < scrollstart)
                scrollstart--;
            if (row > scrollstart + displayrows - 1)
                scrollstart++;
            for (counter = 0; counter < displayrows; counter++) {
                mvhline(counter + startrow, startcol, ' ', maxcols);
                if (display[counter + scrollstart][0] != 127)
                    mvprintw(counter + startrow, startcol, "%s", display[counter + scrollstart]);
            }
            move(row + startrow - scrollstart, col + startcol); // mover para o final do texto

            ky = getch(); // o texto foi exibido agora aguarde até que o usuário pressione uma tecla
        }

        switch (ky) {

        case _KEY_EXIT: /* key ^X, para sair do editor de texto */
            exitflag = true;
            break;

        case _KEY_SAVE: /* key ^O, chave para salvar o arquivo */
            save_file(p);
            move(y, x);
            break;

        case KEY_HOME: /* mover para o início da linha atual */
            if (col) {
                position = 0;
                for (col = 0; col < row; col++) {
                    position += strlen(display[col]);
                    if ((strchr(display[row], '\n') != NULL) || (strchr(display[row], ' ') != NULL))
                        position++;
                }
            }
            break;

        case KEY_END: /* mover para o final da linha atual */
            if (col < strlen(display[row])) {
                position = -1;
                for (col = 0; col <= row; col++) {
                    position += strlen(display[col]);
                    if ((strchr(display[row], '\n') != NULL) || (strchr(display[row], ' ') != NULL))
                        position++;
                }
            }
            break;

        case KEY_PPAGE: /* mover para o início do texto */
            position = 0;
            scrollstart = 0;
            break;

        case KEY_NPAGE: /* mover para o final do texto */
            position = strlen(p->text);
            for (counter = 0; counter < maxrows; counter++)
                if (display[counter][0] == 127)
                    break;
            scrollstart = counter - displayrows;
            if (scrollstart < 0)
                scrollstart = 0;
            break;

        case KEY_LEFT:
            if (position)
                position--;
            break;

        case KEY_RIGHT:
            if (position < strlen(p->text) && (row != maxrows - 1 || col < maxcols - 1))
                position++;
            break;

        case KEY_UP:
            if (row) {
                if (col > strlen(display[row - 1]))
                    position = strlen(display[row - 1]);
                else
                    position = col;

                ky = 0;

                for (col = 0; col < row - 1; col++) {
                    position += strlen(display[col]);
                    ky += strlen(display[col]);
                    if ((strlen(display[col]) < maxcols) || (p->text[ky] == ' ' && strlen(display[col]) == maxcols)) {
                        position++;
                        ky++;
                    }
                }
            }
            break;

        case KEY_DOWN:
            if (row < maxrows - 1)
                if (display[row + 1][0] != 127) {
                    if (col < strlen(display[row + 1]))
                        position = col;
                    else
                        position = strlen(display[row + 1]);
                    ky = 0;
                    for (col = 0; col <= row; col++) {
                        position += strlen(display[col]);
                        ky += strlen(display[col]);
                        if ((strlen(display[col]) < maxcols) || (p->text[ky] == ' ' && strlen(display[col]) == maxcols)) {
                            position++;
                            ky++;
                        }
                    }
                }
            break;

        case KEY_IC: /* key insert */
            ins = !ins;
            if (ins)
                mvaddstr(LINES - 1, COLS - 8, "Inserir");
            else
                mvaddstr(LINES - 1, COLS - 8, "Normal ");
            break;

        case KEY_DC: /* key delete  */
            if (strlen(p->text))
                memmove(&p->text[position], &p->text[position + 1], maxchars - position);
            break;

        case KEY_BACKSPACE: /* key backspace */
            if (strlen(p->text) && position) {
                position--;
                memmove(&p->text[position], &p->text[position + 1], maxchars - position);
            }
            break;

        case _KEY_ENTER:
            if (display[maxrows - 1][0] == 127 || display[maxrows - 1][0] == '\n') {
                memmove(&p->text[position + 1], &p->text[position], maxchars - position);
                p->text[position] = '\n';
                position++;
            }
            break;

        default: //  no caso de quaisquer outros caracteres além do especificado acima
            if ((ky > 31 && ky < 127) && strlen(p->text) < maxchars - 1 && (row != maxrows - 1 || (strlen(display[maxrows - 1]) < maxcols || (ins && (row != maxrows - 1 && col < maxcols))))) {
                if (ins || p->text[position + 1] == '\n' || p->text[position] == '\n')
                    memmove(&p->text[position + 1], &p->text[position], maxchars - position);
                p->text[position] = ky;
                if (row != maxrows - 1 || col < maxcols - 1)
                    position++;
            }
        }
        
        p->file_size = strlen(p->text);
        
        pthread_create(&pid_1, NULL, (void *)my_thread_1, (void *)p);
        pthread_create(&pid_2, NULL, (void *)my_thread_2, (void *)p);
        pthread_create(&pid_3, NULL, (void *)my_thread_3, (void *)p);
        pthread_create(&pid_4, NULL, (void *)my_thread_4, (void *)p);

        pthread_join(pid_1, NULL);
        pthread_join(pid_2, NULL);
        pthread_join(pid_3, NULL);
        pthread_join(pid_4, NULL);
    }

    /* free display*/
    for (scrollstart = 0; scrollstart < maxrows; scrollstart++)
        free(display[scrollstart]);

    free(display);

    return 0;
}

char *left(char *string, const int length) {

    if (strlen(string) > length)
        string[length] = '\0';

    return string;
}

void die(const char *msg){
    
    endwin();
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}