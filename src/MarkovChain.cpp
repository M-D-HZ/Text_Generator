#include <iostream>
#include <fstream>
#include "MarkovChain.h"
#include "MarkovState.h"
#include "Parser.h"

#include <windows.h>
#include <time.h>
#include <vector>
#include <string>
#include "algorithm"

using namespace std;


//------------------------- Hulpfuncties ---------------------------------------//

bool isPunctuation(char c) {
    vector<char> chars = {'.', ',', '!', ':', '?', '\n'};
    vector<char>::iterator it;
    it = find(chars.begin(), chars.end(), c);
    if (it != chars.end()) {
        return true;
    }
    return false;
}

/// Train Markov chain constructor (parse txt file)
/// \param filename: file waaruit geparsed wordt
MarkovChain::MarkovChain(string &filename) {
    Parser parser(filename);
    states = parser.getStates();
    cout << states.size() << endl;

//    // Read file
//    fstream outfile;
//    outfile.open(filename);
//    if (!outfile.is_open()) {
//        cerr << "File not found!" << endl;
//        exit(5);
//    }
//
//    // Initialise Variables
//    MarkovState *previousWordState;
//    string previousWord;
//    string punctuation;
//    bool repeat;
//
//    // Reads file (word by word)
//    while (outfile) {
//        string currentWord;
//        if (!repeat) {
//            // Parses word
//            //  -- (aka add char to string till you reach a space)
//            getline(outfile, currentWord, ' ');
//        } else {
//            // Reached end of sentence (?) final word(?)
//            currentWord = punctuation;
//        }
//        if (!repeat && isPunctuation(currentWord[currentWord.size() - 1])) {
//            // Removes punctuation from the current word and saves the used punctuation
//            punctuation = currentWord[currentWord.size() - 1];
//            currentWord.erase(currentWord.size() - 1);
//            repeat = true;
//        }
//
//        MarkovState *currentWordState;
//        if (!wordExists(currentWord)) {
//            // create a new state for current (new) word and add it to the state map
//            currentWordState = new MarkovState(currentWord);
//            states[currentWord] = currentWordState;
//        } else {  // else if it exists make currentWordState a pointer to that state
//            currentWordState = states[currentWord];
//        }
//        if (!previousWord.empty()) { // Not the first word
//            // Add a transition to the previousWordState
//            previousWordState->addTransition(currentWordState);
//        }
//        if (currentWord == punctuation) {
//            repeat = false;
//        }
//
//        // Update previousWord variables
//        previousWord = currentWord;
//        previousWordState = currentWordState;
//    }
//    outfile.close();
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

bool MarkovChain::IsUncommonWord(string &word){
    if (word.size() >= 3){
        return true;
    }
    return false;
}

bool MarkovChain::LowerChance(string &word, vector<MarkovState*> PrevWords){
    for (auto &b:PrevWords){
        if (b->name == word && IsUncommonWord(word)){
            return true;
        }
    }
    return false;
}

void MarkovChain::randomWalkAlgorithm(string &input,int size) {
    if (!wordExists(input)){ // Woord kan niet gebruikt worden als begin van een zin
        cerr<< "This word is not supported as begin!" << endl;
        exit(5);
    }
    // Create outputfile
    fstream output;
    output.open("output.txt", ios::out | ios::trunc);
    currentState = states[input];
    vector<MarkovState*> Prevwords;
    bool stoppen = false;
    int amountOfPeriods = 0;
    int amountOfSentences = 0;
    if (size == 0) {
        amountOfSentences = 1;
    }
    else if (size == 1) {
        amountOfSentences = 5;
    }
    else if (size == 2) {
        amountOfSentences = 10;
    }

    // Main loop begint met input
    while (!stoppen) {
        Prevwords.push_back(currentState);
        vector<string> nextWords;
        for (const auto &transitionPair: currentState->transitions) {
            int Checkup = transitionPair.second;
            string word = transitionPair.first;
            if (LowerChance(word,Prevwords) && Checkup != 0){
                Checkup--;
            }
            vector<string> v(Checkup, word);
            nextWords.insert(nextWords.end(), v.begin(), v.end());
        }
        int size = nextWords.size();

        srand((int)time(0));
        int r = rand() %size;

        output<< currentState->name;
        if (states[nextWords[r]]->name[states[nextWords[r]]->name.size() - 1] != '.') {
            output<< " ";
        }
        currentState = states[nextWords[r]];

        if (states[nextWords[r]]->name[states[nextWords[r]]->name.size() - 1] == '.') {
            Prevwords.clear();
            amountOfPeriods += 1;
            if (amountOfPeriods == amountOfSentences) {
                stoppen = true;
            }
        }
    }

    output << currentState->name;
    output.close();
}

void MarkovChain::testWalk(string &input) {
    if (!wordExists(input)){ // Woord kan niet gebruikt worden als begin van een zin
        cerr<< "This word is not supported as begin!" << endl;
        exit(5);
    }
    vector<MarkovState*> Prevwords;
    vector<string> gegenereerdeT;
    currentState = states[input];
    gegenereerdeT.push_back(currentState->name);
    int i = 0;
    while (i < 100) {
        vector<string> nextWords;
        for (const auto &transitionPair: currentState->transitions) {
            int Checkup = transitionPair.second;
            string word = transitionPair.first;
            if (LowerChance(word,Prevwords) && Checkup != 0){
                Checkup--;
            }
            vector<string> v(Checkup, word);
            nextWords.insert(nextWords.end(), v.begin(), v.end());
        }
        int size = nextWords.size();
        srand((int) time(0));
        int r = rand() % size;
        currentState = states[nextWords[r]];
        gegenereerdeT.push_back(currentState->name);
        i++;
        Sleep(50);
    }
    print(gegenereerdeT);
}

void MarkovChain::print(vector<string> ggT) {
    fstream output;
    output.open("output.txt", ios::out | ios::trunc);
    Parser hulp;
    for (auto &w : ggT){
        if (!hulp.isPunctuation(w[w.size()-1])){
            output << " ";
        }
        output << w;
    }
    output.close();
}