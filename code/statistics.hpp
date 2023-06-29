#include <iostream>
#include <cstdlib>
#include <time.h>
#include <utility>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <numeric>
#include </usr/local/include/boost/math/statistics/univariate_statistics.hpp>

using namespace std;
using namespace boost::math;

//https://www.boost.org/doc/libs/1_82_0/libs/math/doc/html/math_toolkit/univariate_statistics.html

class Stats {
    public:
        Stats(int thread_count, int N, int n, vector < vector < double > > falls);
        vector < vector < double > > m_falls;

        void Worker();

    private:
        double std_dev(vector < double > v);
        double confidence_level(vector < double > v);
        double average(vector < double > v);


        //constructor populated variables
        vector < double > t_average;
        vector < double > t_std_dev;
        double om_average; 
        double om_std_dev; 
        double om_probability;
        double om_total_falls;
        int m_thread_count;
        int m_n;
        int m_N;
};
