#ifndef TOG_TXT_GENERATOR_MAINGUIWINDOW_H
#define TOG_TXT_GENERATOR_MAINGUIWINDOW_H
#include <QVariant>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextEdit>
#include <QLineEdit>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include <QWidget>

using namespace std;

QT_BEGIN_NAMESPACE

class MainGuiWindow : public QMainWindow {
    Q_OBJECT
public:
    QWidget *centralwidget;
    QPushButton *GenerateText;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow);// setupUi

    void retranslateUi(QMainWindow *MainWindow); // retranslateUi
private slots:
    void On_PushButton_Clicked();


};

namespace Ui {
    class MainWindow: public MainGuiWindow {};
} // namespace Ui

QT_END_NAMESPACE
#endif //TOG_TXT_GENERATOR_MAINGUIWINDOW_H
