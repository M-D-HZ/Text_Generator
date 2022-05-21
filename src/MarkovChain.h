#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "State.h"
#include <map>
using namespace std;

class MarkovChain {
public:
    MarkovChain();
    MarkovChain(string Filename);
    map<string,State> states;
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
