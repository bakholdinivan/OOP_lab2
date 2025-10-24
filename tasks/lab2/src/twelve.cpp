#include "twelve.h"
#include <stdexcept>
// В задаче я решил использовать перевод из 12-ричной СС в 10чную для облегчения реализации вычислений
// и лучше потенциальной масштабируемости программы, она не так сильно привязана к СС в условии
// СС объявляется еще в twelve.h константой





// Преобразование символа в цифру для двенадцатеричной системы счисления
// Символы '0'-'9' становятся числами 0-9, 'A'/'a' -> 10, 'B'/'b' -> 11
// Если символ не входит в допустимый диапазон, выбрасывается исключение
unsigned char Twelve::charToDigit(char c) {
    if (c >= '0' && c <= '9') return (c - '0'); // Цифры
    if (c == 'A' || c == 'a') return 10;        // Буква A
    if (c == 'B' || c == 'b') return 11;        // Буква B
    throw std::invalid_argument("Недопустимый символ");
}

// Преобразование цифры (0-11) обратно в символ
// 0-9 превращается в символы '0'-'9', 10 -> 'A', 11 -> 'B'
// Если цифра вне диапазона, выбрасывается исключение
char Twelve::digitToChar(unsigned char d) {
    if (d < 10) return ('0' + d); // Цифры
    if (d == 10) return 'A';      // 10 -> 'A'
    if (d == 11) return 'B';      // 11 -> 'B'
    throw std::invalid_argument("Недопустимая цифра");
}

// Конструктор по умолчанию создает объект, который хранит число 0
// digits(1, 0) — массив из одной цифры, равной 0
Twelve::Twelve() : digits(1, 0) {}

// Конструктор из строки, принимающей число в виде строки в 12-ричной системе
// digits(s.size(), 0) — резервируем массив под все цифры числа
// Цифры хранятся в обратном порядке: младший разряд — в начале массива
Twelve::Twelve(const std::string& s)
    : digits(s.size(), 0)
{
    if (s.empty()) throw std::invalid_argument("Пустая строка");
    size_t len = s.size();
    // Инициализация цифр числа через метод set, чтобы не нарушать иммутабельность
    for (size_t i = 0; i < len; ++i)
        digits.set(i, charToDigit(s[len - 1 - i]));
}

// Копирующий конструктор: создаёт новый объект с копией массива digits
Twelve::Twelve(const Twelve& other)
    : digits(other.digits)
{}

// Деструктор по умолчанию, освобождает память из digits (Array сам освобождает свою память)
Twelve::~Twelve() noexcept = default;

// Перевод числа из 12-ричной системы в 10-ричную (unsigned long long)
// Проходим по всем разрядам, умножая каждый на соответствующую степень 12
unsigned long long Twelve::toDecimal() const {
    unsigned long long result = 0, power = 1;
    // digits.getSize() — количество разрядов
    for (size_t i = 0; i < digits.getSize(); ++i) {
        result += digits.at(i) * power; // Добавляем значение разряда
        power *= BASE; // Переходим к следующей степени 12 (BASE == 12)
    }
    return result;
}

// Статический метод: создание объекта Twelve из 10-ричного числа
// Алгоритм: делим число на 12, запоминаем остатки (цифры) в tmp, затем строим строку
Twelve Twelve::fromDecimal(unsigned long long n) {
    if (n == 0) return Twelve("0"); // Особый случай: 0

    unsigned char tmp[64]; // Временный массив для хранения цифр (максимум 64 разряда)
    size_t cnt = 0;        // Количество цифр

    // Пока число не обнулится, делим на 12 и запоминаем остаток
    while (n > 0) {
        tmp[cnt++] = (n % BASE);
        n /= BASE;
    }

    // Составляем строку: старшие разряды — в начале строки
    std::string s;
    s.reserve(cnt);
    for (size_t i = 0; i < cnt; ++i)
        s += digitToChar(tmp[cnt - 1 - i]); // tmp хранит цифры в обратном порядке

    return Twelve(s); // Используем конструктор из строки
}

// Метод сложения: переводит оба числа в десятичную систему, складывает, возвращает результат как объект Twelve
Twelve Twelve::add(const Twelve& other) const {
    unsigned long long result = toDecimal() + other.toDecimal();
    return fromDecimal(result);
}

// Метод вычитания: переводит оба числа в десятичную, вычитает, если результат отрицательный — исключение
Twelve Twelve::sub(const Twelve& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    if (a < b) throw std::out_of_range("Отрицательный результат");
    return fromDecimal(a - b);
}

// Метод, возвращающий копию текущего объекта (использует копирующий конструктор)
Twelve Twelve::copy() const {
    return Twelve(*this);
}

// Метод сравнения: возвращает -1, если текущее число меньше other, 1 — больше, 0 — равны
int Twelve::compare(const Twelve& other) const {
    unsigned long long a = toDecimal();
    unsigned long long b = other.toDecimal();
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Преобразование числа в строку (12-ричная система)
// Проходим по массиву digits с конца (старший разряд), и формируем строку
std::string Twelve::toString() const {
    std::string s;
    // digits.getSize() — количество разрядов, проходим от старшего к младшему разряду
    for (int i = static_cast<int>(digits.getSize()) - 1; i >= 0; --i)
        s += digitToChar(digits.at(i));
    return s;
}