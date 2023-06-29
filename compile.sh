#!/bin/bash

g++ -std=c++20 -c first_MC_sim.cpp
g++ -std=c++20 -c statistics.cpp
g++ -std=c++20 -c main.cpp
g++ main.o statistics.o first_MC_sim.o -o mc_walk_exe.out
