/*
 * Exemplo de uso de fork. Quantos processos serão criados?
*/


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

  fork();
  fork();
  fork();

  printf("PID = %d\n", getpid());

  return 1;
}
