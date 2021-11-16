#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
using namespace std;
typedef long long ll;

int counter=0;
std::mutex m;
void inc(){
	for (int i=0;i<999999;i++){

		if (m.try_lock()){
			counter++;
			m.unlock();
		}

	}

}

int main(){
	std::thread t1(inc);
	std::thread t2(inc);
	t1.join();
	t2.join();
	return 0;
}
