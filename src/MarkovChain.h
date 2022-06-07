#ifndef TOG_TXT_GENERATOR_MARKOVCHAIN_H
#define TOG_TXT_GENERATOR_MARKOVCHAIN_H

#include "Parser.h"
#include <map>
using namespace std;

class MarkovState;
class MarkovChain {
private:
    int index = 0;
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
    void addFirstOrder(vector<string> fO);

    void testWalk(string &input, int size);
    void print(vector<string> ggT);
};


#endif //TOG_TXT_GENERATOR_MARKOVCHAIN_H
