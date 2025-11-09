#include "polynom.h"
#include <cmath>
#include <QString>
#include <QVector>
#include <QDebug>

Polynom::Polynom() : degree(0), leadingCoeff(number(1.0, 0.0)) {
    coefficients = Array(1, number(0.0, 0.0));
    roots = Array(0);
}

Polynom::Polynom(int n, number an) : degree(n), leadingCoeff(an) {
    if (n > 0) {
        coefficients = Array(n + 1, number(0.0, 0.0));
        roots = Array(n, number(0.0, 0.0));
        coefficients.setElement(n, an);
    } else {
        degree = 0;
        coefficients = Array(1, number(0.0, 0.0));
        roots = Array(0);
    }
}

void Polynom::calculateCoefficients() {
    if (degree <= 0) {
        coefficients = Array(1, leadingCoeff);
        return;
    }

    coefficients = Array(degree + 1, number(0.0, 0.0));

    // a_n = leadingCoeff
    coefficients.setElement(degree, leadingCoeff);

    // Вычисляем остальные коэффициенты через элементарные симметрические полиномы
    for (int k = 1; k <= degree; k++) {
        number sum = number(0.0, 0.0);

        // Сумма произведений k различных корней
        for (int i = 0; i < degree; i++) {
            number product = number(1.0, 0.0);
            int count = 0;

            for (int j = i; j < degree && count < k; j++) {
                product = product * roots.getElement(j);
                count++;
            }

            if (count == k) {
                sum = sum + product;
            }
        }

        // Коэффициент a_{n-k} = (-1)^k * an * sum
        if (k % 2 == 0) {
            coefficients.setElement(degree - k, leadingCoeff * sum);
        } else {
            coefficients.setElement(degree - k, number(-1.0, 0.0) * leadingCoeff * sum);
        }
    }
}

number Polynom::evaluate(number x) const {
    if (isEmpty()) return number(0.0, 0.0);

    // Схема Горнера
    number result = coefficients.getElement(degree);
    for (int i = degree - 1; i >= 0; i--) {
        result = result * x + coefficients.getElement(i);
    }
    return result;
}

number Polynom::getCoefficient(int index) const {
    if (index >= 0 && index <= degree) {
        return coefficients.getElement(index);
    }
    return number(0.0, 0.0);
}

void Polynom::setLeadingCoeff(number an) {
    leadingCoeff = an;
    calculateCoefficients();
}

void Polynom::setRoot(int index, number root) {
    if (index >= 0 && index < degree) {
        roots.setElement(index, root);
        calculateCoefficients();
    }
}

number Polynom::getRoot(int index) const {
    if (index >= 0 && index < degree) {
        return roots.getElement(index);
    }
    return number(0.0, 0.0);
}

QString Polynom::toStringForm1() const {
    if (isEmpty()) return "P(x) = 0";

    QString result = "P(x) = ";
    bool firstTerm = true;

    for (int i = degree; i >= 0; i--) {
        number coeff = coefficients.getElement(i);
        
        // Пропускаем нулевые коэффициенты (кроме нулей)
        if (coeff == number(0.0, 0.0)) continue;

        if (!firstTerm) {
            if (coeff.real() >= 0 && coeff.imag() >= 0) {
                result += " + ";
            } else {
                result += " - ";
                coeff = number(-coeff.real(), -coeff.imag());
            }
        }

        result += "(" + coeff.toString() + ")";

        if (i > 0) {
            result += "x";
            if (i > 1) {
                result += QString("^%1").arg(i);
            }
        }

        firstTerm = false;
    }

    if (firstTerm) {
        result += "0";
    }
    return result;
}

QString Polynom::toStringForm2() const {
    if (isEmpty()) return "P(x) = 0";

    QString result = "P(x) = " + leadingCoeff.toString();
    for (int i = 0; i < degree; i++) {
        number root = roots.getElement(i);
        result += QString("(x - (%1))").arg(root.toString());
    }
    return result;
}

void Polynom::setFromRoots(int n, number an, const QVector<number>& rootsList) {
    degree = n;
    leadingCoeff = an;
    
    if (n > 0) {
        roots = Array(n, number(0.0, 0.0));
        for (int i = 0; i < n && i < rootsList.size(); i++) {
            roots.setElement(i, rootsList[i]);
        }
        calculateCoefficients();
    } else {
        coefficients = Array(1, number(0.0, 0.0));
        roots = Array(0);
    }
}
