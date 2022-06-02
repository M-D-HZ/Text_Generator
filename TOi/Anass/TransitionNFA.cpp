//
// Created by othma on 31/03/2022.
//

#include "TransitionNFA.h"

TransitionNFA::TransitionNFA() {}

const string &TransitionNFA::getInput() const {
    return input;
}

void TransitionNFA::setInput(const string &input) {
    TransitionNFA::input = input;
}

const vector<State *> &TransitionNFA::getTo() const {
    return to;
}

void TransitionNFA::setTo(const vector<State *> &to) {
    TransitionNFA::to = to;
}

const vector<State *> &TransitionNFA::getFrom() const {
    return from;
}

void TransitionNFA::setFrom(const vector<State *> &from) {
    TransitionNFA::from = from;
}
