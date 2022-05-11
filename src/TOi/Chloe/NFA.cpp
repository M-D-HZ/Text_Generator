//
// Created by chloeacm on 19.03.22.
//

#include "NFA.h"
#include "State.h"
#include <fstream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;

NFA::NFA(string s) {
    ifstream input(s);
    json j;
    input >> j;

    alphabet = j["alphabet"].get<vector<string>>();

    auto st = j["states"];
    int amount = st.size();
    for (int i=0; i<amount; i++) {
        State* stateke = new State;
        stateke->name = st[i]["name"];
        stateke->start = st[i]["starting"];
        stateke->accept = st[i]["accepting"];
        this->states.push_back(stateke);

        if (stateke->start) {
            vector<string> start; start.push_back(stateke->name);
            currentState = start;
            startState = stateke;
        }
    }

    auto tr = j["transitions"];
    amount = tr.size();
    for (int i=0; i<amount; i++) {
        string characterInput = tr[i]["input"];
        string start = tr[i]["from"];
        State* f = getState(start);
        pair<State*,string> combo; combo.first = f; combo.second = characterInput;
        string destination = tr[i]["to"];
        if (checkTransition(combo)) {
            vector<string> currentStates = transitionTable[combo];
            currentStates.push_back(destination);
            sort(currentStates.begin(), currentStates.end());
            transitionTable[combo] = currentStates;
        }
        else {
            vector<string> newState; newState.push_back(destination);
            transitionTable[combo] = newState;
        }
    }
}

State* NFA::getState(string &s) {
    for (State* stateke:states) {
        if (stateke->name == s) {
            return stateke;
        }
    }
}

bool NFA::checkTransition(const pair<State*, string>& combo) {
    auto i = transitionTable.find(combo);
    if (i != transitionTable.end()) {
        return true;
    }
    return false;
}


DFA NFA::toDFA() {
    DFA dfa;
    dfa.alphabet = alphabet;
    map<pair<State*,string>, vector<string>> dfaTable;

    bool allStatesDone = false;
    vector<string> tempStart = {startState->name};
    vector<string> current = tempStart;

    while (!allStatesDone) {
        for (auto &c:alphabet) {

            vector<string> trans;
            string name = createName(current);
            State* newState = dfa.getState(name);


            if (newState == nullptr) {
                newState = createState(current);
                if (dfa.startState->name == "" and current[0] == startState->name) {
                    newState->start = true;
                    dfa.startState = newState;
                    dfa.currentState = dfa.startState;
                }
                dfa.states.push_back(newState);
            }


            for (auto &s:current) {
                pair<State*,string>p; p.first = this->getState(s); p.second = c;
                auto i = transitionTable.find(p);
                if (i != transitionTable.end()) {
                    vector<string>statekes = transitionTable[p];
                    trans.insert(trans.end(), statekes.begin(), statekes.end());
                }
            }

            sort(trans.begin(), trans.end() );
            trans.erase( unique(trans.begin(), trans.end() ), trans.end() );
            pair<State*,string> combo; combo.first = newState; combo.second = c;
            dfaTable[combo] = trans;
            dfa.transitionTable[combo] = createName(trans);
        }

        allStatesDone = true;
        for (auto i = dfa.transitionTable.begin(); i != dfa.transitionTable.end(); i++) {
            if (dfa.getState(i->second) == nullptr) {
                allStatesDone = false;
                current = dfaTable[i->first];
                break;
            }
        }
    }
    return dfa;
}


State* NFA::createState(vector<string> &s) {
    State* st = new State;
    st->start = false;
    st->name = createName(s);
    for (int i=0; i<s.size(); i++) {
        State* state = getState(s[i]);
        if (state->accept) {
            st->accept = true;
        }
    }
    return st;
}

string NFA::createName(vector<string> &s) {
    string newName = "{";
    for (int i=0; i<s.size(); i++) {
        State* state = getState(s[i]);
        if (i != s.size()-1) {
            newName += state->name + ",";
        }
        else {
            newName += state->name + "}";
        }
    }
    return newName;
}





