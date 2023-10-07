/*
 *  * Teste com fork e espacos de enderecamento.
 *   */ 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

volatile int s = 0; /* Variavel compartilhada */

int main() {

	printf("Antes do fork\n");
   
	if (fork() == 0) {
		s = 0;
		printf("Processo filho, &s = %p, s = %d\n", (void*) &s, s);
	} else {
		s = 1;
		printf("Processo pai,   &s = %p, s = %d\n", (void*) &s, s);
	} 
     
	return 0;
}
