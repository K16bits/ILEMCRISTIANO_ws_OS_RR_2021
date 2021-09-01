#include <stdio.h>
#include <stdlib.h> 
#include <curses.h> 

// gcc  entrada.c -o entrada  -lncurses

void mapeamento(int* eixoX,int* eixoY){
    move(0,0);
    printw("X: %d | Y: %d",*eixoX,*eixoY);
}

void moverEsquerda(int* eixoX,int* eixoY){
    //if(*eixoX-1 > 0) 
    move(*eixoY,--(*eixoX));
}
void moverDireita(int* eixoX,int* eixoY){
    move(*eixoY,++(*eixoX));
}

void atualizaStatus(char* info){
    int oldy,oldx;
	clrtoeol();
    //getyx(stdscr,oldy,oldx);
    move(5,5);
    printw(info);
}


int main(){
    int eixoX = 0,eixoY = 0; 

    FILE* demo;
    demo = fopen("demo_file.txt","w+");
    int size = 5;
    // char palavra[5] = "abcd";

    initscr();
    cbreak();   //pega todo o teclado
    keypad(stdscr,TRUE);//inicial o teclado de arrow keys e num keys
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_RED); //Texto(Branco) | Fundo(RED)

    bkgd(COLOR_PAIR(1)); // Ativa as cores no texto e fundo

    move(1,0);  //inicial
    //printw("%s",palavra);    
    printw("--um editor de texto -- \n");
    int ch;
    while (1){
        mapeamento(&eixoX,&eixoY);
        ch = getch();
        switch(ch){
            case KEY_LEFT:
                moverEsquerda(&eixoX,&eixoY);
                atualizaStatus("esquerada");
                break;
            case KEY_RIGHT:
                moverDireita(&eixoX,&eixoY);
                atualizaStatus("direita");
                break;
            default:
                break;
        }
   }
}