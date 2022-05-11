#include "Automata.h"


Transitions Automata::getTransitions() {
    return Transitions();
}

json Automata::makeJson() {
    json mainJson;
    mainJson["alphabet"] = alphabet;

    vector<json> jsonStates;
    for(auto statepair : states){
        jsonStates.push_back(statepair.second->returnJson());
    }
    mainJson["states"] = jsonStates;

    vector<json> jsonTransitions;
    for(auto transition : transitions){
        jsonTransitions.push_back(transition->returnJson());
    }
    mainJson["transitions"] = jsonTransitions;

    return mainJson;
}

bool Automata::checkSymbol(string str) {
    for (const string& symbol : alphabet){
        if(str == symbol){return true;}
    }
    return false;
}

void Automata::setStart(State* state) {
    if(state == nullptr){
        cerr << "[ERROR] - setStart function took a nullptr as state!" << endl;
        exit(3);
    }
    else if(!state->start){
        cerr << state->name << " is not a starting State!" << endl;
        exit(3);
    }
    else{ start = state;}
}

Automata::Automata() {
    alphabet.clear();
    states.clear();
    transitions.clear();
    start = nullptr;
}

Automata::Automata(const string &filepath) {
    // ----------------------------- Reset variables ------------------------------//
    start = nullptr;
    alphabet.clear();
    transitions.clear();
    states.clear();

    // ----------------------------- Read file input ------------------------------//
    ifstream input(filepath);
    if(!input){
        cerr<< "File not found" << endl;
        exit(3);
    }
    json automata;
    input >> automata;
    input.close();

    // Alphabet
    for(string str : automata["alphabet"]){
        alphabet.push_back(str);
    }

    //--------------------------------- States -----------------------------------//
    for (auto state: automata["states"]){
        // added to the states vector and checked if it is a starting state
        auto *newstate = new State(state["name"],
                                   state["accepting"],
                                   state["starting"]);

        if (newstate->start){
            if(start != nullptr) {
                cerr << "More than 1 starting state found in json file!" << endl;}
            else{
                start = newstate;
            }
        }
        states[newstate->name] = newstate;
    }

    if (start == nullptr){
        cerr << "No starting state found in json file! Please fix!"<< endl;
        setStart(nullptr);
        exit(6666);
    }

    //---------------------------------- Transitions -----------------------------//
    for (auto transit : automata["transitions"]){
        if(states[transit["from"]] == nullptr || states[transit["from"]] == nullptr ){
            cerr << "Not all states from the transition exist!" << endl;
            exit(5);
        }
        auto *newtransit = new Transition(
                states[transit["from"]],
                states[transit["to"]],
                transit["input"]
        );
        transitions.push_back(newtransit);
    }
}


