#!/bin/bash

g++ -std=c++11 -c first_MC_sim.cpp
g++ -std=c++11 -c main.cpp
g++ main.o first_MC_sim.o -o mc_walk_exe.out
