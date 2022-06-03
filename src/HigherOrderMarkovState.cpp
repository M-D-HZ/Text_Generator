#include "HigherOrderMarkovState.h"

const string &HigherOrderMarkovState::getName() const {
    return name;
}

void HigherOrderMarkovState::setName(const string &name) {
    HigherOrderMarkovState::name = name;
}

const map<vector<HigherOrderMarkovState *>, map<double, set<HigherOrderMarkovState *>>> &
HigherOrderMarkovState::getTransitions() const {
    return transitions;
}

void HigherOrderMarkovState::setTransitions(
        const map<vector<HigherOrderMarkovState *>, map<double, set<HigherOrderMarkovState *>>> &transitions) {
    HigherOrderMarkovState::transitions = transitions;
}

HigherOrderMarkovState::HigherOrderMarkovState(string &word) {
    name = word;
}
