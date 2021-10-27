/*
 
Do time analysis
 
Shared Buffer
1)Manage shared memory
Probably using Mutex
2)What happens if the buffer is full
Or multiple producers
So check if buffer is full
 
3) What if P>C
 Also check if the buffer is empty
 
 Also tweak around the number of consumers and Producers
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>
#define THREADS 2
pthread_mutex_t  mutexBuffer;
sem_t semAvailable;
sem_t semOccupied;
 
int buffer[20];
int count=0;
 
 // This step produces a
void *producer(void *args){
    // To get the essence of the consumer producer question we need a constant inflow of processes
    while(1){
        int a=rand() % 100;
        // Here we have to decrement the buffer by 1 and wait for an empty slot to add a  to the Buffer
        sem_wait(&semAvailable);
         // To avoid the race condition
        pthread_mutex_lock(&mutexBuffer);
       
        if (count<20){
             buffer[count] =a;
            // Add it to the buffer and  them increment the counter
            count++;
        }
        else{
            printf("Entities Skipped %d",a);
        }
       // Once a occupies a place in the buffer we need to increment the semaphore
        sem_post(&semOccupied);
        pthread_mutex_unlock(&mutexBuffer);
    }
 
}
 
void *consumer(void *args){
    int out=-1;
    // Here it is the inverse as we will wait for Sem Full and post on semAvailable
    // This is due to emptying of buffer in this case
    sem_wait(&semOccupied);
    pthread_mutex_lock(&mutexBuffer);
    // Here we have to read the value from the buffer and also check for empty buffer
    if (count>0){
        out=buffer[count-1];
        // Here we will be using STack so LIFO Policy Followed
        count--;
        // Decrement the count
    }
    pthread_mutex_unlock(&mutexBuffer);  
   
    // Print the element
    sem_post(&semAvailable);
    printf("Consumed %d\n",out);
 
}
 
 
int main(int argc, char *argv[]){
    srand(time(NULL));
    pthread_t threads[THREADS];
    // Initializing the Mutex
    pthread_mutex_init(&mutexBuffer,NULL);\
    // Initializing the semaphores
    sem_init(&semAvailable,0,20);
    sem_init(&semOccupied,0,0);
    // Creating two threads
    // So obviously we can create more consumer threads and producer threads
    for (int i=0;i<THREADS;i++){
        if (i%2==0){
           
            if (pthread_create(&threads[i],NULL,&producer,NULL)!=0){
                perror("Thread was not created");
            }
        }
        else{
            if (pthread_create(&threads[i],NULL,&consumer,NULL)!=0){
                 perror("Thread was not created");
            }
        }
        // Now we will join the threads together
        for (int j=0;j<THREADS;j++){
            if (pthread_join(threads[i],NULL)!=0){
                perror("Threads not joined");
            }
        }
    }
   
    pthread_mutex_destroy(&mutexBuffer,NULL);
    sem_destroy(&semAvailable);
    sem_destroy(&semOccupied);
 
    return 0;
 
 
 
 
 
}
