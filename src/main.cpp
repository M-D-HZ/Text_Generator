#include <iostream>
#include "vector"
#include "MarkovChain.h"
#include "HigherOrderMarkovChain.h"
//#include "../GUI/MainGuiWindow.h"

using namespace std;

int main(int argc, char *argv[]){
    cout << "test" << endl;
//    QApplication a(argc, argv);
//    MainGuiWindow* GUI = new MainGuiWindow();
//    QMainWindow* QM = new QMainWindow();
//    GUI->setupUi(QM);
    string Filename = "MonkBoek.txt";
    MarkovChain chain(Filename);
    string input = "I";
    chain.testWalk(input);
//    chain.randomWalkAlgorithm(input,1);
//    QM->show();
//    return a.exec();
    return 0;
};