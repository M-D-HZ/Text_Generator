#include <iostream>
#include "vector"
#include "MarkovChain.h"
#include "../GUI/MainGuiWindow.h"

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainGuiWindow* GUI = new MainGuiWindow();
    QMainWindow* QM = new QMainWindow();
    GUI->setupUi(QM);
//    string Filename = "MonkBoek.txt";
//    MarkovChain chain(Filename);
//    MarkovState* test = chain.states["I"];
////    cout << "Poopie" << endl;
//    string input = "I";
//    chain.randomWalkAlgorithm(input,0);
    QM->show();
    return a.exec();
};