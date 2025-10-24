#include "Figure.h"
#include <cmath>
#include <algorithm>

/**
 * @file Figure.cpp
 * @brief Реализация методов базового класса Figure
 */

// ===================================================================
// УПОРЯДОЧИВАНИЕ ТОЧЕК
// ===================================================================

/*
  Упорядочивает 4 вершины против часовой стрелки.

  Формула Гаусса (Shoelace) и формулы центроида требуют обхода вершин
  по контуру; если вершины заданы в произвольном порядке, результат
  будет некорректен.

  Алгоритм:
  1) Находим центр масс (среднее всех точек).
  2) Для каждой точки вычисляем угол относительно центра: atan2(y - cy, x - cx).
  3) Сортируем точки по углу (возрастание) — получаем обход против часовой.

  Для n=4 используется простой O(n^2) обменный метод — читабельно и быстро.
  Пограничные случаи (коллинеарные точки, совпадение точек) должны обрабатываться
  при валидации входных данных.
*/
void Figure::sortPoints() {
    // Шаг 1: центр масс (среднее)
    double cx = 0, cy = 0;
    for (int i = 0; i < 4; i++) {
        cx += points[i].x;
        cy += points[i].y;
    }
    cx /= 4;
    cy /= 4;

    struct PointAngle {
        Point p;
        double angle; // угол в радианах (-π..π)
    };
    PointAngle pa[4];

    // Шаг 2: вычисляем углы относительно центра
    for (int i = 0; i < 4; i++) {
        pa[i].p = points[i];
        pa[i].angle = atan2(points[i].y - cy, points[i].x - cx);
    }

    // Шаг 3: простая сортировка по углу (для 4 элементов приемлемо)
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (pa[i].angle > pa[j].angle) {
                std::swap(pa[i], pa[j]);
            }
        }
    }

    // Копируем отсортированные точки обратно
    for (int i = 0; i < 4; i++) points[i] = pa[i].p;
}

// ===================================================================
// МЕТОДЫ РАБОТЫ С ВЕРШИНАМИ
// ===================================================================

/*
  Копирует массив точек и упорядочивает их (вызывает sortPoints()).
  Контракт: p содержит ровно 4 корректные точки.
*/
void Figure::setPoints(const Point p[4]) {
    for (int i = 0; i < 4; i++) points[i] = p[i];
    sortPoints();
}

// ===================================================================
// ПРАВИЛО ПЯТИ (конструкторы/операторы)
// ===================================================================

Figure::Figure(const Figure& other) {
    for (int i = 0; i < 4; i++) points[i] = other.points[i];
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) points[i] = other.points[i];
    }
    return *this;
}

Figure::Figure(Figure&& other) noexcept {
    for (int i = 0; i < 4; i++) points[i] = other.points[i];
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; i++) points[i] = other.points[i];
    }
    return *this;
}

// ===================================================================
// ОПЕРАТОР СРАВНЕНИЯ
// ===================================================================

/*
  Сравниваем вершины с допуском eps; порядок вершин не важен.
  Проверяем для каждой вершины текущей фигуры наличие соответствующей
  вершины в другой фигуре (O(16) проверок для 4 точек).
*/
bool Figure::operator==(const Figure& other) const {
    const double eps = 1e-4;
    for (int i = 0; i < 4; i++) {
        bool found = false;
        for (int j = 0; j < 4; j++) {
            if (fabs(points[i].x - other.points[j].x) < eps &&
                fabs(points[i].y - other.points[j].y) < eps) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}