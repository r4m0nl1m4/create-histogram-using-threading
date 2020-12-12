#!/bin/bash

# To run on terminal: ./shellscript_start.sh

g++ -std=c++11 creates-a-histogram-with-a-normal-distribution.cpp -o creates-a-histogram-with-a-normal-distribution -lpthread

./creates-a-histogram-with-a-normal-distribution 10000000