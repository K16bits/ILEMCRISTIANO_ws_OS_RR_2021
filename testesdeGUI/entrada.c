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

    FILE* demo;
    demo = fopen("demo_file.txt","w+");
    int size = 5;
    char palavra[5] = "abcd";

    initscr();
    cbreak();   //pega todo o teclado
    keypad(stdscr,TRUE);//inicial o teclado de arrow keys e num keys
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_RED); //Texto(Branco) | Fundo(RED)

    bkgd(COLOR_PAIR(1)); // Ativa as cores no texto e fundo

    move(0,0);  //inicial
    printw("%s",palavra);    
    // char letra[50];
    printw("-- Teste de fazer um editor de texto -- \n");
    move(1,1);  //inicial
    int ch = getch();
    x = 1; y = 2;
    while (1){
        printw("X: %d | Y: %d",x,y);
        switch(ch){
            case KEY_LEFT:
                if(x)
                    x=14;
                break;
            default:
                break;
        }
   }
}