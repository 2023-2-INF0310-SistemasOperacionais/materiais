/*
 Programa: Escalonamento em sistemas POSIX

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lpthread

 @adapted_from: Figure 5.10
 Operating System Concepts - Tenth Edition
 Silberschatz, Galvin, and Gagne

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS  5 /* Numero de threads a criar */

/* Declaracao da funcao thread */
void *runner(void *param);

int main(int argc, char *argv[]) {
    int i, scope;
    pthread_t tid[NUM_THREADS];  /* TID - Identificador da threadr */
    pthread_attr_t attr; 	 /* Thread PCB - Conjunto de atributos da thread */

    /* Definir atributos de thread padrao */
    pthread_attr_init(&attr);

    /* Consultar escopo atual */
    if(pthread_attr_getscope(&attr, &scope) != 0)
        fprintf(stderr, "Nao foi possivel obter o escopo de escalonamento\n");
    else {
        if(scope == PTHREAD_SCOPE_PROCESS)
	    printf("PTHREAD_SCOPE_PROCESS\n");
	else if(scope == PTHREAD_SCOPE_SYSTEM)
	    printf("PTHREAD_SCOPE_SYSTEM\n");
	else
	    fprintf(stderr, "Valor de escopo ilegal\n");
    }

    /* Configurar algoritmo de escalonamento de PCS para SCS */
    if(pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) != 0)
        fprintf(stderr, "Nao foi possivel configuar a politica de escalonamento\n");

    /* Criar threads */
    for(i = 0; i < NUM_THREADS; i++)
        pthread_create(&tid[i], &attr, runner, NULL);

    /* Juntar-se a cada thread */
    for(i = 0; i < NUM_THREADS; i++)
        pthread_join(tid[i], NULL);
}

/* Definicao da funcao thread */
void *runner(void *param) {
    /* fazer alguma coisa ... */
    printf("oi sou a thread exemplo\n");
    pthread_exit(0);
}
