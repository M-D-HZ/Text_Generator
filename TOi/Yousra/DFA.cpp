#include "DFA.h"

bool DFA::accepts(string input) {
    State* currstat = getStart();
    if (currstat == nullptr){
        cerr << "No startstate!" << endl;
        exit(3);
    }

    for (char c : input){
        string cstr;
        cstr = c;

        if(!checkSymbol(cstr)){
            cerr << "Input contains a character that isn't in the alphabet!" << endl;
            exit(3);
        }

        currstat = getDestination(currstat, cstr);
        if(currstat == nullptr){
            cerr << "Geen transition gebeurd, dit is geen DFA!" << endl;
            exit(3);
        }
    }
    return currstat->accept;
}

State *DFA::getDestination(State *from, string input) {
    if(!checkSymbol(input)){return nullptr;}

    for (auto transit : transitions){
        if(transit->from == from && transit->input == input){
            return transit->to;
        }
    }
    return nullptr;
}

void DFA::print() {
    json mainJson = makeJson();
    mainJson["type"] = "DFA";

    cout << setw(4) << mainJson << endl;
}

DFA::DFA(DFA dfa1, DFA dfa2, bool doorsnede) { // Best not to give these by reference, its possible that one of them is the current DFA
    // Reset variables
    alphabet.clear();
    start = nullptr;

    for(auto statepair : states){delete statepair.second;}
    states.clear();

    for(auto transition:transitions){delete transition;}
    transitions.clear();

    // combines Alphabets
    auto newAlphabet = dfa1.getAlphabet();
    for(auto str : dfa2.getAlphabet()){newAlphabet.push_back(str);}
    // sorts and removes duplicates:
    sort(newAlphabet.begin(), newAlphabet.end());
    newAlphabet.erase(unique( newAlphabet.begin(), newAlphabet.end() ), newAlphabet.end());

    alphabet = newAlphabet;

    // States and transitions done in a recursive function
    pair<State*, State*> startstates = pair<State*, State*>(dfa1.getStart(), dfa2.getStart());
    State* startstate = toState(startstates, doorsnede);
    startstate->start =true;
    states[startstate->name] = startstate;
    start = startstate;

    combine(startstate->name, dfa1, dfa2, doorsnede);
}


void DFA::combine(const string& newStatename, DFA &dfa1, DFA &dfa2, bool doorsnede) {
    vector<pair<string, State*>> inputResults;

    bool first = true; // voor te weten in welke dfa we moeten kijken
    for (auto symb : alphabet){
        pair<State*, State*> destinationStates;
        for(auto stateName : extractStates(newStatename)){
            if(first){
                first = false;
                destinationStates.first = dfa1.getDestination(dfa1.getState(stateName), symb);
            }
            else {
                first = true;
                destinationStates.second = dfa2.getDestination(dfa2.getState(stateName), symb);
            }
        }
        auto destinationState = new State;
        destinationState = toState(destinationStates, doorsnede);
        inputResults.emplace_back(symb, destinationState);
    }

    for(auto resultpair : inputResults){
        auto *transition = new Transition(states[newStatename], resultpair.second, resultpair.first);
        transitions.push_back(transition);
    }

    for(auto resultpair : inputResults){
        if(!inStates(resultpair.second, states)){
            states[resultpair.second->name] = resultpair.second;
            combine(resultpair.second->name, dfa1, dfa2, doorsnede);
        }
    }
}


State* DFA::toState(pair<State *, State *> states, bool doorsnede) {
    auto state = new State;

    // Create name
    state->name = '(';
    if(states.first != nullptr){
        state->name += states.first->name;
        if(states.second != nullptr){state->name += ',';}
    }
    if(states.second != nullptr){
        state->name += states.second->name;
    }
    state->name += ')';

    if(states.first != nullptr && states.second != nullptr ) {
        if (doorsnede) {
            if (states.first->accept && states.second->accept)
            { state->accept = true; }
        }
        else{
            if (states.first->accept || states.second->accept)
            {state->accept = true;}
        }
    }
    else if (states.first == nullptr){
        if(states.second != nullptr){state->accept = states.second->accept;}
        else{state->accept = false;}
    }
    else if (states.second == nullptr){
        if(states.first != nullptr){state->accept = states.first->accept;}
    }

    return state;
}

vector <string> DFA::extractStates(const string& str) {
    string stateName;
    vector<string> nameVector;
    for(auto c : str){
        if(c == '(' || c == ',' || c == ')'){
            if(!stateName.empty()){
                nameVector.push_back(stateName);
                stateName.clear();}
        }
        else {stateName.push_back(c);}
    }

    return nameVector;
}
