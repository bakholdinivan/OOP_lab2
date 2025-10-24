#include "Trapezoid.h"
#include <iostream>
#include <cmath>

/**
 * @file Trapezoid.cpp
 * @brief Реализация методов класса Trapezoid
 */

Trapezoid::Trapezoid() {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    setPoints(p);
}

Trapezoid::Trapezoid(const Point p[4]) {
    setPoints(p);
}

Trapezoid::Trapezoid(const Trapezoid& other) {
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
    return *this;
}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept {
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this == &other) return *this;
    for (int i = 0; i < 4; i++) {
        points[i] = other.points[i];
    }
    return *this;
}

Point Trapezoid::center() const {
    double cx = 0, cy = 0;
    for (int i = 0; i < 4; i++) {
        cx += points[i].x;
        cy += points[i].y;
    }
    return Point(cx / 4, cy / 4);
}

double Trapezoid::area() const {
    double sum = 0;
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        sum += points[i].x * points[j].y;
        sum -= points[j].x * points[i].y;
    }
    return fabs(sum) / 2.0;
}

void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid: ";
    for (int i = 0; i < 4; i++) {
        os << "(" << points[i].x << "," << points[i].y << ")";
        if (i < 3) os << " ";
    }
}

void Trapezoid::read(std::istream& is) {
    Point temp[4];
    for (int i = 0; i < 4; i++) {
        is >> temp[i].x >> temp[i].y;
    }
    setPoints(temp);
}