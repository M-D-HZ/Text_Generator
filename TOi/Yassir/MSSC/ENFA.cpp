#include "ENFA.h"


ENFA::ENFA(const string &filename) {
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error opening file" << endl;
    }
    json j;
    input >> j;

    string type = j["type"]; typeN = type;
    vector<string> alfabet = j["alphabet"]; eAlfabet = alfabet;
    epsilon = j["eps"];
    auto states = j["states"]; EStaten = states;
    vector<map<string,string>> transitions = j["transitions"]; eTransitions = transitions;

    for(auto & state : states) {
        string stateName = state["name"];
        State newState;
        newState.name.push_back(stateName);
        if (state["accepting"] == true) {
            eFinalStates.push_back(stateName);
            newState.final = true;
        }
        if (state["starting"] == true) {
            eCurrentState = stateName;
            eStartState = stateName;
            newState.start = true;
        }
        for (auto & transition : transitions) {
            if (transition["from"] == newState.name[0]) {
                newState.stateTransitions.emplace_back(transition["input"], transition["to"]);
            }
        }
        eStatesUno.push_back(newState);
    }
}

DFA ENFA::toDFA() {
    DFA dfa(eTransitions, eStartState, epsilon, eAlfabet, eFinalStates);
    return dfa;
}