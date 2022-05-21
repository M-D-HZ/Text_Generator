//
// Created by chloeacm on 21.05.22.
//

#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "State.h"
#include <map>
using namespace std;


class MarkovChain {
public:
    MarkovChain();
    map<string,State> states;
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
