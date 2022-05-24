#include <iostream>
#include "vector"
#include "MarkovChain.h"

using namespace std;

int main(){
    string Filename = "Parse.txt";
    MarkovChain Chain(Filename);
    State* test = Chain.states["."];
//    cout << "Poopie" << endl;
    string input = "I";
    Chain.randomWalkAlgorithm(input);
};