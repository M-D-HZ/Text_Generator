#ifndef TOG_TXT_GENERATOR_HIGHERORDERMARKOVSTATE_H
#define TOG_TXT_GENERATOR_HIGHERORDERMARKOVSTATE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

class HigherOrderMarkovState {
private:
    string name;
    map<vector<HigherOrderMarkovState*>, map<double, set<HigherOrderMarkovState*>>> transitions;
public:
    HigherOrderMarkovState();
    HigherOrderMarkovState(string &word);

    const string &getName() const;
    void setName(const string &name);
    const map<vector<HigherOrderMarkovState *>, map<double, set<HigherOrderMarkovState *>>> &getTransitions() const;
    void setTransitions(
            const map<vector<HigherOrderMarkovState *>, map<double, set<HigherOrderMarkovState *>>> &transitions);

};


#endif //TOG_TXT_GENERATOR_HIGHERORDERMARKOVSTATE_H
