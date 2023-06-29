#include "statistics.hpp"

Stats::Stats(int thread_count, int N, int n, vector < vector < double > > falls) {
    m_thread_count = thread_count;
    m_N = N;
    m_n = n;
    m_falls = falls;
}

double Stats::average (vector < double > v) {
    return boost::math::statistics::mean(v);
}

double Stats::confidence_level(vector < double > v) {
    //https://www.boost.org/doc/libs/1_56_0/libs/math/doc/html/math_toolkit/stat_tut/weg/st_eg/tut_mean_intervals.html
    return 0.0;
}


double Stats::std_dev(vector < double > v) {
    double aux = boost::math::statistics::variance(v.cbegin(), v.cend());
    return sqrt(aux);
}

void Stats::Worker(){
    om_total_falls = 0.0;
    //calculate mean and std_dev for each thread
    for (int i = 0; i < m_thread_count; i++){
        t_average.push_back(average(m_falls[i]));
        t_std_dev.push_back(std_dev(m_falls[i]));
        om_total_falls = std::accumulate(m_falls[i].begin(), m_falls[i].end(), 0);
        
    }

    //calculate general mean and std_dev
    om_average = average(t_average);
    om_std_dev = std_dev(t_average);
    om_probability = 100.0*om_total_falls/(m_N*m_n);

    //plot general fall/sample iteration

    //output 
    cout << "\n\nBasic Stats (#/run)\n===================\nMean:\t" <<  om_average << "\nSigma:\t" <<  om_std_dev << endl;
    cout << "\n\nProbability of finding a hole: " << om_probability << " percent\n";
}



