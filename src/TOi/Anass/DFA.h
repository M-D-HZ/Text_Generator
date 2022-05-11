//
// Created by othma on 24/02/2022.
//

#ifndef DFA_DFA_H
#define DFA_DFA_H
#include <iostream>
#include "map"
#include "vector"
#include "State.h"
#include "TransitionDFA.h"
#include "TransitionNFA.h"

using namespace std;

class DFA {
    vector<string> alphabet;
    vector<State*> States;
    vector<TransitionDFA*> Transitions;
    set<pair<State*,State*>> NewStates;
    set<TransitionNFA*> NewTrans;
    State* CurrentState;
public:
    DFA(string file);
    DFA();
    DFA(DFA dfa1,DFA dfa2,bool versie);
    State *getCurrentState() const;
    void addState(State* s);
    void addTrans(TransitionDFA* t);
    void setCurrentState(State *currentState);
    bool checkExistance(TransitionNFA* T);
    const vector<State *> &getStates() const;
    const vector<string> &getAlphabet() const;
    State* GetState(string statename);
    void setAlphabet(const vector<string> &alphabet);
    bool checkAlphabet(string k);
    void move(string k);
    bool accepts(string input);
    void print();
    bool checkAccepting(pair<State*,State*> S, bool versie);
    bool checkStarting(pair<State*,State*> S);

    };
#endif //DFA_DFA_H
