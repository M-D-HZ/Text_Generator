#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "State.h"
#include <map>
using namespace std;

class MarkovChain {
public:
    MarkovChain();
    MarkovChain(string &filename);
    map<string,State*> states;
    bool wordExists(string &s);
    void addWord(State* s);
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
