#include "array.h"
#include <cmath>
#include <algorithm>
#include <QDebug>

using namespace std;

Array::Array() : data() {}

Array::Array(int n, number val) : data(n, val) {}

Array::Array(const Array& other) : data(other.data) {}

void Array::resize(int newSize) {
    if (newSize > 0) {
        data.resize(newSize);
    } else {
        data.clear();
    }
}

void Array::setElement(int index, number val) {
    if (index >= 0 && index < data.size()) {
        data[index] = val;
    } else {
        qDebug() << "Array::setElement: index out of bounds" << index << "size:" << data.size();
    }
}

number Array::getElement(int index) const {
    if (index >= 0 && index < data.size()) {
        return data[index];
    }
    qDebug() << "Array::getElement: index out of bounds" << index << "size:" << data.size();
    return number(0.0, 0.0);
}

number Array::average() const {
    if (data.isEmpty()) return number(0.0, 0.0);

    double sumRe = 0, sumIm = 0;
    for (const number& num : data) {
        sumRe += num.real();
        sumIm += num.imag();
    }
    return number(sumRe / data.size(), sumIm / data.size());
}

number Array::deviation() const {
    if (data.isEmpty()) return number(0.0, 0.0);

    number avg = average();
    double sum = 0;
    for (const number& num : data) {
        double dRe = num.real() - avg.real();
        double dIm = num.imag() - avg.imag();
        double distance = sqrt(dRe * dRe + dIm * dIm);
        sum += distance * distance;
    }
    return number(sqrt(sum / data.size() - 1), 0);
}

void Array::sortAsc() {
    if (!data.isEmpty()) {
        sort(data.begin(), data.end(), [](const number& a, const number& b) {
            return a.compare(b) < 0;
        });
    }
}

void Array::sortDesc() {
    if (!data.isEmpty()) {
        sort(data.begin(), data.end(), [](const number& a, const number& b) {
            return a.compare(b) > 0;
        });
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}
