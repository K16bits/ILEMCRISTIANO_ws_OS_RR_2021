#include <stdio.h>
#include <stdlib.h> 
#include <curses.h> 
#include <string.h>

// gcc  entrada.c -o entrada  -lncurses

void mapeamento(int* eixoX,int* eixoY){
    int auxY,auxX;
    getyx(stdscr,auxY,auxX);
    move(0,0);
    printw("TELA (X: %d | Y: %d)|",*eixoX,*eixoY);
    printw("antiga(Y: %d  X: %d)",auxX,auxY);
    move(auxY,auxX);
}

int printVetor(int* eixoX,int* eixoY,char palavra[]){
    int auxY,auxX;
    getyx(stdscr,auxY,auxX);
    mvprintw(auxY,0,"%s",palavra);
    clrtoeol();
    move(auxY,auxX);
    refresh();
}

void removeChar(char* palavra,int indice){
    int tam = strlen(palavra);
    for(int i = indice; i < tam;i++)
        palavra[i] = palavra[i+1];
}

void moverEsquerda(int* eixoX,int* eixoY){
    if(*eixoX > 0){
    move(*eixoY,--(*eixoX));
    } 
}
void moverDireita(int* eixoX,int* eixoY){
    move(*eixoY,++(*eixoX));
}

int main(){

    FILE* demo;
    demo = fopen("demo_file.txt","w+");

    initscr();
    noecho(); // Controle de entrada 
    cbreak();   //pega todo o teclado
    keypad(stdscr,TRUE);//inicial o teclado de arrow keys e num keys
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_RED); //Texto(Branco) | Fundo(RED)

    bkgd(COLOR_PAIR(1)); // Ativa as cores no texto e fundo

    move(1,0);
    int eixoX = 0,eixoY = 1;
    int ch;
    char* palavra = malloc(10*sizeof(char));
    palavra[0] = 'a';
    palavra[1] = 'b';
    palavra[2] = 'c';
    int pos = strlen(palavra);
    eixoX = pos;
    move(eixoY,eixoX);

    while (1){
        mapeamento(&eixoX,&eixoY);
        printVetor(&eixoX,&eixoY,palavra);
        ch = getch();
        switch(ch){
            case KEY_LEFT:
                moverEsquerda(&eixoX,&eixoY);
                break;
            case KEY_RIGHT:
                moverDireita(&eixoX,&eixoY);
                break;
            case KEY_BACKSPACE:

                    removeChar(palavra,eixoX-1);
                    moverEsquerda(&eixoX,&eixoY);
                    pos--;
                
                break;
            default:            
                if(isprint(ch)){
                    if(pos < 10){
                        palavra[pos]=ch;
                        pos+=1;
                        moverDireita(&eixoX,&eixoY);
                    }
                };
                break;
        }
   }
}
