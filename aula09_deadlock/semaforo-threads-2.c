/*
 * Sincronismo com semaforos sem nome em multithread
 * Mostrar valores inteiros em ordem especifica
 *
 * Compilacao:
 * gcc -o semaforo-threads-2.out semaforo-threads-2.c -lpthread
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
void *T0(void *param);
void *T1(void *param);

int main(int argc, char *argv[]) {
	pthread_t workers[NUM_THREADS]; /* Identificador das threads */
	pthread_attr_t attr; /* Conjunto de atributos das threads */

	/* Validacao de argumentos */
	if (argc != 3) {
		fprintf(stderr,"Uso: <meuPrograma.out> <valor_inteiro> <valor_inteiro>\n");
		/*exit(1);*/
		return -1;
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"Argumento %d deve ser nao-negativo\n",atoi(argv[1]));
		/*exit(1);*/
		return -1;
	}
	if (atoi(argv[2]) < 0) {
		fprintf(stderr,"Argumento %d deve ser nao-negativo\n",atoi(argv[2]));
		/*exit(1);*/
		return -1;
	}

	/* Criar e inicializar o Semaforo no valor de 0 */
	sem_init(&sem, 1, 0); // flag1->1: recurso compartilhado entre processos
												// flag2->0: valor inicial do semaforo

	/* Obter atributos padrao das threads */
	pthread_attr_init(&attr);

	/* Criar threads */
	pthread_create(&workers[0],&attr,T0,argv[1]);
	pthread_create(&workers[1],&attr,T1,argv[2]);

	/* Aguardar threads */
	for(int i=0; i<NUM_THREADS; i++)
		pthread_join(workers[i],NULL);

	/* Eliminar Semaforo */
	sem_destroy(&sem);

	return 0;
}

/* Definicao das threads */
void *T0(void *param) {
	int upper = atoi(param);

	/* Adquirir Semaforo */
	sem_wait(&sem);

	/* Secao critica */
	fprintf(stdout,"Sou T0: %d\n",upper);

	/* Liberar Semaforo */
	sem_post(&sem);

	pthread_exit(0);
}

void *T1(void *param) {
	int upper = atoi(param);

	/* Secao critica */
	fprintf(stdout,"Sou T1: %d\n",upper);

	/* Liberar Semaforo */
	sem_post(&sem);

	pthread_exit(0);
}
