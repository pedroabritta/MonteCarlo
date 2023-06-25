#include "first_MC_sim.hpp"

bool in_hole(std::pair<int, int> current_pos){ //NEED TO OPTMIZE FIND -- as number of holes grow, this will escalate as N^2 -- use two?! unordered map?!
    for (int i = 0; i < 10; i++){
        if (m_holes[i][0] == current_pos.first){
            if (m_holes[i][1] == current_pos.second){
                return true;
            }
        }
    }
    return false;
}

int boundary(int position){
    if (position > limit){
        position -= (2*limit);
    }
    if (position < -1*limit){
        position += (2*limit);
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

