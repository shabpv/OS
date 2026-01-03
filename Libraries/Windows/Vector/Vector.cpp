#include "pch.h"

#define VECTOR_EXPORTS
#include "Vector.h"
#include <cmath>
#include <iostream>

Vector::Vector(Number xx, Number yy) : x(xx), y(yy) {}

Number Vector::GetX() const { return x; }
Number Vector::GetY() const { return y; }

Number Vector::GetRadius() const {
    double r = std::sqrt(x.GetValue() * x.GetValue() + y.GetValue() * y.GetValue());
    return Number::Create(r);
}

Number Vector::GetAngle() const {
    double angle = std::atan2(y.GetValue(), x.GetValue());
    return Number::Create(angle);
}

Vector Vector::Add(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

void Vector::Print() const {
    std::cout << "(" << x.GetValue() << ", " << y.GetValue() << ")"
        << " r=" << GetRadius().GetValue()
        << " phi=" << GetAngle().GetValue() << " rad\n";
}

const Vector Vector::ZeroVector(Number::Zero, Number::Zero);
const Vector Vector::OneOneVector(Number::One, Number::One);