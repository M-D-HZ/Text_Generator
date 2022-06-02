#ifndef DFA_TRANSITIONNFA_H
#define DFA_TRANSITIONNFA_H
#include <iostream>
#include "map"
#include "vector"
#include "set"
#include "State.h"


using namespace std;


class TransitionNFA {
    vector<State*> from;
    vector<State*> to;
    string input;
public:
    TransitionNFA();


    const vector<State *> &getFrom() const;

    void setFrom(const vector<State *> &from);

    const vector<State *> &getTo() const;

    void setTo(const vector<State *> &to);

    const string &getInput() const;

    void setInput(const string &input);
};


#endif //DFA_TRANSITIONNFA_H
