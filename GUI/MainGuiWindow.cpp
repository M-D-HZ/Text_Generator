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

    widget1 = new QWidget(centralwidget);
    widget1->setObjectName(QString::fromUtf8("widget1"));
    widget1->setGeometry(QRect(20, 100, 361, 431));

    verticalLayout_2 = new QVBoxLayout(widget1);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));


    GenerateText = new QPushButton(widget1);
    GenerateText->setObjectName(QString::fromUtf8("Generate Text"));
//    GenerateText->setGeometry(QRect(320, 120, 161, 41));

    horizontalLayout_3->addWidget(GenerateText);

    comboBox = new QComboBox(widget1);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
//    comboBox->setGeometry(QRect(320, 120, 161, 41));
    comboBox->addItem("Small text");
    comboBox->addItem("Medium sized text");
    comboBox->addItem("Large text");

    horizontalLayout_3->addWidget(comboBox);
    verticalLayout_2->addLayout(horizontalLayout_3);

    textEdit = new QTextEdit(widget1);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
//    textEdit->setGeometry(QRect(30, 120, 281, 391));

    verticalLayout_2->addWidget(textEdit);

    widget = new QWidget(centralwidget);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(400, 100, 371, 431)); //20, 102, 361, 431

    verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

    SaveText = new QPushButton(widget);
    SaveText->setObjectName(QString::fromUtf8("Save Text"));
//    SaveText->setGeometry(QRect(490, 80, 131, 29));
    SaveText->setText("Save Text");

    horizontalLayout_2->addWidget(SaveText);

    ClearText = new QPushButton(widget);
    ClearText->setObjectName(QString::fromUtf8("Clear Text"));
//    ClearText->setGeometry(QRect(632, 80, 131, 29));
    ClearText->setText("Clear Text");

    horizontalLayout_2->addWidget(ClearText);
    verticalLayout->addLayout(horizontalLayout_2);

    textEdit_2 = new QTextEdit(widget);
    textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
//    textEdit_2->setGeometry(QRect(490, 120, 271, 391));

    verticalLayout->addWidget(textEdit_2);


    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 26));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);


    retranslateUi(MainWindow);

    connect(GenerateText, SIGNAL(clicked()), this, SLOT(On_GenerateText_Clicked()));
    connect(SaveText, SIGNAL(clicked()), this, SLOT(On_SaveText_Clicked()));
    connect(ClearText, SIGNAL(clicked()), this, SLOT(On_ClearText_Clicked()));

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
        if (current == "." ||current == "!" ||current == ":" ||current == "?" || current == " "){
            current = prev;
        }
    }
    return current;
}
void MainGuiWindow::On_GenerateText_Clicked() {
    if (textEdit->toPlainText().isEmpty()){
        textEdit_2->setPlainText("Please enter something in the left side.");
        return;
    }
    QFile InFile("Input.txt");
    InFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&InFile);
    QString Input = textEdit->toPlainText();
    out << Input;
    InFile.flush();
    InFile.close();

    cout << comboBox->currentIndex() << endl;
    string Filename = "MonkBoek.txt";
    MarkovChain chain(Filename);

    vector<string> words;
    string input = FindLastWord();
    if (!chain.wordExists(input)){
        textEdit_2->setPlainText("Word does not exist in library");
        return;
    }
    chain.randomWalkAlgorithm(input,comboBox->currentIndex());

//    QString filename = QFileDialog::getOpenFileName(this,"output.txt");
    QFile OutFile("output.txt");
    OutFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream oute(&OutFile);
    QString txt = oute.readAll();
    textEdit_2->setPlainText(txt);

    OutFile.close();
}

void MainGuiWindow::On_SaveText_Clicked(){
    cout << "hahaha u tried to save bozo" << endl;
    QString filename = QFileDialog::getSaveFileName(this);
    QFile InFile(filename);
    InFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&InFile);
    QString Input = textEdit_2->toPlainText();
    out << Input;
    InFile.flush();
    InFile.close();

}

void MainGuiWindow::On_ClearText_Clicked(){
    cout << "hahaha u tried to clear bozo" << endl;
    textEdit_2->setPlainText("");
}