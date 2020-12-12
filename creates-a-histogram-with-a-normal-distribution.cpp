
//Main for "creates-a-histogram-with-a-normal-distribution" C application
//Created by r4m0nl1m4 02/12/2020

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include "histogram.h"
#include <unistd.h>

int *array, size, N, min, max, histogram[50], start = 0;
float TotalHistogramGroups, HistogramGroupInterval;

pthread_mutex_t lock;
pthread_cond_t cond;

void *work(void *)
{
    int i, temp;

    pthread_mutex_lock(&lock);
    if(start==0)
        pthread_cond_wait(&cond, &lock);    
    pthread_mutex_unlock(&lock);

    for(;;){
        pthread_mutex_lock(&lock);
        i=size-1;
        size--;
        pthread_mutex_unlock(&lock);

        if(size<0){
            pthread_mutex_lock(&lock);
            pthread_cond_wait(&cond, &lock);
            pthread_mutex_unlock(&lock);
        }

        if(i<0)
            break;

        if(min > array[i])
            min = array[i];
        if(max < array[i])
            max = array[i];                   
    }

    for(;;){
        pthread_mutex_lock(&lock);
        i=size-1;
        size--;
        pthread_mutex_unlock(&lock);
        if(i<0)
            break;
        temp = (float)((array[i]-min))/HistogramGroupInterval;
        if(temp > (TotalHistogramGroups-1))
            temp = TotalHistogramGroups-1;
        histogram[temp]++;
    }

    return NULL;
}

int main(int argc, char **argv)
{
    int problemSize = atoi(argv[1]);

    pthread_t id;
    void *status;            
    int i, nThread;

    pthread_mutex_init(&lock,0);
    pthread_cond_init(&cond,0);

    array  = (int*)calloc( problemSize, sizeof(int) );
    array = generateGaussRandomArray(problemSize);
    //array = getRandomArrayByTerminal(&argc, const_cast<const char**>(argv));

    size = sizeof(array)/sizeof(array[0]);
    N = size;

    HistogramGroupInterval = rand() % 1000;

    TotalHistogramGroups = (float) size / (float) HistogramGroupInterval;

    min = max = array[0];

    for(i=0; i < TotalHistogramGroups; i++)
        histogram[i] = 0;

    nThread = getThreadsNumber();                 
    for(i=0; i < nThread; i++){
        bool pthreadCreated = ( pthread_create(&id,0,work,0) == 0 );
        if(pthreadCreated)
            continue;
        else
            printf("\nError in creating threads");
    }

    pthread_mutex_lock(&lock);
    start=1;
    if(pthread_cond_broadcast(&cond) !=0 )
        printf("\nError in broadcasting");
    pthread_mutex_unlock(&lock);

    while(size >= 0)
        sleep(1);

    HistogramGroupInterval = (float)(max-min) / (float)TotalHistogramGroups;
    size=N;

    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
                                       
    while(size >= 0)
        sleep(1);

    pthread_join(id,&status);

    printHistogram(min, max, TotalHistogramGroups, histogram);

    pthread_mutex_destroy(&lock);                    

    return 0;
}                    
