// Calculate the sum of primes and the maximum sum
#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <ctime>
#include <cstdio>
#ifdef __linux__ 
#define _BSD_SOURCE
#include <sys/time.h>
#endif

#include <mutex>
std::mutex m;
#define MAX_PRIMES	10
#define	N_MAX		100000000
#define N_WORKERS	8
using namespace std;
// For checking if the number is Prime or not
int isPrime(int N)
{
	if (N == 2)
		return true;

	// Check if it divides evenly
	if (N == 1 || N % 2 == 0)
		return false;

	int max = sqrt(N) + 1;
	for (int i = 3; i < max; i += 2)
	{
		// Check if it divides evenly
		if (N % i == 0)
			return false;
	}
	return true;
}
long localPsum=0;
long localMax=0;

void thread_calc(int start,int end){
    for (int i=start;i<end;i++){
        if(isPrime(i)==true){
            m.lock();
            localPsum+=i;
            m.unlock();
           
        }
       
    }
    // Shared resource
    // m.lock();
    // globalPsum+=localPsum;
    // if (localMax>globalMax)
    // {
    //     globalMax=localMax;
    // }
    // m.unlock();

    


}

int main(){
    int numT=8;
    // Divide the range into 8 Parts
    long gap=100000000/numT;
    // This will be the size each thread will iterate
    int offset=0;
    // Offset will be given to each thread and then 
    std:: thread threads[numT];
    for (int i=0;i<numT;i++){
        threads[i]=std::thread(thread_calc,i*gap,(i+1)*gap);
    }

    for(int i=0;i<numT;i++){
        if(threads[i].joinable()){
            threads[i].join();
        }
    }
    cout<<"Sum of Primes"<<localPsum;
    return 0;

}
