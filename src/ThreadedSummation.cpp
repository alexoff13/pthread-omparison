#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include "ThreadedSummation.h"

using namespace std;

typedef struct{
    int numberFile;
    long sum;
} pthrData;

long CalculateSumOneThread(){
    ifstream in;
    stringstream ss;
    int summ;
    for(int i=0;i<10;i++){
    ss<<"..\\files\\"<<i+1<<".txt";
    in.open(ss.str());
    ss.str(std::string());
    if (in.is_open()) {
        while (!in.eof()) {
           int s;
           in>>s;
           summ+=s;
        }
    }
    in.close();
    }
    return summ;
}

void *CalculateSum(void *thread_data){
    ifstream in;
    stringstream ss;
    pthrData *data = (pthrData*) thread_data;
        ss<<"..\\files\\"<<data->numberFile+1<<".txt";
        in.open(ss.str());
        ss.str(std::string());
        if (in.is_open()) {
            while (!in.eof()) {
                int s;
                in>>s;
                data->sum+=s;
            }
        in.close();
    }
}

long CalculateTheSumByUsingThreads(){
    int N=10;
    //выделяем память под массив идентификаторов потоков
    pthread_t threads[N];
    //сколько потоков - столько и структур с потоковых данных
    pthrData* threadData= new pthrData[N];
    long sum=0;
    //инициализируем структуры потоков
    for(int i = 0; i < N; i++){
        threadData[i].numberFile=i;
        threadData[i].sum=0;
        //запускаем поток
        pthread_create(&(threads[i]), NULL, CalculateSum, &threadData[i]);
    }
    //ожидаем выполнение всех потоков
    for(int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
        sum+=threadData[i].sum;
    }
    return sum;
}
