#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "MarkovState.h"
#include <map>
using namespace std;

class MarkovChain {
public:
    MarkovChain();
    MarkovChain(string &filename);

    MarkovStatemap states;
    string outputFile;
    MarkovState* currentState;

    bool wordExists(string &s);

    void addWord(MarkovState* s);
    void randomWalkAlgorithm(string &input);
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
