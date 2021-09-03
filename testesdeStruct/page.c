#include <stdio.h>
#include <stdlib.h>

typedef struct PageLine{
    char* word; 
    int n_size;
    int max;
}pageline;

typedef struct{
    pageline** arrayLine; 
    int n_lines;
}page;

pageline* iniciaLinha(){
    pageline* p = malloc(sizeof(p));
    p->word = malloc(10*sizeof(char));;
    p->n_size = 0;
    p->max = 10;
    return p;
}

page* iniciarPagina(int tamanho){
    page* p = malloc(tamanho*sizeof(page));
    p->arrayLine = malloc(tamanho*sizeof(pageline));
    for(int i= 0; i < tamanho;i++){
        p->arrayLine[i] = iniciaLinha();
    }
    return p;
}

int main(){
    page* p = iniciarPagina(2);
    p->arrayLine[0]->word = "abc";
    printf("palavra %s\n",p->arrayLine[0]->word);
    return 0;
}