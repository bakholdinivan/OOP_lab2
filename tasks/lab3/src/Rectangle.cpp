#include "Rectangle.h"
#include <iostream>
#include <cmath>

/**
 * @file Rectangle.cpp
 * @brief Реализация методов класса Rectangle
 */

Rectangle::Rectangle() {
    Point p[4] = {Point(0, 0), Point(2, 0), Point(2, 1), Point(0, 1)};
    setPoints(p);
}

Rectangle::Rectangle(const Point p[4]) {
    setPoints(p);
}

Rectangle::Rectangle(const Rectangle& other) {
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
    return *this;
}

Rectangle::Rectangle(Rectangle&& other) noexcept {
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this == &other) return *this;
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
    return *this;
}

Point Rectangle::center() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 4; i++) {
        cx += points[i].x;
        cy += points[i].y;
    }
    return Point(cx / 4, cy / 4);
}

double Rectangle::area() const {
    double sum = 0;
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        sum += points[i].x * points[j].y;
        sum -= points[j].x * points[i].y;
    }
    return fabs(sum) / 2.0;
}

void Rectangle::print(std::ostream& os) const {
    os << "Rectangle: ";
    for (int i = 0; i < 4; i++) {
        os << "(" << points[i].x << "," << points[i].y << ")";
        if (i < 3) os << " ";
    }
}

void Rectangle::read(std::istream& is) {
    Point temp[4];
    for (int i = 0; i < 4; i++) {
        is >> temp[i].x >> temp[i].y;
    }
    setPoints(temp);
}