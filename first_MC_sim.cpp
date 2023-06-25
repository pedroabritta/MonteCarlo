// Parallelized solution to walking panda problem
#include "first_MC_sim.hpp"

//constructor
MC_run::MC_run(int N, int n, int radius, int hole_count, int thread_number){
            m_N = N;
            m_n = n;
            m_radius = radius;
            m_position = make_pair(0,0); //always start at initial position
            m_hole_count = hole_count;
            m_thread_number = thread_number;
            m_holes.resize(hole_count);
        }

//destructor
//MC_run::~MC_run(){}

void MC_run::get_holes(){
    float hole_fraction = float(m_hole_count)/(m_radius*m_radius);
    //cout << "Creating " << m_hole_count << " holes; Will have hole fraction is " << hole_fraction;
    pair <int, int> aux;
    int x, y, neg_x, neg_y;
    for (int i = 0; i < m_hole_count; i++){
        neg_x = rand () % 2; neg_y = rand () % 2;
        x = rand () % m_radius; y = rand () % m_radius;
        if (neg_x) x = -1*x;
        if (neg_y) y = -1*y;
        aux.first = x; aux.second = y;
        m_holes[i] = aux;
        }
    //cout << "Created " << m_hole_count << " holes successfully; Current holes/points is " << hole_fraction << endl;
    }

bool MC_run::in_hole(){ //NEED TO OPTMIZE FIND -- as number of holes grow, this will escalate as N^2 -- use two?! unordered map?!
    for (int i = 0; i < 10; i++){
        if (m_holes[i].first == m_position.first){
            if (m_holes[i].second == m_position.second){
                return true;
            }
        }
    }
    return false;
}

int MC_run::boundary(int coordinate){
    if (coordinate > m_radius){
        coordinate -= (2*m_radius);
    }
    if (coordinate < -1*m_radius){
        coordinate += (2*m_radius);
    }
    return coordinate;
}

void MC_run::update_pos(int direction){
    switch (direction) {
        case 1: // this is north
            m_position.second += 1;
            m_position.second = boundary(m_position.second);
            break;
        case 2: // this is northeast
            m_position.first += 1;
            m_position.first = boundary(m_position.first);
            m_position.second += 1;
            m_position.second = boundary(m_position.second);
            break;
        case 3: // this is east
            m_position.first += 1;
            m_position.first = boundary(m_position.first);
            break;
        case 4: // this is southeast
            m_position.first += 1;
            m_position.first = boundary(m_position.first);
            m_position.second -= 1;
            m_position.second = boundary(m_position.second);
            break;
        case 5: // this is south
            m_position.first -= 1;
            break;
        case 6: // this is southwest
            m_position.first -= 1;
            m_position.first = boundary(m_position.first);
            m_position.second -= 1;
            m_position.second = boundary(m_position.second);
            break;
        case 7: // this is west
            m_position.first -= 1;
            m_position.first = boundary(m_position.first);
            break;
        case 8: // this is northwest
            m_position.first -= 1;
            m_position.first = boundary(m_position.first);
            m_position.second -= 1;
            m_position.second = boundary(m_position.second);
            break;
    }
}

double MC_run::Worker(){
    get_holes();
    int fall_count;
    double total_falls = 0.0;
    for (int i = 0; i < m_N; i++){ //can divide this into several threads
        fall_count = 0;
        for (int j = 0; j < m_n; j++){
            //update position
            update_pos(rand() % NUMBER_OF_DIRECTIONS);
            //check if hole
            if (in_hole()) {
                fall_count += 1;
                //should we reset position to initial pos? 
            }
        }
        total_falls += fall_count;
    }
    cout << "Thread " << m_thread_number << " had total of " << total_falls << " falls\n";
    return total_falls;
}