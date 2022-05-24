
#ifndef TAI2_STATE_H
#define TAI2_STATE_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"

using namespace std;

class State {
public:
    vector<string> name;
    bool start = false;
    bool final = false;
    vector<pair<string,string>> stateTransitions;
};


#endif //TAI2_STATE_H
