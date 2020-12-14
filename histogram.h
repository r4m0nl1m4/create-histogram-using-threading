
//Main for "histogram.h" C++ application
//Created by r4m0nl1m4 02/12/2020

//Guard
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//library(ies)
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include <random>
#include <vector>

/*
 * Normal random numbers generator - Marsaglia algorithm.
 */

std::vector<float> getGaussianDistribuition(int n, int mean){
    std::vector<float> distribution(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    float sample;
    for(int i=0; i<n; ++i)
    {
        std::normal_distribution<float> d(mean,2); 
        sample = d(gen);
        distribution[i] = sample;
    }
    return distribution;
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

void printVector(std::vector<float> a){ 
    printf("\nArray: ");   
    for(int i = 0; i < a.size(); ++i){
        printf("%.2f ", a[i]);
    }
    printf("\n");   
}

#endif