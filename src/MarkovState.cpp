#include "MarkovState.h"

MarkovState::MarkovState(string &statename) {
    name = statename;
}

/// Geeft aan of de gevraagde transitie bestaat of niet
/// \param statename naam van de state
/// \return if it exists or not
bool MarkovState::transitionExists(string &statename) {
    MarkovStatemap::iterator it;
    it = nextStates.find(statename);
    if (it != nextStates.end()) {
        return true;
    }
    else {
        return false;
    }
}

/// Voegt een nieuwe transitie toe
/// \param destinationState waar de transitie naartoe gaat
void MarkovState::newTransition(MarkovState *destinationState) {
    nextStates[destinationState->name] = destinationState;
    transitions[destinationState->name] = 1;
}

/// Verhoogt "kans" dat de transitie gebeurt
/// \param statename: naam van de state
void MarkovState::addTransition(string &statename) {
    if (transitionExists(statename)) {
        int count = transitions[statename];
        transitions[statename] = count + 1;
    }
}