
//Main for "histogram.h" C++ application
//Created by r4m0nl1m4 02/12/2020

//Guard
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//library(ies)
#include <stdio.h>
#include <math.h>
#include <cstdio>

/*
 * Normal random numbers generator - Marsaglia algorithm.
 */

int* generateGaussRandomArray(int n)
{
    int i;
    int m = n + n % 2;
    int* values = (int*)calloc(m,sizeof(int));
    int average, deviation;
 
    if ( values )
    {
        for ( i = 0; i < m; i += 2 )
        {
            double x,y,rsq,f;
            do {
                x = 2.0 * rand() / (double)RAND_MAX - 1.0;
                y = 2.0 * rand() / (double)RAND_MAX - 1.0;
                rsq = x * x + y * y;
            }while( rsq >= 1. || rsq == 0. );
            f = sqrt( -2.0 * log(rsq) / rsq );
            values[i]   = (int) (x * f);
            values[i+1] = (int) (y * f);
        }
    }
    return values;
}

int* getRandomArrayByTerminal(int *argc, const char **argv){
    int size = *argc-1;
    int *array  = (int*)calloc( size, sizeof(int) );
    array = generateGaussRandomArray(size);
    return array;
}

void printHistogram(int temp1, int temp2, float TotalHistogramGroups, int* histogram){
    float HistogramGroupInterval = (float)(temp2-temp1) / (float)TotalHistogramGroups;
    printf("\nThe histogram is as follows: \n");
    for(int i=0; i<TotalHistogramGroups; i++)
    {
        if(i!=TotalHistogramGroups-1)
        {
            printf("For %d -> %d = %d\n",temp1, temp2,histogram[i]);
            temp1 = temp2+1;
            temp2 += ceil(HistogramGroupInterval);
        }
        else
            printf("For %d and up values = %d ",temp1, histogram[i]);
    }
    printf("\n");
}

int getThreadsNumber(){
	int nThread;
    printf("\nEnter the total number of threads: ");
    scanf("%d", &nThread);
    return nThread;
}

#endif