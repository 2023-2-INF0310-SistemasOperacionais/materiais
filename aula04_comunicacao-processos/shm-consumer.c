/*
 Programa: Uso da memoria compartilhada em sistemas POSIX

 Este e o processo consumidor

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lrt

 @adapted_from: Figure 3.18
 Operating System Concepts - Tenth Edition
 Silberschatz, Galvin, and Gagne

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
    /* Tamanho do objeto memoria compartilhada (em bytes) */
    const int SIZE = 4096;
    /* Nome do objeto memoria compartilhada */
    const char *name = "shared-mem";
    /* Descritor do arquivo de memoria compartilhada */
    int shm_fd;
    /* Ponteiro ao objeto memoria compartilhada */
    void *ptr;

    /* Abrir o objeto memoria compartilhada */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if(shm_fd == -1) {
        fprintf(stderr, "Falha ao abrir a memoria compartilhada\n");
        exit(-1);
    }

     /* Mapear o objeto memoria compartilhada no espaco de enderecos do processo */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED) {
        printf("Falha no mapeamento da memoria compartilhada\n");
        exit(-1);
    }

    /* Leitura do objeto memoria compartilhada */
    printf("%s", (char *)ptr);

    /* Remover o objeto memoria compartilhada */
    if(shm_unlink(name) == -1) {
        fprintf(stderr, "Erro ao remover %s\n", name);
        exit(-1);
    }

    return 0;
}
