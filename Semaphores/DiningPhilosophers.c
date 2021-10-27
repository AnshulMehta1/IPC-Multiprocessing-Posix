/*
Either eat or think on the table
Five Chopsticks in total
Two chopsticks needed to eat
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>
#define THREADS 5
sem_t chopsticks[5];
 
void *philosophers(void *args){
    int ph=*(int *)args;
    printf("Philosopher %d wants to eat\n",ph);
    printf("Philosopher %d tries to pick left chopstick\n",ph);
    sem_wait(&chopsticks[ph]);
    printf("Philosopher %d picks the left chopstick\n",ph);
    printf("Philosopher %d tries to pick the right chopstick\n",ph);
    sem_wait(&chopsticks[(ph+1)%5]);
    printf("Philosopher %d picks the right chopstick\n",ph);
    eat(ph);
    sleep(2);
   
    printf("Philosopher %d has finished eating\n",ph);
    sem_post(&chopsticks[(ph+1)%5]);
    printf("Philosopher %d leaves the right chopstick\n",ph);
    sem_post(&chopsticks[ph]);
    printf("Philosopher %d leaves the left chopstick\n",ph);
 
}
 
void *eat(void *args){
 
    printf("Philosopher %d begins to eat\n",ph);
 
}
 
int main(int argc, char *argv[]){
    int n[5];
    pthread_t threads[THREADS];
    // Initializing semaphores for five chopsticks
    for (int i=0;i<5;i++){
          sem_init(&chopsticks[i],0,1);
    }
    // Initializing threads for five philosophers
    for (int i=0;i<THREADS;i++){
        n[i] =i;
        if(pthread_create(&threads[i],NULL,philosophers,NULL)!=0){
            perror("Thread not created");
 
        }
    }
    // Joining the threads
    for (int j=0;j<THREADS;j++){
            if (pthread_join(threads[i],NULL)!=0){
                perror("Threads not joined");
            }
}
