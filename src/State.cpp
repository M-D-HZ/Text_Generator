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