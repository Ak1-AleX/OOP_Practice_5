#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <Qdebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Работа с полиномами (ПР5, клиент)");

    // инициализация клиентского приложения
    clientApp = new ClientApp(this);
    connect(clientApp, &ClientApp::responseReceived, this, &MainWindow::onServerResponse);
    connect(clientApp, &ClientApp::errorOccurred, this, &MainWindow::onServerError);

    // запуск клиента
    if (!clientApp->start()) {
        showError("Не удалось запустить клиент");
    } else {
        showInfo("Клиент запущен. Ожидание подключения к серверу...");
    }

    updateDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplay()
{
    ui->statusLabel->setText("Клиентское приложение");
}

// новые методы для обработки ответов от сервера
void MainWindow::onServerResponse(const QString& result) {
    ui->resultTextEdit->setPlainText(result);
    showInfo("Операция выполнена успешно");
}

void MainWindow::onServerError(const QString& error) {
    showError(error);
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::showInfo(const QString& message)
{
    QMessageBox::information(this, "Информация", message);
}

void MainWindow::on_inputPolynomButton_clicked() {
    bool ok;

    int degree = QInputDialog::getInt(this, "Ввод полинома",
                                      "Введите степень полинома:", 2, 0, 10, 1, &ok);
    if (!ok) return;

    if (degree == 0) {
        QVector<QString> roots;
        clientApp->createPolynom(0, "1", roots);  // вызов клиента вместо прямой работы
        return;
    }

    QString coeffText = QInputDialog::getText(this, "Старший коэффициент",
                                              "Введите старший коэффициент an (формат: число или a+bi):",
                                              QLineEdit::Normal, "1", &ok);
    if (!ok || coeffText.isEmpty()) return;

    QVector<QString> roots;
    for (int i = 0; i < degree; i++) {
        QString rootText = QInputDialog::getText(this, QString("Корень %1").arg(i+1),
                                                 QString("Введите корень %1 (формат: число или a+bi):").arg(i+1),
                                                 QLineEdit::Normal, "0", &ok);
        if (!ok) return;
        roots.append(rootText);
    }

    // отправка запроса вместо прямой работы с полиномом
    clientApp->createPolynom(degree, coeffText, roots);
}

void MainWindow::on_changeLeadingCoeffButton_clicked() {
    bool ok;
    QString coeffText = QInputDialog::getText(this, "Изменение старшего коэффициента",
                                              "Введите новый старший коэффициент an:",
                                              QLineEdit::Normal, "1", &ok);
    if (!ok || coeffText.isEmpty()) return;

    clientApp->changeLeadingCoeff(coeffText);  // вызов клиента
}

void MainWindow::on_changeRootButton_clicked() {
    bool ok;
    int index = QInputDialog::getInt(this, "Изменение корня",
                                     "Введите индекс корня (начинается с 0):",
                                     0, 0, 10, 1, &ok);
    if (!ok) return;

    QString rootText = QInputDialog::getText(this, "Изменение корня",
                                             QString("Введите новое значение корня %1:").arg(index),
                                             QLineEdit::Normal, "0", &ok);
    if (!ok || rootText.isEmpty()) return;

    clientApp->changeRoot(index, rootText);  // вызов клиента
}

void MainWindow::on_evaluateButton_clicked() {
    bool ok;
    QString pointText = QInputDialog::getText(this, "Вычисление значения",
                                              "Введите точку x для вычисления:",
                                              QLineEdit::Normal, "0", &ok);
    if (!ok || pointText.isEmpty()) return;

    clientApp->evaluate(pointText);  // вызов клиента
}

void MainWindow::on_showForm1Button_clicked() {
    clientApp->getForm1();  // вызов клиента
}

void MainWindow::on_showForm2Button_clicked() {
    clientApp->getForm2();  // вызов клиента
}

void MainWindow::on_exitButton_clicked()
{
    close();
}
