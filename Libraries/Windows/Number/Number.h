#pragma once

class Number {
private:
    double value;

public:
    Number(double val = 0.0);

    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;

    double GetValue() const;

    static Number Create(double val);

    static const Number Zero;
    static const Number One;
};