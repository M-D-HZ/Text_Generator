//
// Created by chloeacm on 21.05.22.
//

#ifndef TOG_TXT_GENERATOR_STATE_H
#define TOG_TXT_GENERATOR_STATE_H

#include <string>
#include <map>
using namespace std;


class State {
    string name;
    map<string,State> nextstates;
    map<string, int> transitions;
};


#endif //TOG_TXT_GENERATOR_STATE_H
