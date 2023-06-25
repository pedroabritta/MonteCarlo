#include <iostream>
#include <cstdlib>
#include <time.h>
#include <utility>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <thread>
#include <unistd.h>
//need to add boost lib to accomodate for std dev

using namespace std;

#define NUMBER_OF_DIRECTIONS 8

//const variables
pair<int,int> position(0,0); //initial position -- never changes
int arguments_count = 4;

pair<int, int> current_position;

// varying variables 
int N; //samples
int n; //iterations
int radius; //half-side of square
int hole_count; // number of holes in square
//int thread_count; //number of threads used
vector < pair <int, int> > m_holes;


//void get_holes(vector < vector < int > > holes){
void get_holes(){
    pair <int, int> aux;
    int x, y, neg_x, neg_y; 
    for (int i = 0; i < hole_count; i++){
        neg_x = rand () % 2; neg_y = rand () % 2;
        x = rand () % radius; y = rand () % radius;
        if (neg_x) x = -1*x;
        if (neg_y) y = -1*y;
        aux.first = x; aux.second = y;
        m_holes[i] = aux;
        }
    }

bool in_hole(std::pair<int, int> current_pos){ //NEED TO OPTMIZE FIND -- as number of holes grow, this will escalate as N^2 -- use two?! unordered map?!
    for (int i = 0; i < 10; i++){
        if (m_holes[i].first == current_pos.first){
            if (m_holes[i].second == current_pos.second){
                return true;
            }
        }
    }
    return false;
}

int boundary(int position){
    if (position > radius){
        position -= (2*radius);
    }
    if (position < -1*radius){
        position += (2*radius);
    }
    return position;
}

std::pair<int, int> update_pos(std::pair<int, int> current_pos, int direction){
    switch (direction) {
        case 1: // this is north
            current_pos.second += 1;
            current_pos.second = boundary(current_pos.second);
            break;
        case 2: // this is northeast
            current_pos.first += 1;
            current_pos.first = boundary(current_pos.first);
            current_pos.second += 1;
            current_pos.second = boundary(current_pos.second);
            break;
        case 3: // this is east
            current_pos.first += 1;
            current_pos.first = boundary(current_pos.first);
            break;
        case 4: // this is southeast
            current_pos.first += 1;
            current_pos.first = boundary(current_pos.first);
            current_pos.second -= 1;
            current_pos.second = boundary(current_pos.second);
            break;
        case 5: // this is south
            current_pos.first -= 1;
            break;
        case 6: // this is southwest
            current_pos.first -= 1;
            current_pos.first = boundary(current_pos.first);
            current_pos.second -= 1;
            current_pos.second = boundary(current_pos.second);
            break;
        case 7: // this is west
            current_pos.first -= 1;
            current_pos.first = boundary(current_pos.first);
            break;
        case 8: // this is northwest
            current_pos.first -= 1;
            current_pos.first = boundary(current_pos.first);
            current_pos.second -= 1;
            current_pos.second = boundary(current_pos.second);
            break;
    }
    return current_pos;
}

int main(int argc, char* argv[])
{
    auto start = chrono::high_resolution_clock::now();
    cout << "starting arguments" << std::endl;
    //read in variables -- make sure they are correct
    try {
        if (argc != arguments_count + 1){
            printf("You have entered %d argument(s), and this program needs %d: \n \n   1 - \n   2 - \n   3 - \n   4 - \n\n\n", argc, arguments_count);
            throw std::runtime_error("Sorry! Review your entries and try again :) - The MC team\n");
        }
        N = stoi(argv[1]);
        n = stoi(argv[2]);
        radius = stoi(argv[3]);
        hole_count = stoi(argv[4]);
        //thread_count = stoi(argv[4]);

    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    //vector < int > falls;
    int fall_count;
    double total_falls = 0;
    m_holes.resize(hole_count);
    //falls.resize(N);

    // get holes
    srand(time(0)); // make it so that every different run generates differen numbers
    get_holes();
    float hole_fraction = float(hole_count)/(radius*radius);
    printf("Created %d holes successfully; Current holes/points is %.2f\n\n", hole_count, hole_fraction);

    for (int i = 0; i < N; i++){ //can divide this into several threads
        fall_count = 0;
        for (int j = 0; j < n; j++){
            //update position
            position = update_pos(position, rand() % NUMBER_OF_DIRECTIONS);
            //check if hole
            if (in_hole(position)) {
                fall_count += 1;
                //should we reset position to initial pos? 
            }
        }
        if (i%10 == 0) printf("Sample %d had %d falls\n", i, fall_count);
        total_falls += fall_count;
    }
    double probability = 100.0*total_falls/(float(N));
    probability = probability/float(n);
    auto finish = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    float exec_time = float(duration)/1000000.0;
    printf("The probability of finding a hole is %.6f percent\n", probability);
    printf("Execution took %.6f seconds\n", exec_time);
    return 0;
}

