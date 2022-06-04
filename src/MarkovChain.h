#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "Parser.h"
#include <map>
using namespace std;

class MarkovState;
class MarkovChain {
public:
    MarkovChain() = default;
    MarkovChain(string &filename);

    MarkovStatemap states;
    string outputFile;
    MarkovState* currentState;
    bool IsUncommonWord(string &word);
    bool LowerChance(string &word, vector<MarkovState*> PrevWords);
    bool wordExists(string &word);
    void addWord(MarkovState* state);
    void randomWalkAlgorithm(string &input,int size = 0);
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
