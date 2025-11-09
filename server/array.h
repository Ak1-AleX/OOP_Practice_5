#pragma once

#include "number.h"
#include <QVector>

class Array {
private:
    QVector<number> data;  // Исп QVector тк с указателями были вылеты

public:
    Array();
    Array(int n, number val = number(0.0));
    Array(const Array& other);
    ~Array() = default;  // QVector сам управляет памятью

    void resize(int newSize);
    void setElement(int index, number val);
    number getElement(int index) const;

    number average() const;
    number deviation() const;

    void sortAsc();
    void sortDesc();

    bool isEmpty() const { return data.isEmpty(); }
    int getSize() const { return data.size(); }
    
    // Оператор присваивания
    Array& operator=(const Array& other);
};
