/* Programa Multiplos Processos
*
* # 1. Compilar:
* gcc -o <nome-programa>.out <nome-programa>.c -lm
*
* # 2. Executar
* time ./<nome-programa>.out
*
*/

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NPROCESS 10

void CPU_bound(int id) {
    int i;
    double result=0.0;

    /* Consumo de CPU */
    for (i=0; i<10000; i++)
        result = result + sin(i) * tan(i) * sqrt(result);
    printf("%d: CPU intensiva terminada\n", id);
}

void IO_bound(int id) {
    /* Simula operações de I/O, as quais levam a bloqueio */
    sleep(1);
    printf("%d: E/S intensiva terminada\n", id);
}

int main() {
    int i, status;
    pid_t children[NPROCESS];

    for(i=0; i<NPROCESS; i++) {
        if(i % 2) {
            children[i] = fork();
            if(children[i] == 0) {
                CPU_bound(i);
                exit(0);
            }
        }
        else {
            children[i] = fork();
            if(children[i] == 0) {
                IO_bound(i);
                exit(0);
            }
        }
    }

    for(i=0; i<NPROCESS; i++)
        waitpid(children[i], &status, 0);

    printf("\n*** Tarefas concluidas ***\n");

    return 0;
}
