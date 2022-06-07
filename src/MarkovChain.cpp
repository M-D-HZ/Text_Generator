#include <iostream>
#include <fstream>
#include "MarkovChain.h"
#include "MarkovState.h"
#include "Parser.h"

#include "unistd.h" // random lib voor Linux
#include "random"   // random lib voor windows
#include <time.h>
#include <vector>
#include <string>
#include "algorithm"

using namespace std;


//------------------------- Hulpfuncties ---------------------------------------//

/**
 * Controleert of een character een leesteken is.
 * @param c character
 * @return boolean
 */
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

/**
 * Eerste versie van randomWalkAlgoritme.
 * Zie XXX voor laatste versie.
 * @param input Naam van de state.
 * @param size In relatie met het aantal zinnen die geconstrueerd moeten worden.
 * 0: Één zin.
 * 1: Vijf zinnen.
 * 2: Tien zinnen.
 */
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

/**
 * Verbeterde versie van randomWalkAlgoritme.
 * @param input Naam van de state.
 * @param size In relatie met het aantal zinnen die geconstrueerd moeten worden.
 * 0: Één zin.
 * 1: Vijf zinnen.
 * 2: Tien zinnen.
 */
void MarkovChain::testWalk(string &input, int size) {
    if (!wordExists(input)){ // Woord kan niet gebruikt worden als begin van een zin
        cerr<< "This word is not supported as begin!" << endl;
        exit(5);
    }
    vector<MarkovState*> Prevwords;
    vector<string> gegenereerdeT;
    currentState = states[input];
    gegenereerdeT.push_back(currentState->name);

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
    while (!stoppen) {
        vector<string> nextWords;
        for (const auto &transitionPair: currentState->transitions) {
            vector<string> v(transitionPair.second, transitionPair.first);
            nextWords.insert(nextWords.end(), v.begin(), v.end());
        }
        int v_size = nextWords.size();
        srand((int) time(0));
        index += rand() % 1000;
        int r = index % v_size;

        currentState = states[nextWords[r]];
        gegenereerdeT.push_back(currentState->name);
        if (states[nextWords[r]]->name[states[nextWords[r]]->name.size() - 1] == '.') {
            amountOfPeriods += 1;
            if (amountOfPeriods == amountOfSentences) {
                stoppen = true;
            }
        }
    }
    print(gegenereerdeT);
}

void MarkovChain::print(vector<string> ggT) {
    fstream output;
    output.open("output.txt", ios::out | ios::trunc);
    Parser hulp;
    int c = 0;
    for (auto &w : ggT){
        if (!hulp.isPunctuation(w[w.size()-1])){
            if (c != 0){
                output << " ";
            }
        }
        output << w;
        c++;
    }
    output.close();
}

void MarkovChain::addFirstOrder(vector<string> fO) {
    for (auto &el : fO){
        MarkovState* markovState = new MarkovState(el);
        this->addWord(markovState);
    }
}
