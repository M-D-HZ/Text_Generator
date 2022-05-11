#include "states_n_transitions.h"

#include <fstream>
#ifndef TOI_2021_2022_AUTOMATA_H
#define TOI_2021_2022_AUTOMATA_H

class Automata {
protected:
    vector<string> alphabet;
    States states;
    Transitions transitions;

    State* start;
    public:
    Automata();
    explicit Automata(const string &filepath);

    vector<string> getAlphabet(){return alphabet;}
    void setAlphabet(vector<string> theAlphabet){alphabet = theAlphabet;}

    State* getState(string name)    { return states[name];}
    States getStates()              { return states;}
    void setStates(States newStates){ states = newStates;}

    Transitions getTransitions();
    void setTransitions(Transitions newTransitions){transitions = newTransitions;}

    State* getStart(){return start;}
    void setStart(State* state);

    bool checkSymbol(string str);
    json makeJson();
    virtual bool accept(string &input){exit(3);} // Exits because you're not supposed to be here
};


#endif //TOI_2021_2022_AUTOMATA_H
