/*
 Programa: Thread ilustrando escalonamento Pthread de tempo real (RT)

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lpthread

 @adapted_from: Figure 5.25
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
    int i, policy;
    pthread_t tid[NUM_THREADS];  /* TID - Identificador da threadr */
    pthread_attr_t attr;         /* Thread PCB - Conjunto de atributos da thread */

    /* Definir atributos de thread padrao */
    pthread_attr_init(&attr);

    /* Consultar politica de escalonamento atual */
    if(pthread_attr_getschedpolicy(&attr, &policy) != 0)
        fprintf(stderr, "Nao foi possivel obter a politica de escalonamento\n");
    else {
        if(policy == SCHED_OTHER)
	    printf("SCHED_OTHER\n");
	else if(policy == SCHED_RR)
	    printf("SCHED_OTHER\n");
	else if(policy == SCHED_FIFO)
            printf("SCHED_FIFO\n");
    }

    /* Configurar a politica de escalonamento - FIFO, RT, ou OTHER */
    if(pthread_attr_setschedpolicy(&attr, SCHED_OTHER) != 0)
        fprintf(stderr, "Nao foi possivel configurar a politica de escalonamento para SCHED_OTHER\n");

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
    printf("somos as threads em tempo real\n");
    pthread_exit(0);
}
