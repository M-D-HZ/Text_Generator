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
#include <QComboBox>
#include <QStatusBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>


using namespace std;

QT_BEGIN_NAMESPACE

class MainGuiWindow : public QMainWindow {
    Q_OBJECT
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *widget1;
    QPushButton *GenerateText;
    QPushButton *SaveText;
    QPushButton *ClearText;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QMenuBar *menubar;
    QComboBox *comboBox;
    QStatusBar *statusbar;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;

    void setupUi(QMainWindow *MainWindow);// setupUi

    void retranslateUi(QMainWindow *MainWindow); // retranslateUi
private slots:
    void On_GenerateText_Clicked();
    void On_SaveText_Clicked();
    void On_ClearText_Clicked();
};

namespace Ui {
    class MainWindow: public MainGuiWindow {};
} // namespace Ui

QT_END_NAMESPACE
#endif //TOG_TXT_GENERATOR_MAINGUIWINDOW_H
