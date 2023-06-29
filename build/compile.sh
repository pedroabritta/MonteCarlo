#!/bin/bash

g++ -std=c++20 -c ../code/first_MC_sim.cpp
g++ -std=c++20 -c ../code/statistics.cpp
g++ -std=c++20 -c ../code/main.cpp
g++ main.o statistics.o first_MC_sim.o -o ../mc_walk_exe.out
rm *.o
