//
// Created by chloeacm on 19.03.22.
//

#ifndef TOI_CHLOE_NFA_H
#define TOI_CHLOE_NFA_H

#include <string>
#include <vector>
using namespace std;

#include "DFA.h"

class NFA {
public:
    vector<string> alphabet;
    vector<State*> states;
    map<pair<State*,string>,vector<string>> transitionTable;
    vector<string> currentState;
    State* getState(string &s);
    bool checkTransition(const pair<State*,string>& combo);
    State* startState;
    State* createState(vector<string> &s);
    string createName(vector<string> &s);
    NFA(string s);
    DFA toDFA();



};


#endif //TOI_CHLOE_NFA_H
