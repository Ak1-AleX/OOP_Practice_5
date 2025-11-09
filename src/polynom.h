#pragma once
#ifndef POLYNOM_H
#define POLYNOM_H

#include "array.h"
#include <QString>
#include <QVector>

class Polynom {
private:
    Array coefficients;
    Array roots;
    int degree;
    number leadingCoeff;

    void calculateCoefficients();

public:
    Polynom();
    Polynom(int n, number an = number(1.0, 0.0));

    // основные методы
    number evaluate(number x) const;

    // методы доступа
    int getDegree() const { return degree; }
    number getCoefficient(int index) const;
    number getLeadingCoeff() const { return leadingCoeff; }
    void setLeadingCoeff(number an);
    void setRoot(int index, number root);
    number getRoot(int index) const;

    bool isEmpty() const { return degree == 0; }
    
    // методы для GUI
    QString toStringForm1() const;
    QString toStringForm2() const;
    void setFromRoots(int n, number an, const QVector<number>& rootsList);
};

#endif // POLYNOM_H
