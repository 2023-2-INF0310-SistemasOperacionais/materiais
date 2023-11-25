/*
 * Deadlock com semaforo sem nome em multithread
 *
 * Compilacao:
 * gcc -o semaforo-deadlock.out semaforo-deadlock.c -lpthread
 *
 * @author Prof. Aldo Diaz, 2021
 * Instituto de Informatica - INF
 * Universidade Federal de Goias - UFG
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NUM_THREADS	2

/* Variaveis globais */
sem_t sem; /* Semaforo na API POSIX Pthreads */

/* Threads */
void *T0();
void *T1();

int main() {
	pthread_t workers[NUM_THREADS]; /* Identificador das threads */
	pthread_attr_t attr; /* Conjunto de atributos das threads */

	/* Criar e inicializar o Semaforo no valor de 0 */
	sem_init(&sem, 1, 1); // flag1->1: recurso compartilhado entre processos
			      // flag2->0: valor inicial do semaforo
	
	/* Obter atributos padrao das threads */
	pthread_attr_init(&attr);

	/* Criar threads */
	pthread_create(&workers[1], &attr, T1, NULL);
	pthread_create(&workers[0], &attr, T0, NULL);

	/* Aguardar threads */
        pthread_join(workers[0], NULL);
        pthread_join(workers[1], NULL);

	/* Eliminar Semaforo */
	sem_destroy(&sem);

	return 0;
}

/* Definicao das threads */
void *T0() {
	/* Adquirir Semaforo */
	sem_wait(&sem);

	/* Secao critica */
	fprintf(stdout,"Sou T0\n");

	/* Liberar Semaforo */
	sem_post(&sem);

	pthread_exit(0);
}

void *T1() {
	/* Adquirir Semaforo */
	sem_wait(&sem);

	/* Secao critica */
	fprintf(stdout,"Sou T1\n");

	/* Liberar Semaforo */
	sem_post(&sem);

	pthread_exit(0);
}

