
//Main for "creates-a-histogramgram-with-a-normal-distribution" C++ application
//Created by r4m0nl1m4 02/12/2020

#include "histogram.h"
#include <pthread.h>
#include "report.h"

int N, size, start=0;
int min, max, nGroups;
float groupSize;
std::vector<int> histogram(11, 0);

pthread_mutex_t lock;
pthread_cond_t cond;

void * work(void * arg)
{
    std::vector<int>* data = (std::vector<int>*)arg;
    int i, temp;
    int distribution[data->size()];
    int count = 0;
    for (auto it : *data){
        distribution[count] = it;
        count++;
    }

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

        if(min>distribution[i])
            min=distribution[i];
        if(max<distribution[i])
            max=distribution[i];                   
    }

    for(;;){
        pthread_mutex_lock(&lock);
        i=size-1;
        size--;
        pthread_mutex_unlock(&lock);
        if(i<0)
            break;
        temp=(int)((distribution[i]-min))/groupSize;
        if(temp>(nGroups-1))
            temp=nGroups-1;
        if ((temp>=0.0)&&(temp<10.0)) ++histogram[temp];
    }
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t id;
    void * status;            
    int nThread;

    pthread_mutex_init(&lock,0);
    pthread_cond_init(&cond,0);

    N = atoi(argv[1]);
    nThread = atoi(argv[2]);
    nGroups = 10;

    std::vector<int> distribution = getGaussianDistribuition(N);

    size = distribution.size();
    min=max=distribution[0];
          
    for(int i=1; i<=nThread; i++){
        bool isCreated = (0==pthread_create(&id,0,work,&distribution)); 
        if(isCreated)
            continue;
        else
            printf("\nError in creating threads");
    }

    pthread_mutex_lock(&lock);
    start=1;
    bool isBlocked = (0!=pthread_cond_broadcast(&cond));
    if(isBlocked)
        printf("\nError in broadcasting");
    pthread_mutex_unlock(&lock);

    while(size>=0)
        sleep(1);

    groupSize=(float)(max-min)/(float)nGroups;
    size=N;

    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);

    while(size>=0)
        sleep(1);

    pthread_join(id,&status);

    printHistogram(distribution, histogram);

    pthread_mutex_destroy(&lock);                    

    return 0;
}                    