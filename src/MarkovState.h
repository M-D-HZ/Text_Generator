#ifndef TOG_TXT_GENERATOR_MARKOVSTATE_H
#define TOG_TXT_GENERATOR_MARKOVSTATE_H

#include <string>
#include <map>
using namespace std;


class MarkovState {
public:
    string name;

    map<string,MarkovState*> nextStates;
    map<string, int> transitions;

    MarkovState(string& statename);
    ~MarkovState()=default;

    bool transitionExists(string &statename);

    void newTransition(MarkovState* destinationState);
    void addTransition(MarkovState* destinationState);
};

typedef map<string, MarkovState*> MarkovStatemap;

#endif //TOG_TXT_GENERATOR_MARKOVSTATE_H
