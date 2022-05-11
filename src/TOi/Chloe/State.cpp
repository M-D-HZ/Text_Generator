//
// Created by chloeacm on 01.04.22.
//

#include "State.h"

State::State() {
    name = "";
    start = false;
    accept = false;
}

State::~State() {
    delete this;
}