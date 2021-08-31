#include <stdio.h>
#include <stdlib.h> 
#include <curses.h> 

// gcc  entrada.c -o entrada  -lncurses

void print_loc(int x, int y){
	#ifdef DEBUG
	int oldx, oldy;
	getyx(stdscr, oldy, oldx);
	mvprintw(0, COLS - 20, "x: %d y: %d o: %d", x, y, y_offset);
	move(oldy, oldx);
	#endif
}

void move_left(int *x, int *y){
	if(*x - 1 > 0) move(*y, --(*x)); // move é da bibliote curses
}


int main(){
    int x,y;
    initscr();
    cbreak();   //pega todo o teclado
    keypad(stdscr,TRUE);//inicial o teclado de arrow keys e num keys
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_RED); //Texto(Branco) | Fundo(RED)

    bkgd(COLOR_PAIR(1)); // Ativa as cores no texto e fundo

    move(0,0);  //inicial
    char letra[50];
    printw("-- Teste de fazer um editor de texto -- \n");

    int ch = getch();
    char palavra[5] = {'a','b','c'};
    while (1){
        printw(palavra);
        switch(ch){
            case KEY_LEFT:
                move_left(&x,&y);
                break;
            default:
                break;
        }
    }
}
