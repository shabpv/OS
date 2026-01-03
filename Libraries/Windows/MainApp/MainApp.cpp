#include <iostream>
#include "Number.h"
#include "Vector.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "=== Демонстрация библиотеки Number ===\n";
    Number a = Number::Create(10.0);
    Number b = Number::One;
    Number c = a + b;
    Number d = a - b * a / b;
    std::cout << "a = " << a.GetValue() << "\n";
    std::cout << "Zero = " << Number::Zero.GetValue() << "\n";
    std::cout << "One = " << Number::One.GetValue() << "\n";
    std::cout << "c = a + b = " << c.GetValue() << "\n";
    std::cout << "d = a - b*a/b = " << d.GetValue() << "\n\n";

    std::cout << "=== Демонстрация библиотеки Vector ===\n";
    Vector v1(Number::Create(3.0), Number::Create(4.0));
    Vector v2 = Vector::OneOneVector;
    Vector sum = v1.Add(v2);

    std::cout << "v1 "; v1.Print();
    std::cout << "v2 (1,1) "; v2.Print();
    std::cout << "sum "; sum.Print();
    std::cout << "ZeroVector "; Vector::ZeroVector.Print();

    return 0;
}