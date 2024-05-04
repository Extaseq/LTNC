#include "MyVector.h"

MyVector::MyVector()
{
    x = y = 0.0f;
}

MyVector::MyVector(float x, float y)
{
    this->x = x;
    this->y = y;
}

MyVector& MyVector::Add(const MyVector &other)
{
    this->x += other.x;
    this->y += other.y;
}

MyVector& MyVector::Subtract(const MyVector &other)
{
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

MyVector& MyVector::Multiply(const MyVector &other)
{
    this->x *= other.x;
    this->y *= other.y;

    return *this;
}

MyVector& MyVector::Divide(const MyVector &other)
{
    this->x /= other.x;
    this->y /= other.y;

    return *this;
}

MyVector& operator+(MyVector &v1, const MyVector &v2)
{
    return v1.Add(v2);
}

MyVector& operator-(MyVector &v1, const MyVector &v2)
{
    return v1.Subtract(v2);
}

MyVector& operator*(MyVector &v1, const MyVector &v2)
{
    return v1.Multiply(v2);
}

MyVector& operator/(MyVector &v1, const MyVector &v2)
{
    return v1.Divide(v2);
}

MyVector& MyVector::operator+=(const MyVector& vec)
{
    return this->Add(vec);
}

MyVector& MyVector::operator-=(const MyVector& vec)
{
    return this->Subtract(vec);
}

MyVector& MyVector::operator*=(const MyVector& vec)
{
    return this->Multiply(vec);
}

MyVector& MyVector::operator/=(const MyVector& vec)
{
    return this->Divide(vec);
}

MyVector& MyVector::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;

    return *this;
}

MyVector& MyVector::Zero()
{
    this->x = 0.0f;
    this->y = 0.0f;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const MyVector& vec)
{
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}
