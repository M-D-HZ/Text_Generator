#include <iostream>
#include <fstream>
#include "MarkovChain.h"

#include <time.h>
#include <vector>
#include <string>
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
    string Punctuation;
    bool repeat = false;
    while(outfile){
        string CurrentWord;
        if (!repeat){
            getline(outfile,CurrentWord,' ');     /// Read out of file until u encounter ' '
        }
        else{
            CurrentWord = Punctuation;
        }
        if (!repeat && CurrentWord[CurrentWord.size()-1] == '.' or !repeat && CurrentWord[CurrentWord.size()-1] == ','){
            Punctuation = CurrentWord[CurrentWord.size()-1];
            CurrentWord.erase(CurrentWord.size()-1);
            repeat = true;
        }
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
        if (CurrentWord == Punctuation){
            repeat = false;
        }
        PreviousWord = CurrentWord;                      /// Set the previous word to Current word
        PreviousWordState = newstate;                    /// Set the state of the previous word to the state we used
    }
    outfile.close();
}


// check if state already exists
// 2. exists: add to transitions of previous word (state)
// 3. doesn't exist: make new state + add to transitions of previous word + add to states of markovchain

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

void MarkovChain::randomWalkAlgorithm(string &input) {

    fstream output;
    output.open("output.txt",ios::out|ios::trunc);
    currentState = states[input];
    int rand = 0;

    while (currentState->name != ".") {
        vector<string>nextWords;
        for (auto t:currentState->transitions) {
            vector<string> v(t.second,t.first);
            nextWords.insert(nextWords.end(), v.begin(), v.end());
        }
        int size = nextWords.size();
        srand((int)time(0));
        int r = rand %size;
        output<< currentState->name;
        if (states[nextWords[r]]->name != ".") {
            output<< " ";
        }
        currentState = states[nextWords[r]];
    }

    output << currentState->name;
    output.close();
}