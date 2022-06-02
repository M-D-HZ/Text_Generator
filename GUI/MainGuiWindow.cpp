#include "MainGuiWindow.h"
#include "../src/MarkovChain.h"
#include "fstream"
#include <iostream>

void MainGuiWindow::setupUi(QMainWindow *MainWindow){

    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(800, 600);
    MainWindow->setToolTipDuration(1);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    GenerateText = new QPushButton(centralwidget);
    GenerateText->setObjectName(QString::fromUtf8("GenerateText"));
    GenerateText->setGeometry(QRect(330, 120, 151, 41));
    textEdit = new QTextEdit(centralwidget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setGeometry(QRect(30, 120, 281, 391));
    textEdit_2 = new QTextEdit(centralwidget);
    textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
    textEdit_2->setGeometry(QRect(490, 120, 271, 391));
    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 26));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);


    retranslateUi(MainWindow);

    connect(GenerateText, SIGNAL(clicked()), this, SLOT(On_PushButton_Clicked()));

    QMetaObject::connectSlotsByName(MainWindow);
}

void MainGuiWindow::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    GenerateText->setText(QCoreApplication::translate("MainWindow", "Generate Text", nullptr));
}
string FindLastWord(){
    fstream outfile;
    outfile.open("Input.txt");
    if (!outfile.is_open()) {
        cerr << "File not found!" << endl;
        exit(5);
    }
    string current;
    while (outfile){
        string prev = current;
        getline(outfile, current, ' ');
        if (current == "." ||current == "!" ||current == ":" ||current == "?"){
            current = prev;
        }
    }
    return current;
}
void MainGuiWindow::On_PushButton_Clicked() {
    QFile InFile("Input.txt");
    InFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&InFile);
    QString Input = textEdit->toPlainText();
    out << Input;
    InFile.flush();
    InFile.close();


    string Filename = "MonkBoek.txt";
    MarkovChain chain(Filename);

    vector<string> words;
    string input = FindLastWord();
    chain.randomWalkAlgorithm(input,0);

//    QString filename = QFileDialog::getOpenFileName(this,"output.txt");
    QFile OutFile("output.txt");
    OutFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream oute(&OutFile);
    QString txt = oute.readAll();
    textEdit_2->setPlainText(txt);

    OutFile.close();
}

