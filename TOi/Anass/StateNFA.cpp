//
// Created by othma on 29/03/2022.
//

#include "StateNFA.h"

StateNFA::StateNFA() {}

StateNFA::StateNFA(const string &name, const set<string> &to, const string &input) : name(name), to(to), input(input) {}

const string &StateNFA::getName() const {
    return name;
}

void StateNFA::setName(const string &name) {
    StateNFA::name = name;
}

const set<string> &StateNFA::getTo() const {
    return to;
}

void StateNFA::setTo(const set<string> &to) {
    StateNFA::to = to;
}

const string &StateNFA::getInput() const {
    return input;
}

void StateNFA::setInput(const string &input) {
    StateNFA::input = input;
}

bool StateNFA::isAccepting() const {
    return Accepting;
}

void StateNFA::setAccepting(bool accepting) {
    Accepting = accepting;
}

bool StateNFA::isStarting() const {
    return Starting;
}

void StateNFA::setStarting(bool starting) {
    Starting = starting;
}

void StateNFA::addTo(string TO) {
    to.insert(TO);

}
