
#ifndef TAI2_DFA_H
#define TAI2_DFA_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "State.h"
#include "json.hpp"

using namespace std;
using namespace nlohmann;

class DFA {
private:
    string typeN;
    string epsilon;
    string eCurrentState;
    string eStartState;
    vector<State> eStatesUno;
    vector<vector<string>> eStatesDos;
    vector<State> eStatesTres;
    vector<string> eFinalStates;
    vector<string> eAlfabet;
    vector<string> DFAstartState;
    vector<map<string,string>> eTransitions;
    vector<map<string,vector<string>>> eTransitionsTwo;
    nlohmann::basic_json<> EStaten;

public:
    DFA(vector<map<string,string>>& eTransitionTwo, string& eStartStateUno, string& Epsilon, vector<string> &eAlfabetUno, vector<string>& finalStates);

    void print();

    vector<string> epsilonClosure(string &state, vector<map<string,string>> &transitions);

    vector<vector<string>> fullTransition(vector<string> &startStates, vector<map<string,string>> &transitions);

    vector<string> transitionInput(const string& iS, vector<string> &states, vector<map<string,string>> &transitions);
};

#endif //TAI2_DFA_H
