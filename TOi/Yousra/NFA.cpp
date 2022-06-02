#include "NFA.h"

bool NFA::accepts(string input) {
    // Variables
    vector<State*> currentstates;
    vector<State*> tempmap;
    tempmap.clear();

    if(start == nullptr){
        cerr << "No startstate!" << endl;
        exit(3);
    }
    currentstates.push_back(start);
    string inputstring;

    // Code
    for (char c : input){
        inputstring = c;

        if(!checkSymbol(inputstring)){
            cerr << "Input contains a character that isn't in the alphabet!" << endl;
            exit(3);
        }

        for (auto currentstate : currentstates){
            for(auto transition: getTransitions()){
                if(transition->from == currentstate && transition->input == inputstring){
                    tempmap.push_back(transition->to);
                }
            }
        }
        currentstates = tempmap;
    }
    for (auto state : currentstates){
        if(state->accept){return state->accept;}
    }
    return false;
}

DFA NFA::toDFA() {
    DFA dfa;
    dfa.setAlphabet(alphabet);

    States dfaStates;           Transitions dfaTransitions;
    if(start == nullptr){
        cerr<< "There is no starting state in this NFA!" << endl;
        exit(3);
    }
    string startName = '{' + start->name + '}';

    createSubsets(startName, dfaStates, dfaTransitions);

    // Set start state
    dfaStates[startName]->start = true;

    dfa.setStates(dfaStates);
    dfa.setTransitions(dfaTransitions);

    dfa.setStart(dfa.getStates()['{' + start->name + '}']);

    return dfa;
}

States NFA::getDestinations(State *from, string input) {
    States destinations;

    for (auto transit : transitions){
        if(transit->from == from && transit->input == input){
            destinations[transit->to->name] = transit->to;
        }
    }
    return destinations;
}

void NFA::print() {
    json mainJson = makeJson();
    mainJson["type"] = "NFA";

    cout << setw(4) << mainJson << endl;
}

void NFA::createSubsets(const string &newStatename, States &dfaStates, Transitions &dfaTransitions) {
    State *dfaState;
    if(dfaStates.empty()) {
        dfaState = new State;
        dfaState->name = newStatename;
        dfaStates[newStatename] = dfaState;
    }
    else{
        dfaState = dfaStates[newStatename];
    }
    map<string, State*> inputResults;

    for(auto symb : alphabet){
        States destinationStates;
        for(auto statepair : extractStates(newStatename)) {
            auto tempstates = getDestinations(statepair.second, symb);
            destinationStates.insert(tempstates.begin(), tempstates.end());
        }
        State*  destinationState = new State;
        *destinationState = toState(destinationStates);
        inputResults[symb] = destinationState;
    }

    for(auto resultpair : inputResults){
        Transition *transition = new Transition(dfaStates[newStatename], resultpair.second, resultpair.first);
        dfaTransitions.push_back(transition);
    }

    for(auto resultpair : inputResults){
        if(!inStates(resultpair.second, dfaStates)){
            dfaStates[resultpair.second->name] = resultpair.second;
            createSubsets(resultpair.second->name, dfaStates, dfaTransitions);
        }
    }
}

States NFA::extractStates(string str) {
    string stateName;
    vector<string> nameVector;
    for(auto c : str){
        if(c == '{' || c == ',' || c == '}'){
            if(!stateName.empty()){
                nameVector.push_back(stateName);
                stateName.clear();}
        }
        else {stateName.push_back(c);}
    }

    States allStates;
    for(auto name : nameVector){
        if(states.find(name) == states.end()){
            cerr << "There is a transition that goes to a non-existent state (Should be impossible)" << endl;
            exit(3);
        }
        allStates[name] = states[name];
    }

    return allStates;
}


State NFA::toState(States thestates){
    State newState;
    string name = "{";

    for (auto statepair : thestates){
        if(name != "{"){name += ',';}
        name += statepair.first;

        if(statepair.second->accept){
            newState.accept = true;
        }
    }
    name += '}';
    newState.name = name;
    return newState;
}

