#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <mutex>
using namespace std;
std::recursive_mutex m1;
std:: mutex m;
// std::mutex mA;
// std::mutex ma;
int i=1;
char c='A';
char c1='a';
int pos =0;
void Printpattern(){
    for (i = 0; i < 26; i++){
       
        m.lock();
        if (pos % 3 != 1){
            i--;
        }
        else{
            cout<<i+1;
            pos++;
        }
        m.unlock();    
       
    }
  
      
}


void Printpatternch(){
 
    for (int i=0;i<26;i++){
        m.lock();
   
        if (pos % 3 != 0) {
            i--;
        }
        else{
            c+=i;
            // cout<<'a'+i;
            printf("%c",'a'+i);
            pos++;
        }
       
        m.unlock();   
    }
}
void PrintpatternCH(){
     
     
    for (int i=0;i<26;i++){
        m.lock();
        
        if (pos % 3 != 2){
            i--;
        }
        else{
            c1+=i;
            printf("%c\n",'A'+i);
            // cout<<'A'+i;
            pos++;
        }
        
        m.unlock();  
    } 
}
int main(){
    // std::thread threads[25];
    // for (int i = 0; i < 25; ++i) {
    //     // Initializing the threads

    //     threads[i] = std::thread(Printpattern);
    // }
    // for (int i = 0; i < 25; ++i) {
    //     if(threads[i].joinable()){
    //          threads[i].join();
    //     }
       
    // }
    for (i=0;i<10;i++){
    std::thread threads[3];
	threads[0]=std::thread(Printpattern);
	threads[1]=std::thread(Printpatternch);
    threads[2]=std::thread(PrintpatternCH);
    for (int i = 0; i < 3; ++i) {
        if(threads[i].joinable()){
              threads[i].join();
         }
    }
    }
    return 0;
}
