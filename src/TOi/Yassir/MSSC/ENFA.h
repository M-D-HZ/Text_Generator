
#ifndef TAI2_ENFA_H
#define TAI2_ENFA_H


#include "json.hpp"
#include "State.h"
#include <string>
#include <vector>
#include <set>
#include "DFA.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace nlohmann;

class State;
class ENFA {
private:
    string typeN;
    string epsilon;
    vector<State> eStatesUno;
    string eCurrentState;
    string eStartState;
    vector<string> eFinalStates;
    vector<string> eAlfabet;
    vector<map<string,string>> eTransitions;
    nlohmann::basic_json<> EStaten;

public:
    explicit ENFA(const string& filename);

    DFA toDFA();
};


#endif //TAI2_ENFA_H
