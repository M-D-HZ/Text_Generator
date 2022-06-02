#ifndef CLION_DFA_H
#define CLION_DFA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "json.hpp"

using namespace std;
using namespace nlohmann;

class DFA {
private:
    string typeN;
    string startState;
    vector<string> fstates;
    vector<string> Alphabet;
    vector<string> Astates;
    vector<string> productStartState;
    vector<vector<string>> productStates;
    vector<vector<string>> productFStates;
    vector<map<string, string>> Transitions;
    nlohmann::basic_json<> Staten;

public:
    DFA();

    explicit DFA(const string &fname);

    DFA(DFA &dfa1, DFA &dfa2, bool intersect);

    void print();
};


#endif //CLION_DFA_H
