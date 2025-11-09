/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *statusLabel;
    QGridLayout *gridLayout;
    QPushButton *inputPolynomButton;
    QPushButton *changeLeadingCoeffButton;
    QPushButton *changeRootButton;
    QPushButton *evaluateButton;
    QPushButton *showForm1Button;
    QPushButton *showForm2Button;
    QPushButton *exitButton;
    QLabel *resultLabel;
    QTextEdit *resultTextEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 500);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        verticalLayout->addWidget(statusLabel);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        inputPolynomButton = new QPushButton(centralwidget);
        inputPolynomButton->setObjectName(QString::fromUtf8("inputPolynomButton"));

        gridLayout->addWidget(inputPolynomButton, 0, 0, 1, 1);

        changeLeadingCoeffButton = new QPushButton(centralwidget);
        changeLeadingCoeffButton->setObjectName(QString::fromUtf8("changeLeadingCoeffButton"));

        gridLayout->addWidget(changeLeadingCoeffButton, 0, 1, 1, 1);

        changeRootButton = new QPushButton(centralwidget);
        changeRootButton->setObjectName(QString::fromUtf8("changeRootButton"));

        gridLayout->addWidget(changeRootButton, 1, 0, 1, 1);

        evaluateButton = new QPushButton(centralwidget);
        evaluateButton->setObjectName(QString::fromUtf8("evaluateButton"));

        gridLayout->addWidget(evaluateButton, 1, 1, 1, 1);

        showForm1Button = new QPushButton(centralwidget);
        showForm1Button->setObjectName(QString::fromUtf8("showForm1Button"));

        gridLayout->addWidget(showForm1Button, 2, 0, 1, 1);

        showForm2Button = new QPushButton(centralwidget);
        showForm2Button->setObjectName(QString::fromUtf8("showForm2Button"));

        gridLayout->addWidget(showForm2Button, 2, 1, 1, 1);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        gridLayout->addWidget(exitButton, 3, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));

        verticalLayout->addWidget(resultLabel);

        resultTextEdit = new QTextEdit(centralwidget);
        resultTextEdit->setObjectName(QString::fromUtf8("resultTextEdit"));
        resultTextEdit->setReadOnly(true);

        verticalLayout->addWidget(resultTextEdit);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260\320\274\320\270", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260\320\274\320\270 (\320\237\320\2403, \320\272\320\276\320\274\320\277\320\273\320\265\320\272\321\201\320\275\321\213\320\265 \321\207\320\270\321\201\320\273\320\260)", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\270\320\275\320\276\320\274 \320\275\320\265 \320\267\320\260\320\264\320\260\320\275", nullptr));
        inputPolynomButton->setText(QCoreApplication::translate("MainWindow", "1. \320\222\320\262\320\276\320\264 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260", nullptr));
        changeLeadingCoeffButton->setText(QCoreApplication::translate("MainWindow", "2. \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \321\201\321\202\320\260\321\200\321\210\320\270\320\271 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 an", nullptr));
        changeRootButton->setText(QCoreApplication::translate("MainWindow", "3. \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\272\320\276\321\200\320\265\320\275\321\214 \320\277\320\276 \320\270\320\275\320\264\320\265\320\272\321\201\321\203", nullptr));
        evaluateButton->setText(QCoreApplication::translate("MainWindow", "4. \320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \320\262 \321\202\320\276\321\207\320\272\320\265", nullptr));
        showForm1Button->setText(QCoreApplication::translate("MainWindow", "5. \320\222\321\213\320\262\320\265\321\201\321\202\320\270 \320\277\320\276\320\273\320\270\320\275\320\276\320\274 (\321\204\320\276\321\200\320\274\320\260 \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\320\276\320\262)", nullptr));
        showForm2Button->setText(QCoreApplication::translate("MainWindow", "6. \320\222\321\213\320\262\320\265\321\201\321\202\320\270 \320\277\320\276\320\273\320\270\320\275\320\276\320\274 (\321\204\320\276\321\200\320\274\320\260 \320\272\320\276\321\200\320\275\320\265\320\271)", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "7. \320\222\321\213\321\205\320\276\320\264", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
