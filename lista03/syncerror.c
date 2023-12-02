/*
 Programa: syncerror

 # Compilar
 gcc -o <nome-programa>.out <nome-programa>.c -lpthread

 @author: Prof. Dr. Aldo Diaz
          Instituto de Informatica - INF
          Universidade Federal de Goias - UFG
 Copyright Aldo Diaz - 2021
*/

#include <stdio.h>

#define FILENAME1 "arq1.txt"
#define FILENAME2 "arq2.txt"

pthread_mutex_t arq1_lock, arq2_lock;

void *t1() {
    FILE *arq1, *arq2;
    
    pthread_mutex_lock(&arq2_lock);
    pthread_mutex_lock(&arq1_lock);
    
    arq1 = fopen(FILENAME1, "w");
    printf("Thread%d@TID-%d: Escrevendo no %s\n", 1, pthread_self(), FILENAME1);
    fputs("1 2 3 4 5\n", arq1);
    fclose(arq1);
    
    arq2 = fopen(FILENAME2, "w");
    printf("Thread%d@TID-%d: Escrevendo no %s\n", 1, pthread_self(), FILENAME2);
    fputs("A B C D E\n", arq2);
    fclose(arq2);
    
    pthread_mutex_unlock(&arq2_lock);
    pthread_mutex_unlock(&arq1_lock);
}

void *t2() {
    FILE *arq1, *arq2;
    
    pthread_mutex_lock(&arq1_lock);
    pthread_mutex_lock(&arq2_lock);
    
    arq1 = fopen(FILENAME1, "w");
    printf("Thread%d@TID-%d: Escrevendo no %s\n", 2, pthread_self(), FILENAME1);
    fputs("6 7 8 9 10\n", arq1);
    fclose(arq1);
    
    arq2 = fopen(FILENAME2, "w");
    printf("Thread%d@TID-%d: Escrevendo no %s\n", 2, pthread_self(), FILENAME2);
    fputs("F G H I J\n", arq2);
    fclose(arq2);
    
    pthread_mutex_unlock(&arq1_lock);
    pthread_mutex_unlock(&arq2_lock);
}

int main() { 
    pthread_t tid[2];
    
    pthread_mutex_init(&arq1_lock, NULL);
    pthread_mutex_init(&arq2_lock, NULL);
    
    pthread_create(&tid[0], NULL, t1, NULL);
    pthread_create(&tid[1], NULL, t2, NULL);
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    return 0;
}
