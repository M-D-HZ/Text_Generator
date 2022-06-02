#include <iostream>
#include "vector"
#include "MarkovChain.h"

using namespace std;

int main(){
    string Filename = "MonkBoek.txt";
    MarkovChain chain(Filename);
    MarkovState* test = chain.states["I"];
//    cout << "Poopie" << endl;
    string input = "I";
    chain.randomWalkAlgorithm(input,0);
};