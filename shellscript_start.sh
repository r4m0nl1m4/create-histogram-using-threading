#!/bin/bash

# To run on terminal: ./shellscript_start.sh

rm creates-a-histogram-with-a-normal-distribution1

g++ -std=c++11 creates-a-histogram-with-a-normal-distribution1.cpp -o creates-a-histogram-with-a-normal-distribution1 -lpthread

./creates-a-histogram-with-a-normal-distribution1 40

#10000000