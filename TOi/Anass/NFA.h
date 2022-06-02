#ifndef DFA_NFA_H
#define DFA_NFA_H
#include <iostream>
#include "map"
#include "vector"
#include "DFA.h"
#include "set"
#include "State.h"
#include "TransitionNFA.h"

using namespace std;

class NFA {
    vector<string> alphabet;
    vector<State*> States;
    set<TransitionDFA*> Transitions;
    set<TransitionNFA*> NewTrans;
    set<State*> CurrentState;
    set<set<State*>> NewStates;
public:
    NFA(string filename);
    bool checkAlphabet(string k);
    set<State*> move(set<State*> S, string A);
    State* GetState(string statename);
    bool checkExistance(TransitionNFA* T);
    bool checkAccepting(set<State*> S);
    bool checkStarting(set<State*> S);
    DFA toDFA();
};


#endif //DFA_NFA_H
