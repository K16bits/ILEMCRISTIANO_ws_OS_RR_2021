#include <stdio.h>
#include <stdlib.h> 
#include <curses.h> 
#include <string.h>

// gcc  entrada.c -o entrada  -lncurses

void mapeamento(int* eixoX,int* eixoY,char palavra[], int desl){
    int auxY,auxX;
    getyx(stdscr,auxY,auxX);
    move(0,0);
    printw("TELA (X: %d | Y: %d)|",*eixoX,*eixoY);
    printw("antiga(Y: %d  X: %d)",auxX,auxY);  
    mvprintw(auxY,0,"%s",palavra);
    move(auxY,desl);
}

// void printMoveAtt(int* eixoX,int* eixoY){
//     int oldx, oldy;
//     getyx(stdscr, oldy, oldx);
//     mvprintw(0, 1, "x: %d y: %d o: %d", eixoX, eixoY, -1);
// 	move(5, 5);
// }

void moverEsquerda(int* eixoX,int* eixoY){
    //if(*eixoX-1 > 0) 
    move(*eixoY,--(*eixoX));
}
void moverDireita(int* eixoX,int* eixoY){
    move(*eixoY,++(*eixoX));
}

int main(){
    int eixoX = 0,eixoY = 0; 

    FILE* demo;
    demo = fopen("demo_file.txt","w+");


    initscr();
    noecho(); // Controle de entrada 
    cbreak();   //pega todo o teclado
    keypad(stdscr,TRUE);//inicial o teclado de arrow keys e num keys
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_RED); //Texto(Branco) | Fundo(RED)

    bkgd(COLOR_PAIR(1)); // Ativa as cores no texto e fundo
    move(1,1);
    int ch;
    char* palavra = malloc(10*sizeof(char));
    int pos = 0;
    int desl = 0;
    while (1){
        desl = strlen(palavra);
        mapeamento(&eixoX,&eixoY,palavra,desl);
        ch = getch();
        switch(ch){
            case KEY_LEFT:
                moverEsquerda(&eixoX,&eixoY);
                break;
            case KEY_RIGHT:
                moverDireita(&eixoX,&eixoY);
                break;
            default:            
                if(isprint(ch)){
                    palavra[pos]=ch;
                    pos+=1;
                };
                break;
        }
   }
}
