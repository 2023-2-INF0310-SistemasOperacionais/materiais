/*
 Programa: Uso de sinais v1.0

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

/* Funcao manipuladora de sinais */
void confirma_saida(int sig) {
    /* KeyboardInterrupt: Sinal de usuario <CTRL+C> */
    if(sig == SIGINT) {
        printf("\nSinal de usuario recebido: SIGINT (Signal Interrupt)\n");
        printf("Tem certeza que quer terminar [s/n]? ");
        if(getchar() == 's')
            exit(0);
    }
}

int main() {
    /* Associar a funcao manipuladora de sinal a um sinal especifico */
    if(signal(SIGINT, confirma_saida) == SIG_ERR)
        fprintf(stderr, "Nao foi possivel pegar o sinal");

    printf("Bem-vindos ao programa signal\n");

    /* Executar uma espera longa */
    while(1)
        sleep(1);

    return 0;
}