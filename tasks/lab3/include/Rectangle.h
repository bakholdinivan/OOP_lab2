#pragma once
#include "Figure.h"

/**
 * @file Rectangle.h
 * @brief Класс для представления прямоугольника
 */

/**
 * @class Rectangle
 * @brief Класс Прямоугольник - наследник Figure
 * 
 * ПРЯМОУГОЛЬНИК - это четырехугольник с:
 * - Противоположные стороны равны
 * - 4 прямых угла (90°)
 * - НЕ все стороны равны (иначе это квадрат)
 */
class Rectangle : public Figure {
public:
    /**
     * @brief Конструктор по умолчанию
     * 
     * Создает прямоугольник 2x1 с вершинами:
     * (0,0), (2,0), (2,1), (0,1)
     */
    Rectangle();
    
    /**
     * @brief Конструктор с заданными вершинами
     * @param p Массив из 4 точек
     */
    Rectangle(const Point p[4]);
    
    // Правило пяти
    ~Rectangle() override = default;
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(Rectangle&& other) noexcept;
    
    // Виртуальные методы
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    const char* getType() const override { return "Rectangle"; }
};