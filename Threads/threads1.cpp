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

int main(){
    ll start=0;
    ll end=1000000;
    std ::thread t1(addEven,start,end);
    std::thread t2(addOdd,start,end);
    t1.join();
    t2.join();
    cout<<"Even Sum is "<<EvenSum<<endl;
    cout<<"Odd Sum is "<<OddSum<<endl;

}
