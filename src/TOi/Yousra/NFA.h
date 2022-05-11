#include "DFA.h"

#ifndef TOI_2021_2022_NFA_H
#define TOI_2021_2022_NFA_H


class NFA : public Automata {
public:
    using Automata::Automata;

    States extractStates(string str);

    void createSubsets(const string& newStatename, States &dfaStates, Transitions &dfaTransitions);
    DFA toDFA();
    States getDestinations(State* from, string input);
    bool accepts(string input);
    void print();

    State toState(States states);
};


#endif //TOI_2021_2022_NFA_H
