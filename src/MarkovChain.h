#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "MarkovState.h"
#include <map>
using namespace std;

class MarkovChain {
public:
    MarkovChain() = default;
    MarkovChain(string &filename);

    MarkovStatemap states;
    string outputFile;
    MarkovState* currentState;

    bool wordExists(string &word);

    void addWord(MarkovState* state);
    void randomWalkAlgorithm(string &input,int size);
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
