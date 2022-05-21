//
// Created by chloeacm on 21.05.22.
//

#include "MarkovChain.h"

// Empty constructor
MarkovChain::MarkovChain() = default;

// Train Markov chain constructor (parse txt file)
MarkovChain::MarkovChain(string &filename) {

}


// check if state already exists
// 2. exists: add to transitions of previous word (state)
// 3. doesn't exist: make new state + add to transitions of previous word + add to states of markovchain

bool MarkovChain::wordExists(string &s) {
    map<string,State*>::iterator it;
    it = states.find(s);
    if (it != states.end()) {
        return true;
    }
    else {
        return false;
    }
}

void MarkovChain::addWord(State *s) {
    states[s->name] = s;
}