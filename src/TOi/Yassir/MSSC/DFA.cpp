
#include "DFA.h"

DFA::DFA(vector<map<string, string>> &eTransitionTwo, string &eStartStateUno, string &Epsilon, vector<string> &eAlfabetUno,
         vector<string> &finalStates) {
    epsilon = Epsilon;
    eAlfabet = eAlfabetUno;
    eTransitions = eTransitionTwo;
    eStartState = eStartStateUno;
    eFinalStates = finalStates;
    DFAstartState = epsilonClosure(eStartState, eTransitions);

    State startState;
    startState.name = DFAstartState;
    startState.start = true;
    eStatesUno.push_back(startState);
    eStatesDos.push_back(DFAstartState);
    vector<vector<string>> newStates = fullTransition(DFAstartState, eTransitions);

    while (!newStates.empty()) {
        vector<vector<string>> newStatesTotal;
        for (auto &nieuweState: newStates) {
            vector<vector<string>> nieuweStates1 = fullTransition(nieuweState, eTransitions);
            for (auto &j: nieuweStates1) {
                newStatesTotal.push_back(j);
            }
        }
        newStates = newStatesTotal;
    }
    for (auto &i: eStatesDos) {
        State state;
        state.name = i;
        if (i == DFAstartState) {
            state.start = true;
        }
        for (auto &j: i) {
            for (auto &EfinalState: eFinalStates) {
                if (j == EfinalState) {
                    state.final = true;
                }
            }
        }
        eStatesTres.push_back(state);
    }
}

void DFA::print() {
    json j;
    j["type"] = "DFA";
    j["alphabet"] = eAlfabet;

    basic_json<> kStates;
    for (auto &it: eStatesTres) {
        basic_json<> staten;
        string stateName = "{";
        sort(it.name.begin(), it.name.end());
        for (auto i = 0; i < it.name.size(); i++) {
            if (i == it.name.size() - 1) {
                stateName += it.name[i];
            } else {
                stateName += it.name[i];
                stateName += ",";
            }
        }
        stateName += "}";
        staten["name"] = stateName;
        if (it.start) {
            staten["starting"] = true;
        } else {
            staten["starting"] = false;
        }
        if (it.final) {
            staten["accepting"] = true;
        } else {
            staten["accepting"] = false;
        }
        kStates.push_back(staten);
    }

    j["states"] = kStates;
    auto tempTransitions = eTransitionsTwo;
    basic_json<> fullTransition;
    while (!tempTransitions.empty()) {
        basic_json<> lowest = tempTransitions[0];
        int lowestIndex = 0;
        for (auto tempTransIndex = 0; tempTransIndex < tempTransitions.size(); tempTransIndex++) {
            if (tempTransitions[tempTransIndex]["from"] < lowest["from"]) {
                lowest = tempTransitions[tempTransIndex];
                lowestIndex = tempTransIndex;
            } else if (tempTransitions[tempTransIndex]["from"] == lowest["from"]) {
                if (tempTransitions[tempTransIndex]["input"] < lowest["input"]) {
                    lowest = tempTransitions[tempTransIndex];
                    lowestIndex = tempTransIndex;
                } else if (tempTransitions[tempTransIndex]["input"] == lowest["input"]) {
                    if (tempTransitions[tempTransIndex]["to"] < lowest["to"]) {
                        lowest = tempTransitions[tempTransIndex];
                        lowestIndex = tempTransIndex;
                    }
                }
            }
        }
        sort(lowest["from"].begin(), lowest["from"].end());
        string stateNaam = "{";
        for (auto i = 0; i < lowest["from"].size(); i++) {
            if (i == lowest["from"].size() - 1) {
                stateNaam += lowest["from"][i];
            } else {
                stateNaam += lowest["from"][i];
                stateNaam += ",";
            }
        }
        stateNaam += "}";
        lowest["from"] = stateNaam;
        stateNaam = "{";
        for (auto i = 0; i < lowest["to"].size(); i++) {
            if (i == lowest["to"].size() - 1) {
                stateNaam += lowest["to"][i];
            } else {
                stateNaam += lowest["to"][i];
                stateNaam += ",";
            }
        }
        stateNaam += "}";
        lowest["to"] = stateNaam;
        lowest["input"] = lowest["input"][0];

        fullTransition.push_back(lowest);
        tempTransitions.erase(tempTransitions.begin() + lowestIndex);
    }
    j["transitions"] = fullTransition;
    cout << setw(4) << j << endl;
}

vector<string> DFA::epsilonClosure(string &state, vector<map<string, string>> &transitions) {
    vector<string> closureStates = {state};
    vector<string> currentStates = {state};
    vector<string> tempCurrentStates;
    string tempCurState;
    bool status = true;
    while (status) {
        for (auto i = 0; i < currentStates.size(); i++) {
            tempCurState = currentStates[i];
            for (auto &transition: transitions) {
                if (tempCurState == transition["from"]) {
                    if (transition["input"] == epsilon) {
                        if (!count(closureStates.begin(), closureStates.end(), transition["to"])) {
                            closureStates.push_back(transition["to"]);
                            status = true;
                        } else {
                            status = false;
                        }
                        tempCurrentStates.push_back(transition["to"]);
                    } else {
                        status = false;
                    }
                }
            }
            currentStates = tempCurrentStates;
            tempCurrentStates.clear();
        }
    }
    return closureStates;
}



vector<vector<string>> DFA::fullTransition(vector<string> &states, vector<map<string, string>> &transitions) {
    vector<vector<string>> nieuweStates;
    vector<string> tempStates;
    for (auto &h: eAlfabet) {
        set<string> statesNaClosure;
        tempStates = transitionInput(h, states, eTransitions);
        for (auto &tempState: tempStates) {
            vector<string> tempStatesNaClosure = epsilonClosure(tempState, eTransitions);
            for (auto &j: tempStatesNaClosure) {
                statesNaClosure.insert(j);
            }
        }
        vector<string> statesAfterClosure;
        for (const auto &it: statesNaClosure) {
            statesAfterClosure.push_back(it);
        }
        map<string, vector<string>> transities;
        transities["from"] = states;
        transities["input"] = {h};
        transities["to"] = statesAfterClosure;
        if (!count(eStatesDos.begin(), eStatesDos.end(), statesAfterClosure)) {
            nieuweStates.push_back(statesAfterClosure);
            State state;
            state.name = transities["to"];
            eStatesUno.push_back(state);
            eStatesDos.push_back(transities["to"]);
        }
        eTransitionsTwo.push_back(transities);
    }
    return nieuweStates;
}

vector<string>
DFA::transitionInput(const string &iS, vector<string> &states, vector<map<string, string>> &transitions) {
    vector<string> tempStates;
    for (auto &state: states) {
        for (auto &eTransition: eTransitions) {
            if (state == eTransition["from"]) {
                if (iS == eTransition["input"]) {
                    tempStates.push_back(eTransition["to"]);
                }
            }
        }
    }
    return tempStates;
}