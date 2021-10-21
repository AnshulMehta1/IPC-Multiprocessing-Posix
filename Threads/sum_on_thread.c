/* 
Spawn Multiple threads to make the work faster
Ligth Weight Processes
To sum up numbers and add them using thread
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Sum maate
long long sum = 0;

// Thread function to generate sum of 0 to N
void* sum_runner(void* arg) {
    // casting the arg to long long *
    long long *limit_ptr = (long long*)arg;
    // get the pointer value OR deference the pointer
    long long limit = *limit_ptr;
    // Simple RUnning sm
    long long i = 0;
    for (i = 0; i <= limit; i++) {
        sum += i;
    }

    // what to do w sum? how to exit
    pthread_exit(0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <num>\n", argv[0]);
        exit(-1);
    }

    long long limit = atoll(argv[1]);

    // pthread_create --> pthread data type: id
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // pthread create points to a function
    pthread_create(&tid, &attr, sum_runner, &limit);

    // do other stuff.
    // wait for thread to complete.
    pthread_join(tid, NULL);

    printf("Sum is %lld\n", sum);
}
