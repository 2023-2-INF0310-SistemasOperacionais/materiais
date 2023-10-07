/*
 Exemplo de hierarquia de processos
   A
  / \
 B   C
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    if(fork())
        if(fork())
	    printf("Processo B\n");
	else
	    printf("Processo C\n");
    else
        printf("Processo A\n");

    return 0;
}
