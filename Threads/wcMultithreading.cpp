// Here the shared resource is the file which can either be broken into segments or concurrently accessed for coutning 
// The criticial section here will be lc,wc,cc as all threads must not concurrently make channges so they have to be synchornized
// vid a mutex
#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <algorithm>
#include <chrono>
#include <array>
#include <fstream>
using namespace std;
std::mutex m;
//  synchronization can be done using mutexes 
int charC=0;
int wordC=0;
int lineC=0;
char ch;
void wcT(const char *fileName){
    ifstream f;
    f.open(fileName);
    while(!f.eof()){
        f.get(ch);
        if(ch=='\n'){
            lineC+=1;
            wordC+=1;
        }
        else if(ch=='\t' || ch== ' '){
            wordC+=1;
            
        }
        charC++;

    }

    cout<<"Single Thread CharCOunt"<<charC<<'\n';
    cout<<"Single Thread WordCOunt"<<wordC<<'\n';
    cout<<"SIngle Thread LineCOunt"<<lineC<<'\n';

}
int charCm=0;
int wordCm=0;
int lineCm=0;
char ch1;
int totCh=0;
int totll=0;
int totWd=0;
void countMt(const char *filename, long offset, long size){
    //  Offset --> Kyathi size --> ketlu
    FILE *fp1;
    fp1= fopen(filename, "r");
    if (fseek(fp1, offset, SEEK_SET) < 0) {
        char buf[BUFSIZ] = {0};
        // snprintf(buf, BUFSIZ, "[%d] fseek");
        
    }
    for (long i = 0; i < size; i++) {
        int ch1 = fgetc(fp1);
    
        if(ch1=='\n'){
          
            lineCm+=1;
            wordCm+=1;
       
        }
        else if(ch1=='\t' || ch1== ' '){
       
            wordCm+=1;
          
            
        }
      
        charCm++;
        m.lock();
        totCh+=charCm;
        totll+=lineCm;
        totWd+=wordCm;
        m.unlock();


    }
   
}

int main(){
    // 3 separate functions thi to easily thai jase a bigger challenege is to split the files into segments
    // Input the num of threads 
    int numT;
    long size;
    cin>>numT;
    // max 8-16
    FILE *fp;
    fp = fopen("final.html", "r");
    // Moving pointer to end
    fseek(fp, 0, SEEK_END);
    //printf("%ld\n", ftell(fp));
    size=ftell(fp);
    cout<<"size of FIle"<<size<<'\n';
 
    // SO NOw we have the size as well and the numT as well
    long bpt=size/numT;
    // So our bytes per thread to read are this and this can be used to increment offsets
    cout<<"Bytes per thread"<<bpt<<'\n';
    // Bpt is also the size each thread has to read from it's specified offset
    long tsize=bpt;
    // Declaring an array of threads with size  numT
    std::thread threads[numT];
    // We will create all the threads with calling wcT and pass an offset from where it can read
    // std::thread single_thread(wcT,"final.html");
    // if(single_thread.joinable()){
    //     single_thread.join();
    // }
    long off=0;
    for (int i=0;i<numT;i++){
        // arguments to be passed as csv
        threads[i]=std::thread (countMt,"final.html",off,bpt);
        off+=bpt;
    }
    //  Joining the threads
    for (int j=0;j<numT;j++){
        if(threads[j].joinable()){
            threads[j].join();
        }
    }
     // Prining the Final Res
    cout<<"Multi-Threading CharCOunt"<<totCh<<'\n';
    cout<<"Multi-THreading WordCOunt"<<totWd<<'\n';
    cout<<"Multi-Threading LineCOunt"<<totll<<'\n';

    return 0;


}
