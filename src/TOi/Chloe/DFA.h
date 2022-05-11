//
// Created by chloeacm on 01.04.22.
//

#ifndef TOI_CHLOE_DFA_H
#define TOI_CHLOE_DFA_H

class State;


using namespace std;
#include <string>
#include <vector>
#include <map>
#include "RE.h"

class RE;

class DFA {
public:
    DFA();
    DFA(string s);
    DFA(DFA A, DFA B, bool doorsnede);
    bool accepts(const char* s);
    void print();
    State* getState(string &s);
    vector<string> alphabet;
    vector<State*> states;
    map<pair<State*,string>, string> transitionTable;
    map<pair<string,string>,string> regexTransitions;
    bool transition(const pair<State*,string>& combo);
    bool checkCharacter(string &c);
    State* currentState;
    State* startState;
    RE toRE();
    string stateElimination(int &i, int &j, int &k, vector<string> &state);
    string findLoop(string &state);
    State* createState(State* A, State* B, bool &doorsnede);
    string createName(State* A, State* B);

};


#endif //TOI_CHLOE_DFA_H
