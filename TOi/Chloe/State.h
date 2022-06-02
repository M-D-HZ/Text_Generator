//
// Created by chloeacm on 01.04.22.
//

#ifndef TOI_CHLOE_STATE_H
#define TOI_CHLOE_STATE_H


#include <string>
using namespace std;


class State {

public:
    string name;
    bool start;
    bool accept;

    State();
    ~State();
};


#endif //TOI_CHLOE_STATE_H
