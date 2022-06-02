//
// Created by othma on 31/03/2022.
//

#include "TransitionDFA.h"

TransitionDFA::TransitionDFA() {}

const string &TransitionDFA::getInput() const {
    return input;
}

void TransitionDFA::setInput(const string &input) {
    TransitionDFA::input = input;
}

State *TransitionDFA::getName() const {
    return name;
}

void TransitionDFA::setName(State *name) {
    TransitionDFA::name = name;
}

State *TransitionDFA::getTo() const {
    return to;
}

void TransitionDFA::setTo(State *to) {
    TransitionDFA::to = to;
}
