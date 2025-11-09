#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "polynom.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputPolynomButton_clicked();
    void on_changeLeadingCoeffButton_clicked();
    void on_changeRootButton_clicked();
    void on_evaluateButton_clicked();
    void on_showForm1Button_clicked();
    void on_showForm2Button_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    Polynom currentPolynom;
    
    void updateDisplay();
    void showError(const QString& message);
    void showInfo(const QString& message);
};

#endif