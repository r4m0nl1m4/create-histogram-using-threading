
//Main for "histogram.h" C++ application
//Created by r4m0nl1m4 02/12/2020

//Guard
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//library(ies)
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include <random>
#include <string>
#include <vector>

void printVector(std::vector<int> a){ 
    printf("\nArray: ");   
    for(int i = 0; i < a.size(); ++i){
        printf("%d ", a[i]);
    }
    printf("\n");   
}

std::vector<int> getGaussianDistribuition(int n){
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(5,2); 
    std::vector<int> distributionVector(n);
    int p[10]={};
    int number;

    for(int i=0; i<n; ++i)
    {
        number = int(distribution(generator));
        if ((number>=0.0)&&(number<10.0)) ++p[number];
        distributionVector[i] = number;
    }
    //printVector(distributionVector);
    std::cout << std::endl;
    std::cout << "normal_distribution (5.0,2.0):" << std::endl;
    for (int i=0; i<10-1; ++i) {
        std::cout << i << "-" << (i+1) << ": " << p[i] << "\t" << std::string(p[i]*100/n,'*') << std::endl;
    }
    
    return distributionVector;
}

void printHistogram(std::vector<int> distribution, std::vector<int> histogram){
    std::cout << "\nnormal_distribution (5.0,2.0):" << std::endl;
    int qtd;
    std::cout << std::endl;
    for (int i=0; i<10; ++i) {
        qtd = (int) ( histogram[i]*100/distribution.size() );
        if(i<3){            
            std::cout << i << "-" << (i+1) << ": " << histogram[i] << "\t" << std::string(qtd,'*') << std::endl;
        }
        else if(i>3){
            std::cout << (i-1) << "-" << i << ": " << histogram[i] << "\t" << std::string(qtd,'*') << std::endl;
        }
    }
    std::cout << std::endl;
}

#endif