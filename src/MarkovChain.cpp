#include <iostream>
#include <fstream>
#include "MarkovChain.h"


using namespace std;

/// Empty constructor
MarkovChain::MarkovChain() = default;

/// Train Markov chain constructor (parse txt file)
MarkovChain::MarkovChain(string &filename) {
    fstream outfile;
    outfile.open(filename);         /// open file to read
    if (!outfile.is_open()){
        return;
    }
    string PreviousWord;
    State* PreviousWordState;
    while(outfile){
        string CurrentWord;
        getline(outfile,CurrentWord,' ');     /// Read out of file until u encounter ' '
        State* newstate;
        if (!wordExists(CurrentWord)){                 /// if word hasn't been added to the states
            newstate = new State(CurrentWord);         /// create a new state for current word
            states[CurrentWord] = newstate;               /// Add the Currentword to our states
        }
        else{
            newstate = states[CurrentWord];               /// else if it exsits make newstates a pointer to that state
        }
        if (!PreviousWord.empty()){                       /// if this isnt the first word
            if (PreviousWordState->transitionExists(CurrentWord)){      /// Check if the previous word has transitions
                PreviousWordState->addTransition(CurrentWord);          /// if it has transitions on the current word, Add to it
            }
            else{
                PreviousWordState->newTransition(newstate);         /// Else create a new transition for the current word
            }
        }
        PreviousWord = CurrentWord;                      /// Set the previous word to Current word
        PreviousWordState = newstate;                    /// Set the state of the previous word to the state we used
    }
    outfile.close();
}


/// check if state already exists
/// 2. exists: add to transitions of previous word (state)
/// 3. doesn't exist: make new state + add to transitions of previous word + add to states of markovchain

bool MarkovChain::wordExists(string &s) {
    map<string,State*>::iterator it;
    it = states.find(s);
    if (it != states.end()) {
        return true;
    }
    else {
        return false;
    }
}

void MarkovChain::addWord(State *s) {
    states[s->name] = s;
}