#include <mutex>
#include "first_MC_sim.hpp"

std::mutex mtx;

int main(int argc, char* argv[])
{
    auto start = chrono::high_resolution_clock::now();
    srand(time(0));
    int hole_count, N, n, radius, thread_count;
    //read in variables -- make sure they are correct
    try {
        if (argc != ARG_COUNT + 1){
            //printf("You have entered %d argument(s), and this program needs %d: \n \n   1 - \n   2 - \n   3 - \n   4 - \n\n\n", argc, ARG_COUNT);
            throw std::runtime_error("Sorry! You have entered the wrong number of arguments. Review your entries and try again :) - The MC team\n");
        }
        N = stoi(argv[1]);
        n = stoi(argv[2]);
        radius = stoi(argv[3]);
        hole_count = stoi(argv[4]);
        thread_count = stoi(argv[5]);

    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    //parallelization variables
    std::vector< std::thread > threads;
    vector < MC_run > runs;
    vector < double > final_probability(thread_count);
    int N_prime;
    bool set_up = true;
    while(set_up){
        if (N%thread_count == 0) {
            N_prime = N/thread_count;
            set_up = false;
        }
        else {
            cout << "Need to change N; increasing it by 1\n";
            N++;
        }
    }
    cout << "Performing MC simulation for " << N << " samples\n";
    
    for (int i = 0; i < thread_count; ++i) {
            runs.emplace_back(N_prime, n, radius, hole_count, i);
    }

    for (size_t i = 0; i < runs.size(); ++i) {
            threads.emplace_back([&runs, &final_probability, i]() { final_probability[i] = runs[i].Worker(); });
    }

    // Join the threads
    for (auto& thread : threads) {
        thread.join();
    }
    cout << "\n\n";
    double value = 0.0;
    for (int i = 0; i < final_probability.size(); i++) {
        value += 100.0*final_probability[i]/(N_prime*n);
        cout << "Sample " << i << " had "  << final_probability[i] << " falls\n";
    }
    cout << "\n\nProbability of finding a hole: " << value << " percent\n";
    auto finish = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    float exec_time = float(duration)/1000000.0;
    cout << "Execution took " << exec_time << " seconds\n";

    return 0;
}