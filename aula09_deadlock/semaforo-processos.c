#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int main(){
	pid_t pid;
  sem_t sem;
  
  for(int i = 0; i< 2; i++) {
    switch(i){
      case 0: /* P0 */
        pid = fork();
        if(pid<0){
          fprintf(stdout,"fork falhou!");
        }
        else if(pid == 0){ /* Filho P0 */
          fprintf(stdout,"S1\n");
          exit(0);
        }
        else { /* Processo pai*/
          wait(NULL);
        }
        break;
      case 1: /* P1 */
        pid = fork();
        if(pid<0){
          fprintf(stdout,"fork falhou!");
        }
        else if(pid == 0){ /* Filho P0 */
          fprintf(stdout,"S2\n");
          exit(0);
        }
        else { /* Processo pai*/
          wait(NULL);
        }
        break;
      default:
        break;
    }
  }
  
	/* Create the semaphore and initialize it to 1
	sem_init(&sem, 0, 1); // flag 0: resource is shared locally

	/* acquire the semaphore
	sem_wait(&sem);

  /* critical section

  /* release the semaphore
  sem_post(&sem);
  */
  return 0;
}