//
// Created by chloeacm on 01.04.22.
//

#include <iostream>
#include <fstream>
#include "DFA.h"
#include <iomanip>
#include "json.hpp"
#include "State.h"
#include "RE.h"

using json = nlohmann::json;

DFA::DFA() {
    currentState = new State;
    startState = new State;
}

DFA::DFA(string s) {
    ifstream input(s);
    json j;
    input >> j;

    alphabet = j["alphabet"].get<vector<string>>();

    auto states = j["states"];
    int amount = states.size();
    for (int i=0; i<amount; i++) {
        State* stateke = new State{};
        stateke->name = states[i]["name"];
        stateke->start = states[i]["starting"];
        stateke->accept = states[i]["accepting"];
        this->states.push_back(stateke);

        if (stateke->start) {
            currentState = stateke;
            startState = stateke;
        }
    }

    auto transitions = j["transitions"];
    amount = transitions.size();
    for (int i=0; i<amount; i++) {
        string characterInput = transitions[i]["input"];
        State* f = nullptr;
        string t;
        for (State* stateke:this->states) {
            if (stateke->name == transitions[i]["from"]) {
                f = stateke;
            }
            if (stateke->name == transitions[i]["to"]) {
                t = stateke->name;
            }
        }
        pair<State*,string>combo; combo.first = f; combo.second = characterInput;
        transitionTable[combo] = t;
    }
}

bool DFA::checkCharacter(string &c) {
    if (find(alphabet.begin(), alphabet.end(), c) != alphabet.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool DFA::transition(const pair<State*,string>& combo) {
    if (transitionTable.find(combo) != transitionTable.end()) {
        currentState = getState(transitionTable[combo]);
        return true;
    }
    else {
        return false;
    }
}

State* DFA::getState(string &s) {
    State* ss = nullptr;
    for (auto &state:states) {
        if (state->name == s) {
            ss = state;
        }
    }
    return ss;
}

bool DFA::accepts(const char* s) {
    string input = s;
    for (char &c:input) {
        string C; C.push_back(c);
        if (checkCharacter(C)) {
            pair<State*,string> p; p.first = currentState; p.second = C;
            transition(p);
        }
        else {
            return false;
        }
    }

    if (currentState->accept) {
        return true;
    }
    else {
        return false;
    }
}

void DFA::print() {
    vector<json>st;
    for (auto s:this->states) {
        json jk = {
                {"name", s->name},
                {"starting", s->start},
                {"accepting", s->accept},
        };
        st.push_back(jk);
    }

    vector<json>tr;
    for (auto &t:this->transitionTable) {
        json jt = {
                {"from", t.first.first->name},
                {"to", t.second},
                {"input", t.first.second}
        };
        tr.push_back(jt);
    }

    json j = {
            {"type", "DFA"},
            {"alphabet", this->alphabet},
            {"states", st},
            {"transitions", tr}
    };

    cout << setw(4) << j << endl;
}

RE DFA::toRE() {

    RE path;


    for (auto &tr:transitionTable) {
        string regex;
        pair<string,string>p;
        p.first = tr.first.first->name;
        p.second = tr.second;
        auto i = regexTransitions.find(p);
        if (i == regexTransitions.end()) {
            regex = tr.first.second;
        }
        else {
            regex = regexTransitions[p] + "+" + tr.first.second;
        }
        regexTransitions[p] = regex;
    }

    vector<int>finalStates;
    vector<string>allStates;
    for (auto &s:states) {
        allStates.push_back(s->name);
    }
    sort(allStates.begin(),allStates.end());

    for (int i = 0; i < allStates.size(); i++) {
        if (getState(allStates[i])->accept) {
            finalStates.push_back(i);
        }
    }

    vector<pair<string,string>> visited;


    for (auto &f:finalStates) {
        RE p;
        int I = 0;
        int J = f;
        int K = allStates.size()-1;
        p.R = stateElimination(I,I,K,allStates);
        p.S = stateElimination(I,J,K,allStates);
        p.T = stateElimination(J,I,K,allStates);
        p.U = stateElimination(J,J,K,allStates);

        if (p.U.empty() and p.S == p.T) {
            string samen = p.S + p.T;
            if (p.R == samen) {
                p.T = "";
            }
        }

        if (path.S.empty()) {
            path.S = p.createString();
        }
        else {
            path.S += "+" + p.createString();
        }
    }
    return path;
}


string DFA::stateElimination(int &i, int &j, int &k, vector<string> &state) {
    string regex;
    int m = k-1;
    string partOne; string partTwo; string partThree; string partFour;
    if (k >= 1) {
        partOne = stateElimination(i,j,m,state);
        partTwo = stateElimination(i,k,m,state);
        partThree = findLoop(state[k]);
        partFour = stateElimination(k,j,m,state);
        int index = partOne.find('+');
        if (index > 0 and index < partOne.size()) {
            char start = partOne[0];
            char end = partOne[partOne.size()-1];
            if (start != '(' and end != ')') {
                partOne = "(" + partOne + ")";
            }

        }
        if (!partTwo.empty()) {
            index = partTwo.find('+');
            if (index > 0 and index < partTwo.size()) {
                char start = partTwo[0];
                char end = partTwo[partTwo.size()-1];
                if (start != '(' and end != ')') {
                    partTwo = "(" + partTwo + ")";
                }

            }
            if (partThree.size() == 1) {
                partThree += "*";
            }
            else if (partThree.size() > 1) {
                char start = partThree[0];
                char end = partThree[partThree.size()-1];
                if (start != '(' and end != ')') {
                    partThree = "(" + partThree + ")*";
                }
                else {
                    partThree += "*";
                }
            }
            index = partFour.find('+');
            if (index > 0 and index < partFour.size()) {
                char start = partFour[0];
                char end = partFour[partFour.size()-1];
                if (start != '(' and end != ')') {
                    partFour = "(" + partFour + ")";
                }
            }
        }
        if (j == k and !partOne.empty()) {
            regex = partOne;
        }
        else if (j == k and partOne.empty()) {
            regex = "";
        }
        else if (i == k and !partOne.empty()) {
            regex = partOne;
        }
        else if (i == k and partOne.empty()) {
            regex = "";
        }
        else if (!partOne.empty() and !partTwo.empty() and !partFour.empty()) {
            regex = partOne + "+" + partTwo + partThree + partFour;
        }
        else if (!partOne.empty() and !partTwo.empty() and partFour.empty()) {
            regex = partOne;
        }
        else if (!partOne.empty() and partTwo.empty()) {
            regex = partOne;
        }
        else if (partOne.empty() and !partTwo.empty() and !partFour.empty()) {
            regex = partTwo + partThree + partFour;
        }
        else if (partOne.empty() and partTwo.empty()) {
            regex = "";
        }
        else if (partOne.empty() and partFour.empty()) {
            regex = "";
        }
    }
    else { // k-1 == 0, aka startState
        pair<string,string>p; p.first = state[i]; p.second = state[j];
        regex = regexTransitions[p];
    }

    return regex;
}

string DFA::findLoop(string &state) {
    pair<string,string>p; p.first = state; p.second = state;
    string regex = regexTransitions[p];
    return regex;
}

DFA::DFA(DFA A, DFA B, bool doorsnede) {
    alphabet = A.alphabet;
    startState = createState(A.startState, B.startState, doorsnede);
    currentState = startState;
    map<pair<State*,string>, pair<string,string>> table;
    pair<string,string> current; current.first = A.startState->name; current.second = B.startState->name;
    bool allStatesDone = false;
    while (!allStatesDone) {
        State* stateA = A.getState(current.first); State* stateB = B.getState(current.second);
        State* nieuwState = createState(stateA,stateB,doorsnede);
        states.push_back(nieuwState);
        for (auto &c:alphabet) {
            pair<State*,string>p; p.first = stateA; p.second = c;
            string transitieA = A.transitionTable[p];
            p.first = stateB;
            string transitieB = B.transitionTable[p];
            pair<string,string> newPair; newPair.first = transitieA; newPair.second = transitieB;
            State* newState = createState(A.getState(transitieA), B.getState(transitieB), doorsnede);
            string name = createName(stateA,stateB);
            State* currentS = getState(name);
            p.first = currentS; p.second = c;
            transitionTable[p] = newState->name;
            table[p] = newPair;
        }

        allStatesDone = true;
        for (auto i=transitionTable.begin(); i != transitionTable.end(); i++) {
            if (getState(i->second) == nullptr) {
                allStatesDone = false;
                current = table[i->first];
            }
        }
    }

}

State* DFA::createState(State* A, State* B, bool &doorsnede) {
    State* p = new State;
    p->name = createName(A,B);
    if (doorsnede and A->accept and B->accept) {
        p->accept = true;
    }
    else if (!doorsnede and (A->accept or B->accept)) {
        p->accept = true;
    }
    if (A->start and B->start) {
        p->start = true;
    }
    return p;
}

string DFA::createName(State* A,State* B) {
    string name = "(" + A->name + "," + B->name + ")";
    return name;
}