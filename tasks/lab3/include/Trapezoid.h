#pragma once
#include "Figure.h"

/**
 * @file Trapezoid.h
 * @brief Класс для представления трапеции
 */

/**
 * @class Trapezoid
 * @brief Класс Трапеция - наследник Figure
 * 
 * ТРАПЕЦИЯ - это четырехугольник с:
 * - Хотя бы одна пара параллельных сторон (основания)
 * - Другие стороны (боковые) могут быть не параллельны
 */
class Trapezoid : public Figure {
public:
    /**
     * @brief Конструктор по умолчанию
     * 
     * Создает трапецию с вершинами:
     * (0,0), (4,0), (3,2), (1,2)
     * Нижнее основание = 4, верхнее = 2, высота = 2
     */
    Trapezoid();
    
    /**
     * @brief Конструктор с заданными вершинами
     * @param p Массив из 4 точек
     */
    Trapezoid(const Point p[4]);
    
    // Правило пяти
    ~Trapezoid() override = default;
    Trapezoid(const Trapezoid& other);
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    
    // Виртуальные методы
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    const char* getType() const override { return "Trapezoid"; }
};