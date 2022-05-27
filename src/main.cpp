#include <iostream>
#include "vector"
#include "MarkovChain.h"

using namespace std;

int main(){
    string Filename = "Parse.txt";
    MarkovChain chain(Filename);
    MarkovState* test = chain.states["."];
//    cout << "Poopie" << endl;
    string input = "the";
    chain.randomWalkAlgorithm(input);
};