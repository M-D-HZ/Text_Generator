#ifndef DFA_TRANSITIONDFA_H
#define DFA_TRANSITIONDFA_H
#include <iostream>
#include "map"
#include "vector"
#include "set"
#include "State.h"

using namespace std;

class TransitionDFA {
    State* name;
    State* to;
    string input;
public:
    TransitionDFA();

    State *getName() const;

    void setName(State *name);

    State *getTo() const;

    void setTo(State *to);

    const string &getInput() const;

    void setInput(const string &input);
};


#endif //DFA_TRANSITIONDFA_H
