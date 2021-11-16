#include <iostream>
#include <thread>
#incluude <mutex>
#include <chrono>
#include <algorithm>
using namespace std;
typedef long long ll;

// Race Condition
//Race to access the data  and do some things with the data
// Initializes a mutex
std:: mutex m;

// Critical Section
void addMoney(){
	m.lock();
	myAmount++;
	m.unlock();
}
int main(){
	std::thread t1(addMoney);
	std::thread t2(addMoney);
	t1.join();
	t2.join();
}
