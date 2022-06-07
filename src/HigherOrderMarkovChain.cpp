#include "HigherOrderMarkovChain.h"
#include "MarkovChain.h"


HigherOrderMarkovChain::HigherOrderMarkovChain() = default;


const set<HigherOrderMarkovState *> &HigherOrderMarkovChain::getStates() const {
    return states;
}

void HigherOrderMarkovChain::setStates(const set<HigherOrderMarkovState *> &states) {
    HigherOrderMarkovChain::states = states;
}

int HigherOrderMarkovChain::getOrder() const {
    return order;
}

void HigherOrderMarkovChain::setOrder(int order) {
    HigherOrderMarkovChain::order = order;
}

HigherOrderMarkovChain::HigherOrderMarkovChain(int ord) {
    order = ord;
}

void HigherOrderMarkovChain::addState(string &name) {
//    if (stateExists(name)) return;
    HigherOrderMarkovState* nState = new HigherOrderMarkovState(name);
    states.insert(nState);
}

void HigherOrderMarkovChain::removeState(string &name) {
    if (!stateExists(name)) return;

    HigherOrderMarkovState* rState = getState(name);
    for (auto &state : states){
        for (auto &stateTrans : state->getTransitions()){
            if (stateTrans.second.find(rState) != stateTrans.second.end()){
                state->getTransitions().erase(stateTrans.first);
            }
        }
    }
    states.erase(states.find(rState));
}

MarkovChain HigherOrderMarkovChain::toFirstOrder() {
    MarkovChain markovChain;

    for (auto &state : states){
        for (auto &prev_coll_set : state->getTransitions()){
            vector<string> new_state_names;
            for (auto &prev_state : prev_coll_set.first){
                new_state_names.push_back(prev_state->getName());
            }
            new_state_names.push_back(state->getName());
            // push to markovChain
        }
    }

    for (auto &state : states){
        for (auto &prev_coll_set : state->getTransitions()){
            vector<string> new_state_names2;
            for (auto &prev_state : prev_coll_set.first){
                new_state_names2.push_back(prev_state->getName());
            }
            new_state_names2.push_back(state->getName());
            for (auto &trans : prev_coll_set.second){
                for (auto &state2: trans.second){
                    vector<string> new_state_names3 = new_state_names2;
                    new_state_names3.erase(new_state_names3.begin());
                    new_state_names3.push_back(state2->getName());
                // push to MarkovChain
                }
            }
        }
    }
    return markovChain;
}



string HigherOrderMarkovChain::getRandomState() {
    double chance = 1.0 / states.size();
    double rando = ((double)rand() / (RAND_MAX));
    double cN = 0;

    for (auto &state : states){
        cN += chance;
        if (rando < cN) return state->getName();
    }
    return (*states.end())->getName();
}

HigherOrderMarkovState *HigherOrderMarkovChain::getState(string &name) {
    for (auto &state : states){
        if (state->getName() == name) return state;
    }
    return nullptr;
}
