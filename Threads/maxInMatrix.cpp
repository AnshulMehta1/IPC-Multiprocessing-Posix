// Here the shared resource is the matrix which can be broken into fragments
#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <algorithm>
#include <chrono>
#include <array>
using namespace std;
std::mutex m1;
int localM=0;
int globalM=0;
void maxinArray(int arr[]){
     int len = sizeof(arr);
     for (int i=0;i<len;i++){
         if(arr[i+1]>arr[i]){
             localM=arr[i];
         }
     }
     m1.lock();
     if (localM>globalM){
         globalM=localM;
     }
     m1.unlock();

}

// Maximum of two threads will be stored in an array

int main(){
    int numT=3;
    int x[3][3] = {{0,1,2}, {3,4,5}, {8,9,10}};
    // NUmber  of threads to 2-D array na row dimesnion par lesu
    std::thread threads[3];
    cout<<numT;
    // We cann do an enhanced for loop
    for (int i=0;i<numT;i++){
        threads[i]=std::thread(maxinArray,x[i][0]);

    }

    for (int i = 0; i < numT; ++i) {
        if(threads[i].joinable()){
              threads[i].join();
         }
    }
    cout<<globalM;
    return 0;

    
}
