#include "Parser.h"
#include "MarkovState.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Parser::Parser() = default;

Parser::Parser(const string &filename) {
    fstream file;
    file.open(filename);
    if (!file.is_open()){
        cerr << "File is not found!" << endl;
        exit(5);
    }

    // Basic variables
    MarkovState *pWordState;
    string currentWord;
    string previousWord;
    string punctiation;
    bool repeat;

    // Reading file (with use of Regular Expressions)
    while (file){
        if (!repeat){
            getline(file, currentWord, ' ');
        } else {
            currentWord = punctiation;
        }
        if (!repeat && isPunctuation(currentWord[currentWord.size()-1])){
            punctiation = currentWord[currentWord.size()-1];
            currentWord.erase(currentWord.size() -1);
            repeat = true;
        }
        MarkovState *currentWordState;
        if (!wordExists(currentWord)){
            currentWordState = new MarkovState(currentWord);
            states[currentWord] = currentWordState;
        } else{
            currentWordState = states[currentWord];
        }
        if (!previousWord.empty()){
            pWordState->addTransition(currentWordState);
        }
        if (currentWord == punctiation){
            repeat = false;
        }

        previousWord = currentWord;
        pWordState = currentWordState;
    }
    file.close();
}

bool Parser::isPunctuation(char c) const {
    vector<char> chars = {'.', ',', '!', ':', '?', '\n', '(', ')'};
    vector<char>::iterator it;
    it = find(chars.begin(), chars.end(), c);
    if (it != chars.end()){
        return true;
    }
    return false;
}

bool Parser::wordExists(string &word){
    return states.find(word) != states.end();
}

const MarkovStatemap &Parser::getStates() const {
    return states;
}