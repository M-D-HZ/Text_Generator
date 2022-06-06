#include <iostream>
#include "vector"
#include "MarkovChain.h"
#include "HigherOrderMarkovChain.h"
//#include "../GUI/MainGuiWindow.h"

using namespace std;

int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    MainGuiWindow* GUI = new MainGuiWindow();
//    QMainWindow* QM = new QMainWindow();
//    GUI->setupUi(QM);
    string Filename = "Parse.txt";
    MarkovChain chain(Filename);
    string input = "We";
    chain.testWalk(input, 1);
//    chain.randomWalkAlgorithm(input,1);
//    QM->show();
//    return a.exec();
    return 0;
};