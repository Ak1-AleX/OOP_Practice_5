#pragma once
#include <cmath>
#include <QString>

class TComplex {
private:
    double re;
    double im;

public:
    TComplex();
    TComplex(double r, double i = 0.0);

    double real() const { return re; }
    double imag() const { return im; }

    void setReal(double r) { re = r; }
    void setImag(double i) { im = i; }

    // арифметика
    TComplex operator+(const TComplex& other) const;
    TComplex operator-(const TComplex& other) const;
    TComplex operator*(const TComplex& other) const;
    TComplex operator/(const TComplex& other) const;

    // оператор присваивания
    TComplex& operator=(const TComplex& other) {
        if (this != &other) {
            re = other.re;
            im = other.im;
        }
        return *this;
    }

    // сравнение
    bool operator==(const TComplex& other) const;
    bool operator!=(const TComplex& other) const;

    // модуль
    double abs() const;

    // сравнение по модулю и аргументу
    int compare(const TComplex& other) const;

    // методы для строкового представления
    QString toString() const;
    static TComplex fromString(const QString& str);
};
