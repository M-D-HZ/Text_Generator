//
// Created by chloeacm on 21.05.22.
//

#ifndef TOG_TXT_GENERATOR_STATE_H
#define TOG_TXT_GENERATOR_STATE_H

#include <string>
#include <map>
using namespace std;


class State {
public:
    string name;
    map<string,State*> nextStates;
    map<string, int> transitions;
    State(string& s);
    bool transitionExists(string &s);
    void newTransition(State* s);
    void addTransition(string &s)
};


#endif //TOG_TXT_GENERATOR_STATE_H
