#include "DFA.h"


DFA::DFA() = default;

DFA::DFA(const string &fname) {
    ifstream input(fname);
    if (!input.is_open()) {
        cerr << "Error opening file" << endl;
    }
    json j;
    input >> j;

    string T = j["type"];
    this->typeN = T;
    vector<string> alfabet = j["alphabet"];
    Alphabet = alfabet;
    auto states = j["states"];
    Staten = states;
    vector<map<string, string>> transitions = j["transitions"];

    for (auto &state: states) {
        string stateName = state["name"];
        if (state["accepting"] == true) {
            fstates.push_back(stateName);
        }
        if (state["starting"] == true) {
            startState = stateName;
        }
        Astates.push_back(stateName);
    }
    Transitions = transitions;
}

DFA::DFA(DFA &dfa1, DFA &dfa2, bool intersect) {

    typeN = "DFA";
    Alphabet = dfa1.Alphabet;
    vector<string> semiProductStartState = {dfa1.startState, dfa2.startState};
    vector<vector<string>> exStates = {{semiProductStartState}};
    vector<vector<string>> currentStates = {{semiProductStartState}};

    nlohmann::basic_json<> staten;
    string gName = "(" + semiProductStartState[0] + "," + semiProductStartState[1] + ")";
    staten["name"] = gName;
    staten["starting"] = false;
    staten["accepting"] = false;

    if (semiProductStartState[0] == dfa1.startState && semiProductStartState[1] == dfa2.startState) {
        semiProductStartState = semiProductStartState;
        staten["starting"] = true;
    }
    if (intersect) {
        if (count(dfa1.fstates.begin(), dfa1.fstates.end(), semiProductStartState[0]) &&
            count(dfa2.fstates.begin(), dfa2.fstates.end(),
                  semiProductStartState[1])) {
            productFStates.push_back(semiProductStartState); //
            staten["accepting"] = true;
        }
    } else {
        if (count(dfa1.fstates.begin(), dfa1.fstates.end(), semiProductStartState[0]) ||
            count(dfa2.fstates.begin(), dfa2.fstates.end(),
                  semiProductStartState[1])) {
            productFStates.push_back(semiProductStartState);
            staten["accepting"] = true;
        }
    }
    Staten.push_back(staten);

    vector<vector<string>> temporary;
    vector<string> check;
    check.push_back(gName);
    while (!currentStates.empty()) {
        for (auto &currentState: currentStates) {
            for (auto &j: Alphabet) {
                vector<string> temporaryStates;
                for (auto &Transition: dfa1.Transitions) {
                    if (Transition["from"] == currentState[0]) {
                        if (Transition["input"] == j) {
                            temporaryStates.push_back(Transition["to"]);
                        }
                    }
                }
                for (auto &Transition: dfa2.Transitions) {
                    if (Transition["from"] == currentState[1]) {
                        if (Transition["input"] == j) {
                            temporaryStates.push_back(Transition["to"]);
                        }
                    }
                }
                for (auto &doorlopenState: exStates) {
                    if (doorlopenState == temporaryStates) {
                        temporaryStates.clear();
                    }
                }

                if (!temporaryStates.empty()) {
                    nlohmann::basic_json<> statenPlus;
                    string cName = "(" + temporaryStates[0] + "," + temporaryStates[1] + ")";
                    statenPlus["name"] = cName;
                    statenPlus["starting"] = false;
                    statenPlus["accepting"] = false;
                    if (temporaryStates[0] == dfa1.startState && temporaryStates[1] == dfa2.startState) {
                        semiProductStartState = temporaryStates;
                        statenPlus["starting"] = true;
                    }

                    if (intersect) {
                        if (count(dfa1.fstates.begin(), dfa1.fstates.end(), temporaryStates[0]) &&
                            count(dfa2.fstates.begin(), dfa2.fstates.end(), temporaryStates[1])) {
                            productFStates.push_back(temporaryStates);
                            statenPlus["accepting"] = true;
                        }
                    } else {
                        if (count(dfa1.fstates.begin(), dfa1.fstates.end(), temporaryStates[0]) ||
                            count(dfa2.fstates.begin(), dfa2.fstates.end(), temporaryStates[1])) {
                            productFStates.push_back(temporaryStates);
                            statenPlus["accepting"] = true;
                        }
                    }
                    if (!count(check.begin(), check.end(), cName)) {
                        Staten.push_back(statenPlus);
                        check.push_back(cName);
                    }
                    if (!temporaryStates.empty()) {
                        temporary.push_back(temporaryStates);
                    }
                }
            }
        }
        currentStates = temporary;
        temporary.clear();
        for (auto &currentState: currentStates) {
            if (!count(exStates.begin(), exStates.end(), currentState)) {
                exStates.push_back(currentState);
            }
        }
    }
    productStates = exStates;
    for (auto &productDFAState: productStates) {
        for (auto &j: Alphabet) {
            basic_json<> transities;
            vector<string> destinationStates;
            for (auto &Transition: dfa1.Transitions) {
                if (Transition["from"] == productDFAState[0]) {
                    if (Transition["input"] == j) {
                        destinationStates.push_back(Transition["to"]);
                    }
                }
            }
            for (auto &Transition: dfa2.Transitions) {
                if (Transition["from"] == productDFAState[1]) {
                    if (Transition["input"] == j) {
                        destinationStates.push_back(Transition["to"]);
                    }
                }
            }
            string fromNaam = "(" + productDFAState[0] + "," + productDFAState[1] + ")";
            transities["from"] = fromNaam;
            transities["input"] = j;
            string destinationNaam = "(" + destinationStates[0] + "," + destinationStates[1] + ")";
            transities["to"] = destinationNaam;
            Transitions.push_back(transities);
        }
    }
}

void DFA::print() {
    json j;
    j["type"] = typeN;
    j["alphabet"] = Alphabet;

    vector<string> temporaryStates;
    for (auto &productDFAState: productStates) {
        string gName = "(" + productDFAState[0] + "," + productDFAState[1] + ")";
        temporaryStates.push_back(gName);
    }
    vector<string> sortedStates;
    while (!temporaryStates.empty()) {
        auto min = min_element(temporaryStates.begin(), temporaryStates.end());
        sortedStates.push_back(*min);
        temporaryStates.erase(min);
    }
    basic_json<> fullStates;
    for (auto &sortedState: sortedStates) {
        for (auto &it2: Staten) {
            if (sortedState == it2["name"]) {
                fullStates.push_back(it2);
            }
        }
    }
    j["states"] = fullStates;

    auto temporaryTransitions = Transitions;
    basic_json<> fullTransition;

    while (!temporaryTransitions.empty()) {
        basic_json<> lowest = temporaryTransitions[0];
        int lowestIndex = 0;
        for (auto tempTransIndex = 0; tempTransIndex < temporaryTransitions.size(); tempTransIndex++) {
            if (temporaryTransitions[tempTransIndex]["from"] < lowest["from"]) {
                lowest = temporaryTransitions[tempTransIndex];
                lowestIndex = tempTransIndex;
            } else if (temporaryTransitions[tempTransIndex]["from"] == lowest["from"]) {
                if (temporaryTransitions[tempTransIndex]["input"] < lowest["input"]) {
                    lowest = temporaryTransitions[tempTransIndex];
                    lowestIndex = tempTransIndex;
                }
            }
        }
        fullTransition.push_back(lowest);
        temporaryTransitions.erase(temporaryTransitions.begin() + lowestIndex);
    }
    j["transitions"] = fullTransition;
    cout << setw(4) << j << endl;
}

