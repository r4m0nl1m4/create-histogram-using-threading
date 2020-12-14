
//Main for "creates-a-histogramgram-with-a-normal-distribution" C++ application
//Created by r4m0nl1m4 02/12/2020

#include "histogram.h"
#include <pthread.h>
#include "report.h"

int N, size;
int min, max, nGroups;
float groupSize;
int histogram[50];
int start=0;
pthread_mutex_t lock;
pthread_cond_t cond;

void * work(void * arg)
{
    std::vector<float>* data = (std::vector<float>*)arg;
    int i, temp;
    float a[data->size()];
    int count = 0;
    for (auto it : *data){
        a[count] = it;
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
        if(size<0)
        {
            pthread_mutex_lock(&lock);
            pthread_cond_wait(&cond, &lock);
            pthread_mutex_unlock(&lock);
        }
        if(i<0)
            break;
        if(min>a[i])
            min=a[i];
        if(max<a[i])
            max=a[i];                   
    }

    for(;;){
        pthread_mutex_lock(&lock);
        i=size-1;
        size--;
        pthread_mutex_unlock(&lock);
        if(i<0)
            break;
        temp=(float)((a[i]-min))/groupSize;
        if(temp >(nGroups-1))
            temp= nGroups-1;
        histogram[temp]++;
    }
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t id;
    void * status;            
    int nThread;
    int temp1, temp2;

    pthread_mutex_init(&lock,0);
    pthread_cond_init(&cond,0);

    N = atoi(argv[1]);
    nGroups = 10;
    std::vector<float> a = getGaussianDistribuition(N, nGroups);
    printVector(a);

    N = a.size();
    size = N;
    min=max=a[0];

    for(int i=0; i<nGroups; i++)
        histogram[i]=0;

    nThread = nGroups;                 
    for(int i=0; i<nThread; i++)
    {
        if(0==pthread_create(&id,0,work,&a))
            continue;
        else
            printf("\nError in creating threads");
    }

    pthread_mutex_lock(&lock);
    start=1;
    if(0!=pthread_cond_broadcast(&cond))
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

    printf("\nThe histogram is as follows:\n");
    temp1=min;
    temp2=ceil(groupSize);

    for(int i=0; i<nGroups; i++)
    {
        if(i!=nGroups-1)
        {
            printf("For %d->%d = %d\n",temp1, temp2,histogram[i]);
            temp1=temp2+1;
            temp2+=ceil(groupSize);
        }
        else
            printf("For %d and up values = %d ",temp1, histogram[i]);
    }

    pthread_mutex_destroy(&lock);                    

    printf("\n");

    return 0;
}                    