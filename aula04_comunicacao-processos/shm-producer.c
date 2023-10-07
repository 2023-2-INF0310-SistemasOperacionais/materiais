/*
 Programa: Uso da memoria compartilhada em sistemas POSIX

 Este e o processo produtor que escreve na regiao de memoria compartilhada

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lrt

 @adapted_from: Figure 3.16
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
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main() {
    /* Tamanho do objeto memoria compartilhada (em bytes) */
    const int SIZE = 4096;
    /* Nome do objeto memoria compartilhada */
    const char *name = "shared-mem";
    /* strings escritas na memoria compartilhada */
    const char *message0= "Estudar Sistemas Operacionais\n";
    const char *message1= "e bom demais!\n";

    /* Descritor do arquivo de memoria compartilhada */
    int shm_fd;
    /* Ponteiro ao objeto memoria compartilhada */
    void *ptr;

    /* Criar o objeto memoria compartilhada */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if(shm_fd == -1) {
        fprintf(stderr, "Falha ao abrir a memoria compartilhada\n");
        exit(-1);
    }

    /* Definir tamanho do objeto memoria compartilhada */
    ftruncate(shm_fd,SIZE);

    /* Mapear o objeto memoria compartilhada no espaco de enderecos do processo */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(ptr == MAP_FAILED) {
        fprintf(stderr, "Falha no mapeamento da memoria compartilhada\n");
        return -1;
    }

    /* Escritura no objeto memoria compartilhada */
    sprintf(ptr, "%s", message0);
    ptr += strlen(message0);
    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);

    return 0;
}
