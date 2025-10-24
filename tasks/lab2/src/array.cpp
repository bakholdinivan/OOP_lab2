#include "array.h"
#include <stdexcept>
// Этот класс взят как вспомогательный для дальнейшего решения задачи - разделил их в 2, потому что 
// изначально интерпретировал условие именно так

// [можно было бы сделать это все в одном классе -  изначально так и было, однако решил следовать
// четким инструкциям условия]


// --- Конструктор по умолчанию ---
// Инициализирует пустой массив (data = nullptr, size = 0)
// Такой объект не содержит данных, но может быть безопасно уничтожен
Array::Array() : data(nullptr), size(0) {}

// --- Конструктор с заполнением ---
// Создаёт массив размера n, где каждый элемент инициализируется значением t
// Память выделяется динамически, производится ручная инициализация
Array::Array(const size_t& n, unsigned char t) {
    size = n;
    data = new unsigned char[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = t; // Заполняем все элементы значением t
}

// --- Конструктор из списка инициализации ---
// Позволяет создать массив, например: Array a = {1,2,3}
// Размер массива равен числу элементов в списке
Array::Array(const std::initializer_list<unsigned char>& t) {
    size = t.size();
    data = new unsigned char[size];
    size_t i = 0;
    for (auto val : t)
        data[i++] = val; // Копируем значения из списка
}

// --- Конструктор из строки ---
// Каждый символ строки становится отдельным элементом массива
// Используется, например, для создания массива цифр по строковому вводу
Array::Array(const std::string& s) {
    size = s.size();
    data = new unsigned char[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = (s[i]); // Преобразуем char в unsigned char (неявно)
}

// --- Копирующий конструктор ---
// Создаёт глубокую копию другого массива: выделяет новую память и копирует элементы
Array::Array(const Array& other) {
    size = other.size;
    if (size > 0) {
        data = new unsigned char[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    } else {
        data = nullptr; // Если размер 0, не выделяем память
    }
}

// --- Перемещающий конструктор ---
// Забирает память и размер у временного объекта, не копируя данные
// После этого временный объект становится пустым (nullptr, 0)
Array::Array(Array&& other) noexcept {
    data = other.data;
    size = other.size;
    other.data = nullptr; // Очищаем исходный объект, чтобы не было double free
    other.size = 0;
}

// --- Метод копирования ---
// Позволяет копировать содержимое другого массива в текущий объект
// Если копируем себя в себя, ничего не делаем (self-assignment protection)
void Array::copyFrom(const Array& other) {
    if (this == &other) return; // Защита от самокопирования
    delete[] data; // Освобождаем старую память
    size = other.size;
    if (size > 0) {
        data = new unsigned char[size];
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    } else {
        data = nullptr;
    }
}

// --- Метод перемещения ---
// Аналогично перемещающему конструктору, но для уже существующего объекта
// Освобождает старую память, забирает данные у другого объекта, тот становится пустым
void Array::moveFrom(Array&& other) noexcept {
    if (this == &other) return; // Самоперемещение не имеет смысла
    delete[] data; // Освобождаем старую память
    data = other.data;
    size = other.size;
    other.data = nullptr; // Исходный объект становится пустым
    other.size = 0;
}

// --- Деструктор ---
// Освобождает выделенную память (delete[])
// После уничтожения объекта память не утечёт
// Сбрасываем data и size для безопасности (после delete[] data = nullptr безопасно)
Array::~Array() noexcept {
    delete[] data;
    data = nullptr;
    size = 0;
}

// --- Получение размера ---
// Возвращает текущее количество элементов в массиве
size_t Array::getSize() const { return size; }

// Метод записи значения в массив по индексу.
// Не предназначен для публичного использования после создания объекта —
// нужен только для корректной инициализации внутри класса или дружественных классов.
void Array::set(size_t i, unsigned char value) {
    if (i >= size) throw std::out_of_range("set: Индекс вне диапазона");
    data[i] = value;
}

// --- Доступ к элементу (константный вариант) ---
// Позволяет читать элементы у константных объектов Array (например, если Array объявлен const)
// Проверка границ аналогична неконстантной версии
const unsigned char& Array::at(size_t i) const {
    if (i >= size) throw std::out_of_range("Индекс вне диапазона");
    return data[i];
}