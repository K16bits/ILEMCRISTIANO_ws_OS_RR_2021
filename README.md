# ILEMCRISTIANO_ws_OS_RR_2021
Repositório para o seminário da disciplina Sistemas Operacionais – DCC 403, ofertada pelo departamento de Ciência da Computação - UFRR.

O projeto consiste em um editor de texto simples em multithreads feito em C usando `ncurses`, com o sistema de backup em paralelo.

## Dependências
+ `C99`
+ `ncurses`
+ `pthread`
+ `semaphore`
+ `make`

## Instalando
Para compilar e colocar o programa em execução, basta clonar o repositório fazendo:
```bash
git clone https://github.com/K16bits/ILEMCRISTIANO_ws_OS_RR_2021.git && cd ILEMCRISTIANO_ws_OS_RR_2021
```

E então, execute o comando `make` que irá compilar todo o projeto.

Então, basta executar com `./text_editor [<file>]`.
