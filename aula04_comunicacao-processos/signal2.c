/*
 Programa: Uso de sinais v2.0

 # 1. Compilar:
 gcc -o <nome-programa>.out <nome-programa>.c

 # 2. Executar
 ./<nome-programa>.out

 # 3. Sinal SIGINT corresponde a <CTRL+C>

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int flag = 0;

/* Funcao manipuladora de sinais */
void confirma_saida(int sig) {
    /* Definir sinalizador flag como LIGADO */
    flag = 1;
}

int main() {
    void *sig;
    char tecla;

    /* Associar a funcao manipuladora de sinal a um sinal especifico */
    sig = signal(SIGINT, confirma_saida);

    if(sig == SIG_ERR)
        fprintf(stderr, "Nao foi possivel pegar o sinal");

    /* Main program */
    printf("Bem-vindos ao programa signal 2.0 RELOADED!\n");
    while(1) {
        if(flag == 1) { /* Sinalizador LIGADO */
            /* Definir sinalizador flag como DESLIGADO */
            flag = 0;

            /* Leitura do teclado */
            printf("\nTem certeza que quer terminar [s/n]? ");
            tecla = getchar();
            if(tecla == 's')
                exit(0);
        }
        else /* Sinalizador DESLIGADO */
            sleep(1);
    }

    return 0;
}
