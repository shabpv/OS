#pragma once
#include "Number.h"

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

class VECTOR_API Vector {
private:
    Number x;
    Number y;

public:
    Vector(Number xx = Number::Zero, Number yy = Number::Zero);

    Number GetX() const;
    Number GetY() const;

    Number GetRadius() const;
    Number GetAngle() const;

    Vector Add(const Vector& other) const;

    void Print() const;

    static const Vector ZeroVector;
    static const Vector OneOneVector;
};