#pragma once
#include <iostream>

class MyVector
{
public:
    float x;

    float y;

    MyVector();

    MyVector(float x, float y);

    MyVector& Add(const MyVector &other);
    MyVector& Subtract(const MyVector &other);
    MyVector& Multiply(const MyVector &other);
    MyVector& Divide(const MyVector &other);

    friend MyVector& operator+(MyVector &v1, const MyVector &v2);
    friend MyVector& operator-(MyVector &v1, const MyVector &v2);
    friend MyVector& operator*(MyVector &v1, const MyVector &v2);
    friend MyVector& operator/(MyVector &v1, const MyVector &v2);

    MyVector& operator+=(const MyVector& vec);
    MyVector& operator-=(const MyVector& vec);
    MyVector& operator*=(const MyVector& vec);
    MyVector& operator/=(const MyVector& vec);

    MyVector& operator*(const int& i);
    MyVector& Zero();

    friend std::ostream& operator<<(std::ostream& os, const MyVector& vec);
};
