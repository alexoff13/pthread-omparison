#include <iostream>
#include <time.h>
#include "src/ThreadedSummation.h"

int main() {
     clock_t start = clock();
     std::cout<<"One thread:"<<CalculateSumOneThread()<<std::endl;
     clock_t end = clock();

     double seconds = (double)(end - start) / CLOCKS_PER_SEC;
     printf("The time: %f seconds\n", seconds);

     start = clock();
     std::cout<<"Ten thread:"<<CalculateTheSumByUsingThreads()<<std::endl;
     end = clock();

     seconds = (double)(end - start) / CLOCKS_PER_SEC;
     printf("The time: %f seconds\n", seconds);

}