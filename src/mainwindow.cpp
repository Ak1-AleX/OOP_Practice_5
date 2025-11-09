#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Работа с полиномами (ПР3, комплексные числа)");
    updateDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDisplay()
{
    QString status = currentPolynom.isEmpty() ? 
        "Полином не задан" : 
        QString("Степень: %1").arg(currentPolynom.getDegree());
    ui->statusLabel->setText(status);
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::showInfo(const QString& message)
{
    QMessageBox::information(this, "Информация", message);
}

void MainWindow::on_inputPolynomButton_clicked()
{
    bool ok;
    
    // Ввод степени
    int degree = QInputDialog::getInt(this, "Ввод полинома", 
                                     "Введите степень полинома:", 2, 0, 10, 1, &ok);
    if (!ok) return;

    if (degree == 0) {
        currentPolynom = Polynom(0, number(1.0, 0.0));
        showInfo("Создан нулевой полином");
        updateDisplay();
        return;
    }

    // Ввод старшего коэффициента
    QString coeffText = QInputDialog::getText(this, "Старший коэффициент",
                                             "Введите старший коэффициент an (формат: число или a+bi):",
                                             QLineEdit::Normal, "1", &ok);
    if (!ok || coeffText.isEmpty()) return;

    number leadingCoeff = number::fromString(coeffText);

    // Ввод корней
    QVector<number> roots;
    for (int i = 0; i < degree; i++) {
        QString rootText = QInputDialog::getText(this, QString("Корень %1").arg(i+1),
                                                QString("Введите корень %1 (формат: число или a+bi):").arg(i+1),
                                                QLineEdit::Normal, "0", &ok);
        if (!ok) return;
        
        number root = number::fromString(rootText);
        roots.append(root);
    }

    // Создаем полином
    currentPolynom.setFromRoots(degree, leadingCoeff, roots);
    showInfo("Полином создан успешно!");
    updateDisplay();
    
    // Показываем результат
    ui->resultTextEdit->setPlainText(
        QString("Полином создан:\n\n%1\n\n%2")
            .arg(currentPolynom.toStringForm1())
            .arg(currentPolynom.toStringForm2())
    );
}

void MainWindow::on_changeLeadingCoeffButton_clicked()
{
    if (currentPolynom.isEmpty()) {
        showError("Ошибка: полином не задан!");
        return;
    }

    bool ok;
    QString coeffText = QInputDialog::getText(this, "Изменение старшего коэффициента",
                                             QString("Текущий an: %1\nВведите новый an:")
                                             .arg(currentPolynom.getLeadingCoeff().toString()),
                                             QLineEdit::Normal, "", &ok);
    if (!ok || coeffText.isEmpty()) return;

    number newCoeff = number::fromString(coeffText);
    currentPolynom.setLeadingCoeff(newCoeff);
    showInfo("Коэффициент an изменен!");
    updateDisplay();
}

void MainWindow::on_changeRootButton_clicked()
{
    if (currentPolynom.isEmpty()) {
        showError("Ошибка: полином не задан!");
        return;
    }

    bool ok;
    int index = QInputDialog::getInt(this, "Изменение корня",
                                    QString("Введите индекс корня (0-%1):")
                                    .arg(currentPolynom.getDegree() - 1),
                                    0, 0, currentPolynom.getDegree() - 1, 1, &ok);
    if (!ok) return;

    QString rootText = QInputDialog::getText(this, "Изменение корня",
                                            QString("Текущий корень %1: %2\nВведите новый корень:")
                                            .arg(index).arg(currentPolynom.getRoot(index).toString()),
                                            QLineEdit::Normal, "", &ok);
    if (!ok || rootText.isEmpty()) return;

    number newRoot = number::fromString(rootText);
    currentPolynom.setRoot(index, newRoot);
    showInfo("Корень изменен!");
    updateDisplay();
}

void MainWindow::on_evaluateButton_clicked()
{
    if (currentPolynom.isEmpty()) {
        showError("Ошибка: полином не задан!");
        return;
    }

    bool ok;
    QString pointText = QInputDialog::getText(this, "Вычисление значения",
                                             "Введите точку x:",
                                             QLineEdit::Normal, "0", &ok);
    if (!ok || pointText.isEmpty()) return;

    number x = number::fromString(pointText);
    number result = currentPolynom.evaluate(x);
    
    showInfo(QString("P(%1) = %2").arg(x.toString()).arg(result.toString()));
}

void MainWindow::on_showForm1Button_clicked()
{
    if (currentPolynom.isEmpty()) {
        showError("Ошибка: полином не задан!");
        return;
    }
    
    ui->resultTextEdit->setPlainText(currentPolynom.toStringForm1());
}

void MainWindow::on_showForm2Button_clicked()
{
    if (currentPolynom.isEmpty()) {
        showError("Ошибка: полином не задан!");
        return;
    }
    
    ui->resultTextEdit->setPlainText(currentPolynom.toStringForm2());
}

void MainWindow::on_exitButton_clicked()
{
    close();
}
