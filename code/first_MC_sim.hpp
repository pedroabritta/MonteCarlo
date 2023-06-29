#include <iostream>
#include <cstdlib>
#include <time.h>
#include <utility>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <thread>
#include <unistd.h>

using namespace std;

#define NUMBER_OF_DIRECTIONS 8
#define ARG_COUNT 5
#define INIT_POS (0 , 0)

class MC_run {
    public:
        MC_run(int N, int n, int radius, int hole_count, int thread_number);

        //public functions
        //double Worker();
        //void Worker();
        vector < double > Worker();

    private:
        //constructor populated variables
        int m_N; //samples
        int m_n; //iterations
        int m_radius; //half-side of square
        int m_hole_count; // number of holes in square

        //assisting variables
        int m_thread_number;
        pair<int,int> m_position;
        vector < pair <int, int> > m_holes;
        vector < double > falls;
        //std::mutex resultMutex;

        //functions
        bool in_hole();
        int boundary(int coordinate);
        void update_pos(int direction);
        void get_holes();
};