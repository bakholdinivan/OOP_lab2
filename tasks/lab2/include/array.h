#pragma once
#include <string>
#include <initializer_list>
#include <cstddef>

class Array {
private:
    unsigned char* data;
    size_t size;

public:
    // --- Конструктор по умолчанию ---
    Array();

    // --- Конструктор с заполнением ---
    Array(const size_t& n, unsigned char t);

    // --- Конструктор из списка инициализации ---
    Array(const std::initializer_list<unsigned char>& t);

    // --- Конструктор из строки ---
    Array(const std::string& s);

    // --- Копирующий конструктор ---
    Array(const Array& other);

    // --- Перемещающий конструктор ---
    Array(Array&& other) noexcept;

    // --- Деструктор ---
    ~Array() noexcept;

    // --- Метод копирования ---
    void copyFrom(const Array& other);

    // --- Метод перемещения ---
    void moveFrom(Array&& other) noexcept;

    // --- Получение размера ---
    size_t getSize() const;

    // Метод для безопасной инициализации элемента массива по индексу
    void set(size_t i, unsigned char value);
    
    // --- Доступ к элементу ---
    const unsigned char& at(size_t i) const;
};