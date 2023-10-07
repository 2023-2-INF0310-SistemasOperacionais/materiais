/*
 Programa: Mostrar PID do pai, filho e avo

 # 1. Compilar:
 gcc -o <nome-programa>.out <nome-programa>.c

 # 2. Executar
 ./<nome-programa>.out

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SLEEP_TIME  2

int main() {
    pid_t pid;

    pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Fork falhou\n");
        return 1;
    }
    if(pid == 0) { /* Processo filho */
        printf("Processo filho: Valor da variavel \"pid\" = %d\n", pid);
        printf("Processo filho: Pausa de %d segundos\n", SLEEP_TIME);
        sleep(SLEEP_TIME);
        printf("Processo filho: PID do filho = %d\n", getpid());
    }
    else { /* Processo pai */
        /* Pai aguardara filho completar */
        printf("Processo pai: Valor da variavel \"pid\" = %d\n", pid);
        wait(NULL);
        printf("Processo pai: Filho completou\n");
        printf("Processo pai: PID do pai = %d\n", getpid());
        printf("Processo pai: PID do avo = %d\n", getppid());
    }

    return 0;
}
