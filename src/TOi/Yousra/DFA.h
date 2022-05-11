#include "Automata.h"

#ifndef TOI_2021_2022_DFA_H
#define TOI_2021_2022_DFA_H


class DFA : public Automata {
public:
    using Automata::Automata;
    explicit DFA(DFA dfa1, DFA dfa2, bool doorsnede);

    State* getDestination(State* from, string input);
    bool accepts(string input);
    void print();

    State* toState(pair<State*, State*> statepair, bool doorsnede);
    void combine(const string& newStatename, DFA &dfa1, DFA &dfa2, bool doorsnede);
    static vector<string> extractStates(const string& str);
};


#endif //TOI_2021_2022_DFA_H
