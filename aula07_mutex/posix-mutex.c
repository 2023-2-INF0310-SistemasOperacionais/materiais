/*
 Programa: POSIX MutEx

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lpthread

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <pthread.h>

int main(int argc, char *argv[]) {
    pthread_mutex_t mutex; /* MutEx na API POSIX Pthreads */

    /* Criar e inicializar o MutEx */
    pthread_mutex_init(&mutex, NULL);

    /* Adquirir MutEx */
    pthread_mutex_lock(&mutex);

    /* Secao critica (Critical section) */

    /* Liberar MutEx */
    pthread_mutex_unlock(&mutex);

    /* Eliminar MutEx */
    pthread_mutex_destroy(&mutex);

    return 0;
}
