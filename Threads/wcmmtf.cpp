#include<thread>
#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <array>
using namespace std;
mutex mu;
long totalChar=0;
long totalLine=0;
long totalWord=0;

void FUNC(int l,int r,string fileName){
    ifstream fin;
	fin.open(fileName);
	long word=0;
    long line=0;
    long charC=0;
    char ch;
    fin.seekg(l,ios::beg); //bring position of file pointer to begining of file
    while(fin){
        fin.get(ch);
        if(l==r){
            break;
        }
        if(ch==' '|| ch=='\t'){
            word++;
        }
        if(ch=='\n'){
            line++;
            word++;
        }
        charC++;
        l++;
    }
    fin.close();
    mu.lock();
    totalChar+=charC;
    totalLine+=line;
    totalWord+=word;
    mu.unlock();
}

int main(int argc,char **argv){
    string fileName=argv[1];
    FILE *p_file = NULL;
    p_file = fopen(fileName.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int fileSize = ftell(p_file);
    fclose(p_file);
    int numProcess=atoll(argv[2]);
    int gap=fileSize/numProcess;
    thread threads[numProcess];
    for(int i=0;i<numProcess;i++){
        if(i==numProcess-1){
            threads[i]=thread(FUNC,i*gap,fileSize,fileName);
            continue;
        }
        threads[i]=thread(FUNC,i*gap,(i+1)*gap,fileName);
    }
    for(int i=0;i<numProcess;i++){
        if(threads[i].joinable()){
            threads[i].join();
        }
    }
    cout<<"Line"<<" "<<"Word"<<" "<<"Char"<<endl;
    cout<<totalLine<<" "<<totalWord<<" "<<totalChar<<endl;
}
