#include <iostream>
#include <fstream>
#include "MarkovChain.h"

#include <time.h>
#include <vector>
#include <string>
using namespace std;


//------------------------- Hulpfuncties ---------------------------------------//

bool isPunctuation(char c){
    if(c == '.' || c == ',' || c == '!' || c == ':' || c == '?' || c == '\n' || c == '(' || c == ')'){ // TODO: Dit moet korter en we moeten iets aan de haakjes doen :(
        return true;
    }
    return false;
}

/// Train Markov chain constructor (parse txt file)
/// \param filename: file waaruit geparsed wordt
MarkovChain::MarkovChain(string &filename) {
    // Read file
    fstream outfile;
    outfile.open(filename);
    if (!outfile.is_open()){
        cerr << "File not found!" << endl;
        exit(5);
    }

    // Initialise Variables
    MarkovState* previousWordState;
    string previousWord;
    string punctuation;
    bool repeat;

    // Reads file (word by word)
    while(outfile){
        string currentWord;
        if (!repeat){
            // Parses word
            //  -- (aka add char to string till you reach a space)
            getline(outfile, currentWord, ' ');
        }
        else{
            // Reached end of sentence (?) final word(?)
            currentWord = punctuation;
        }
        if (!repeat && isPunctuation(currentWord[currentWord.size() - 1])){
            // Removes punctuation from the current word and saves the used punctuation
            punctuation = currentWord[currentWord.size() - 1];
            currentWord.erase(currentWord.size() - 1);
            repeat = true;
        }

        MarkovState* currentWordState;
        if (!wordExists(currentWord)){
            // create a new state for current (new) word and add it to the state map
            currentWordState = new MarkovState(currentWord);
            states[currentWord] = currentWordState;
        }
        else{  // else if it exists make currentWordState a pointer to that state
            currentWordState = states[currentWord];
        }
        if (!previousWord.empty()){ // Not the first word
            // Add a transition to the previousWordState
            previousWordState->addTransition(currentWordState);
        }
        if (currentWord == punctuation){
            repeat = false;
        }

        // Update previousWord variables
        previousWord        = currentWord;
        previousWordState   = currentWordState;
    }
    outfile.close();
}

/// checks if the state already exists
/// \param word word (name of the state)
/// \return boolean indicating its existence
bool MarkovChain::wordExists(string &word) {
    return states.find(word) != states.end();
}

/// Adds a word/state to the word/state list
/// \param state name of the new word/state
void MarkovChain::addWord(MarkovState *state) {
    states[state->name] = state;
}

void MarkovChain::randomWalkAlgorithm(string &input) {
    if (!wordExists(input)){ // Woord kan niet gebruikt worden als begin van een zin
        cerr<< "This word is not supported as begin!" << endl;
        exit(5);
    }
    // Create outputfile
    fstream output;
    output.open("output.txt",ios::out|ios::trunc);
    currentState = states[input];

    // Main loop begint met input
    while (!isPunctuation(currentState->name[currentState->name.size() - 1])) {
        vector<string> nextWords;
        for (auto transitionpair:currentState->transitions) {
            vector<string> v(transitionpair.second, transitionpair.first);
            nextWords.insert(nextWords.end(), v.begin(), v.end());
        }
        int size = nextWords.size();

        srand((int)time(0));
        int r = rand() %size;

        output<< currentState->name;
        if (!isPunctuation(states[nextWords[r]]->name[states[nextWords[r]]->name.size() - 1])) {
            output<< " ";
        }
        currentState = states[nextWords[r]];
    }

    output << currentState->name;
    output.close();
}