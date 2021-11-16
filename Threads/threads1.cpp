#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
typedef long long ll;
ll OddSum=0;
ll EvenSum=0;
void addEven(ll start,ll end){
    for (ll i=start;i<end;i+=1){
        if(i%2==0){
            EvenSum+=i;
        }
    }
}
void addOdd(ll start,ll end){
    for (ll i=start;i<end;i+=1){
        if(i%2!=0){
            OddSum+=i;
        }
    }
}
