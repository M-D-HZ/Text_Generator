#ifndef TOG_TXT_GENERATOR_HIGHERORDERMARKOVCHAIN_H
#define TOG_TXT_GENERATOR_HIGHERORDERMARKOVCHAIN_H
#include "HigherOrderMarkovState.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

class MarkovChain;
class HigherOrderMarkovChain {
private:
    set<HigherOrderMarkovState*> states;
    int order = 2;

public:
    HigherOrderMarkovChain();
    explicit HigherOrderMarkovChain(int ord);
    void addState(string &name);
    HigherOrderMarkovState* getState(string &name);
    void removeState(string &name);
    void setTransition(string &name1, vector<string> prev_name1, string &name2, double chance);
    string getRandomState();
    MarkovChain toFirstOrder();
    bool stateExists(string &name);


    const set<HigherOrderMarkovState *> &getStates() const;
    void setStates(const set<HigherOrderMarkovState *> &states);
    int getOrder() const;
    void setOrder(int order);
};


#endif //TOG_TXT_GENERATOR_HIGHERORDERMARKOVCHAIN_H
