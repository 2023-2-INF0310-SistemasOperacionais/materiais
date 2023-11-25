/*
 Programa: POSIX Semaforos com nome

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lpthread

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char *argv[]) {
    sem_t *sem; /* Semaforo na API POSIX Pthreads */

    /* Criar e inicializar o Semaforo no valor de 1 */
    sem = sem_open("SEM", O_CREAT, 0666, 1);

    /* Adquirir Semaforo */
    sem_wait(sem);

    /* Secao critica (Critical section) */

    /* Liberar Semaforo */
    sem_post(sem);

    /* Eliminar Semaforo */
    sem_destroy(sem);

    return 0;
}
