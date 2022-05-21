//
// Created by chloeacm on 21.05.22.
//

#include "State.h"

State::State(string &s) {
    name = s;
}

bool State::transitionExists(string &s) {
    map<string,State*>::iterator it;
    it = nextStates.find(s);
    if (it != nextStates.end()) {
        return true;
    }
    else {
        return false;
    }
}

void State::newTransition(State *s) { // nieuwe transitie toevoegen
    nextStates[s->name] = s;
    transitions[s->name] = 1;
}

void State::addTransition(string &s) { // count + 1 voor bestaande transitie
    int count = transitions[s];
    transitions[s] = count + 1;
}