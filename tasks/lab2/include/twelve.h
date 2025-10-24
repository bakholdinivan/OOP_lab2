#pragma once
#include "array.h"
#include <string>

class Twelve {
private:
    Array digits;
    static constexpr unsigned char BASE = 12;

    static unsigned char charToDigit(char c);
    static char digitToChar(unsigned char d);

public:
    // Конструкторы и деструктор
    Twelve();                            // по умолчанию (0)
    explicit Twelve(const std::string&); // из строки
    Twelve(const Twelve& other);         // копирующий
    ~Twelve() noexcept;

    // Основные операции
    unsigned long long toDecimal() const;
    static Twelve fromDecimal(unsigned long long n);
    Twelve add(const Twelve& other) const;
    Twelve sub(const Twelve& other) const;
    Twelve copy() const;
    int compare(const Twelve& other) const;

    // Вывод
    std::string toString() const;
};
