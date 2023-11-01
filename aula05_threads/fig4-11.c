/*
 Programa: Uso da API POSIX pthread

 Este programa ilustra como criar uma thread simples com a API pthread
 O programa implementa uma funcao de soma. A operacao de adicao roda em uma
 thread separada

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lpthread

 @adapted_from: Figure 4.11
 Operating System Concepts - Tenth Edition
 Silberschatz, Galvin, and Gagne

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* Dado compartilhado pelas threads */

void *runner(void *param); /* Declaracao da funcao que a thread executa */

int main(int argc, char *argv[]) {
    pthread_t tid; /* TID - Identificador da thread */
    pthread_attr_t attr; /* Thread PCB - Conjunto de atributos da thread */

    /* Validar argumentos de entrada */
    if(argc != 2) {
        fprintf(stderr, "Sintaxe: <programa.out> <valor_inteiro>\n");
        return -1; // exit(-1);
    }

    if(atoi(argv[1]) < 0) {
        fprintf(stderr, "Argumento %d deve ser nao-negativo\n", atoi(argv[1]));
        exit(-1);
    }

    /* Definir thread com atributos padrao */
    pthread_attr_init(&attr);

    /* Criar thread */
    pthread_create(&tid, &attr, runner, argv[1]);

    /* Aguardar thread finalizar */
    pthread_join(tid, NULL);

    printf("A soma e: %d\n", sum);
}

/* Definicao da funcao que a thread executa */
void *runner(void *param) {
    int i, upper = atoi(param);
    sum = 0;

    if(upper > 0) {
        for (i = 1; i <= upper; i++)
            sum += i;
    }

    pthread_exit(0);
}
