#ifndef DFA_STATENFA_H
#define DFA_STATENFA_H
#include <iostream>
#include "map"
#include "vector"
#include "set"

using namespace std;

class StateNFA {
    string name;
    set<string> to;
    string input;
    bool Accepting = false;
    bool Starting = false;
public:
    StateNFA();

    StateNFA(const string &name, const set<string> &to, const string &input);

    const string &getName() const;

    void setName(const string &name);

    const set<string> &getTo() const;

    void setTo(const set<string> &to);

    void addTo(string TO);

    const string &getInput() const;

    void setInput(const string &input);

    bool isAccepting() const;

    void setAccepting(bool accepting);

    bool isStarting() const;

    void setStarting(bool starting);
};


#endif //DFA_STATENFA_H
