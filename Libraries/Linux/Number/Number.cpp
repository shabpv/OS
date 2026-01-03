#include "pch.h"

#include "Number.h"
#include <stdexcept>

Number::Number(double val) : value(val) {}

Number Number::operator+(const Number& other) const {
    return Number(value + other.value);
}

Number Number::operator-(const Number& other) const {
    return Number(value - other.value);
}

Number Number::operator*(const Number& other) const {
    return Number(value * other.value);
}

Number Number::operator/(const Number& other) const {
    if (other.value == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return Number(value / other.value);
}

double Number::GetValue() const {
    return value;
}

Number Number::Create(double val) {
    return Number(val);
}

const Number Number::Zero(0.0);
const Number Number::One(1.0);