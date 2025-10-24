#include <gtest/gtest.h>
#include "Square.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Array.h"
#include <cmath>
#include <sstream>

/**
 * @file test_geometry.cpp
 * 
 * СТРУКТУРА ТЕСТОВ:
 * - Тесты 1-15: Базовая функциональность (конструкторы, площадь, центр)
 * - Тесты 16-25: Правило пяти (копирование, перемещение)
 * - Тесты 26-35: Перегрузка операторов (<<, >>, ==, double)
 * - Тесты 36-45: Массив и полиморфизм
 */

// ===================================================================
// ГРУППА 1: БАЗОВАЯ ФУНКЦИОНАЛЬНОСТЬ SQUARE (Тесты 1-5)
// ===================================================================

/**
 * ТЕСТ 1: Конструктор по умолчанию квадрата
 * Проверяем, что создается единичный квадрат с площадью 1
 */
TEST(SquareTest, DefaultConstructor) {
    Square sq;
    EXPECT_DOUBLE_EQ(sq.area(), 1.0);
}

/**
 * ТЕСТ 2: Площадь квадрата с заданными вершинами
 * Квадрат 2x2 должен иметь площадь 4
 */
TEST(SquareTest, AreaCalculation) {
    Point p[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Square sq(p);
    EXPECT_DOUBLE_EQ(sq.area(), 4.0);
}

/**
 * ТЕСТ 3: Центр квадрата
 * Проверяем правильность вычисления геометрического центра
 */
TEST(SquareTest, CenterCalculation) {
    Point p[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Square sq(p);
    Point center = sq.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

/**
 * ТЕСТ 4: Оператор приведения к double
 * Проверяем, что (double)square возвращает площадь
 */
TEST(SquareTest, DoubleOperator) {
    Point p[4] = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Square sq(p);
    double area = (double)sq;
    EXPECT_DOUBLE_EQ(area, 9.0);
}

/**
 * ТЕСТ 5: Квадрат с нестандартным расположением
 * Проверяем, что точки в любом порядке обрабатываются корректно
 */
TEST(SquareTest, RandomOrderPoints) {
    // Точки в произвольном порядке
    Point p[4] = {Point(1, 1), Point(0, 0), Point(0, 1), Point(1, 0)};
    Square sq(p);
    EXPECT_DOUBLE_EQ(sq.area(), 1.0);
}

// ===================================================================
// ГРУППА 2: БАЗОВАЯ ФУНКЦИОНАЛЬНОСТЬ RECTANGLE (Тесты 6-10)
// ===================================================================

/**
 * ТЕСТ 6: Конструктор по умолчанию прямоугольника
 * Прямоугольник 2x1 должен иметь площадь 2
 */
TEST(RectangleTest, DefaultConstructor) {
    Rectangle rect;
    EXPECT_DOUBLE_EQ(rect.area(), 2.0);
}

/**
 * ТЕСТ 7: Площадь прямоугольника
 * Прямоугольник 4x3 должен иметь площадь 12
 */
TEST(RectangleTest, AreaCalculation) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)};
    Rectangle rect(p);
    EXPECT_DOUBLE_EQ(rect.area(), 12.0);
}

/**
 * ТЕСТ 8: Центр прямоугольника
 */
TEST(RectangleTest, CenterCalculation) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(4, 2), Point(0, 2)};
    Rectangle rect(p);
    Point center = rect.center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

/**
 * ТЕСТ 9: Прямоугольник со смещением
 * Проверяем работу с прямоугольником не в начале координат
 */
TEST(RectangleTest, OffsetRectangle) {
    Point p[4] = {Point(1, 1), Point(3, 1), Point(3, 4), Point(1, 4)};
    Rectangle rect(p);
    EXPECT_DOUBLE_EQ(rect.area(), 6.0);  // 2x3 = 6
}

/**
 * ТЕСТ 10: Тип прямоугольника
 */
TEST(RectangleTest, GetType) {
    Rectangle rect;
    EXPECT_STREQ(rect.getType(), "Rectangle");
}

// ===================================================================
// ГРУППА 3: БАЗОВАЯ ФУНКЦИОНАЛЬНОСТЬ TRAPEZOID (Тесты 11-15)
// ===================================================================

/**
 * ТЕСТ 11: Конструктор по умолчанию трапеции
 */
TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid trap;
    EXPECT_GT(trap.area(), 0.0);
}

/**
 * ТЕСТ 12: Площадь трапеции
 * Трапеция с основаниями 4 и 2, высотой 2
 * Площадь = (4+2)*2/2 = 6
 */
TEST(TrapezoidTest, AreaCalculation) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    Trapezoid trap(p);
    EXPECT_NEAR(trap.area(), 6.0, 0.01);
}

/**
 * ТЕСТ 13: Центр трапеции
 */
TEST(TrapezoidTest, CenterCalculation) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    Trapezoid trap(p);
    Point center = trap.center();
    EXPECT_GT(center.x, 0.0);
    EXPECT_LT(center.x, 4.0);
    EXPECT_GT(center.y, 0.0);
    EXPECT_LT(center.y, 2.0);
}

/**
 * ТЕСТ 14: Тип трапеции
 */
TEST(TrapezoidTest, GetType) {
    Trapezoid trap;
    EXPECT_STREQ(trap.getType(), "Trapezoid");
}

/**
 * ТЕСТ 15: Равнобедренная трапеция
 */
TEST(TrapezoidTest, IsoscelesTrapezoid) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    Trapezoid trap(p);
    EXPECT_NEAR(trap.area(), 6.0, 0.01);
}

// ===================================================================
// ГРУППА 4: ПРАВИЛО ПЯТИ - КОПИРОВАНИЕ (Тесты 16-20)
// ===================================================================

/**
 * ТЕСТ 16: Конструктор копирования Square
 */
TEST(RuleOfFiveTest, SquareCopyConstructor) {
    Point p[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Square sq1(p);
    Square sq2(sq1);
    EXPECT_DOUBLE_EQ(sq1.area(), sq2.area());
    EXPECT_DOUBLE_EQ(sq2.area(), 4.0);
}

/**
 * ТЕСТ 17: Оператор присваивания копированием Square
 */
TEST(RuleOfFiveTest, SquareCopyAssignment) {
    Point p1[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Point p2[4] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Square sq1(p1);
    Square sq2(p2);
    EXPECT_DOUBLE_EQ(sq1.area(), 4.0);
    EXPECT_DOUBLE_EQ(sq2.area(), 1.0);
    sq2 = sq1;
    EXPECT_DOUBLE_EQ(sq2.area(), 4.0);
}

/**
 * ТЕСТ 18: Конструктор копирования Rectangle
 */
TEST(RuleOfFiveTest, RectangleCopyConstructor) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(4, 2), Point(0, 2)};
    Rectangle rect1(p);
    Rectangle rect2(rect1);
    EXPECT_DOUBLE_EQ(rect1.area(), rect2.area());
    EXPECT_DOUBLE_EQ(rect2.area(), 8.0);
}

/**
 * ТЕСТ 19: Оператор присваивания копированием Rectangle
 */
TEST(RuleOfFiveTest, RectangleCopyAssignment) {
    Point p1[4] = {Point(0, 0), Point(4, 0), Point(4, 2), Point(0, 2)};
    Rectangle rect1(p1);
    Rectangle rect2;
    rect2 = rect1;
    EXPECT_DOUBLE_EQ(rect2.area(), 8.0);
}

/**
 * ТЕСТ 20: Конструктор копирования Trapezoid
 */
TEST(RuleOfFiveTest, TrapezoidCopyConstructor) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    Trapezoid trap1(p);
    Trapezoid trap2(trap1);
    EXPECT_DOUBLE_EQ(trap1.area(), trap2.area());
}

// ===================================================================
// ГРУППА 5: ПРАВИЛО ПЯТИ - ПЕРЕМЕЩЕНИЕ (Тесты 21-25)
// ===================================================================

/**
 * ТЕСТ 21: Конструктор перемещения Square
 */
TEST(RuleOfFiveTest, SquareMoveConstructor) {
    Point p[4] = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Square sq1(p);
    Square sq2(std::move(sq1));
    EXPECT_DOUBLE_EQ(sq2.area(), 9.0);
}

/**
 * ТЕСТ 22: Оператор присваивания перемещением Square
 */
TEST(RuleOfFiveTest, SquareMoveAssignment) {
    Point p1[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Point p2[4] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Square sq1(p1);
    Square sq2(p2);
    sq2 = std::move(sq1);
    EXPECT_DOUBLE_EQ(sq2.area(), 4.0);
}

/**
 * ТЕСТ 23: Конструктор перемещения Rectangle
 */
TEST(RuleOfFiveTest, RectangleMoveConstructor) {
    Point p[4] = {Point(0, 0), Point(5, 0), Point(5, 3), Point(0, 3)};
    Rectangle rect1(p);
    Rectangle rect2(std::move(rect1));
    EXPECT_DOUBLE_EQ(rect2.area(), 15.0);
}

/**
 * ТЕСТ 24: Конструктор перемещения Trapezoid
 */
TEST(RuleOfFiveTest, TrapezoidMoveConstructor) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    Trapezoid trap1(p);
    double area1 = trap1.area();
    Trapezoid trap2(std::move(trap1));
    EXPECT_DOUBLE_EQ(trap2.area(), area1);
}

/**
 * ТЕСТ 25: Оператор присваивания перемещением Trapezoid
 */
TEST(RuleOfFiveTest, TrapezoidMoveAssignment) {
    Point p[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    Trapezoid trap1(p);
    Trapezoid trap2;
    double area1 = trap1.area();
    trap2 = std::move(trap1);
    EXPECT_DOUBLE_EQ(trap2.area(), area1);
}

// ===================================================================
// ГРУППА 6: ОПЕРАТОРЫ (Тесты 26-30)
// ===================================================================

/**
 * ТЕСТ 26: Самоприсваивание Square
 * Защита от sq = sq
 */
TEST(OperatorTest, SelfAssignment) {
    Point p[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Square sq(p);
    double areaBefore = sq.area();
    sq = sq;
    EXPECT_DOUBLE_EQ(sq.area(), areaBefore);
}

/**
 * ТЕСТ 27: Цепочка присваиваний (a = b = c)
 */
TEST(OperatorTest, ChainAssignment) {
    Point p1[4] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Point p2[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Point p3[4] = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Square sq1(p1), sq2(p2), sq3(p3);
    sq1 = sq2 = sq3;
    EXPECT_DOUBLE_EQ(sq1.area(), 9.0);
    EXPECT_DOUBLE_EQ(sq2.area(), 9.0);
    EXPECT_DOUBLE_EQ(sq3.area(), 9.0);
}

/**
 * ТЕСТ 28: Оператор == для равных фигур
 */
TEST(OperatorTest, EqualityOperatorTrue) {
    Point p[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Square sq1(p);
    Square sq2(p);
    EXPECT_TRUE(sq1 == sq2);
}

/**
 * ТЕСТ 29: Оператор == для неравных фигур
 */
TEST(OperatorTest, EqualityOperatorFalse) {
    Point p1[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Point p2[4] = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Square sq1(p1);
    Square sq2(p2);
    EXPECT_FALSE(sq1 == sq2);
}

/**
 * ТЕСТ 30: Оператор << (вывод в поток)
 */
TEST(OperatorTest, OutputOperator) {
    Point p[4] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Square sq(p);
    std::ostringstream oss;
    oss << sq;
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Square") != std::string::npos);
    EXPECT_TRUE(output.find("0") != std::string::npos);
    EXPECT_TRUE(output.find("1") != std::string::npos);
}

// ===================================================================
// ГРУППА 7: МАССИВ - БАЗОВАЯ ФУНКЦИОНАЛЬНОСТЬ (Тесты 31-35)
// ===================================================================

/**
 * ТЕСТ 31: Создание пустого массива
 */
TEST(ArrayTest, EmptyArray) {
    Array arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_DOUBLE_EQ(arr.totalArea(), 0.0);
}

/**
 * ТЕСТ 32: Добавление фигур в массив
 */
TEST(ArrayTest, PushFigures) {
    Array arr;
    arr.push(new Square());
    arr.push(new Rectangle());
    arr.push(new Trapezoid());
    EXPECT_EQ(arr.size(), 3);
}

/**
 * ТЕСТ 33: Общая площадь фигур в массиве
 */
TEST(ArrayTest, TotalArea) {
    Array arr;
    arr.push(new Square());      // Площадь = 1
    arr.push(new Square());      // Площадь = 1
    arr.push(new Square());      // Площадь = 1
    EXPECT_DOUBLE_EQ(arr.totalArea(), 3.0);
}

/**
 * ТЕСТ 34: Удаление фигуры из массива
 */
TEST(ArrayTest, RemoveFigure) {
    Array arr;
    arr.push(new Square());
    arr.push(new Rectangle());
    arr.push(new Trapezoid());
    EXPECT_EQ(arr.size(), 3);
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
}

/**
 * ТЕСТ 35: Получение фигуры по индексу
 */
TEST(ArrayTest, GetFigure) {
    Array arr;
    arr.push(new Square());
    Figure* fig = arr.get(0);
    EXPECT_NE(fig, nullptr);
    EXPECT_STREQ(fig->getType(), "Square");
}

// ===================================================================
// ГРУППА 8: МАССИВ - ГРАНИЧНЫЕ СЛУЧАИ (Тесты 36-40)
// ===================================================================

/**
 * ТЕСТ 36: Удаление из пустого массива
 */
TEST(ArrayTest, RemoveFromEmpty) {
    Array arr;
    arr.remove(0);  // Не должно упасть
    EXPECT_EQ(arr.size(), 0);
}

/**
 * ТЕСТ 37: Получение по неверному индексу
 */
TEST(ArrayTest, GetInvalidIndex) {
    Array arr;
    arr.push(new Square());
    EXPECT_EQ(arr.get(-1), nullptr);
    EXPECT_EQ(arr.get(10), nullptr);
}

/**
 * ТЕСТ 38: Удаление по неверному индексу
 */
TEST(ArrayTest, RemoveInvalidIndex) {
    Array arr;
    arr.push(new Square());
    int sizeBefore = arr.size();
    arr.remove(-1);
    arr.remove(10);
    EXPECT_EQ(arr.size(), sizeBefore);
}

/**
 * ТЕСТ 39: Добавление nullptr
 */
TEST(ArrayTest, PushNullptr) {
    Array arr;
    arr.push(nullptr);
    EXPECT_EQ(arr.size(), 0);
}

/**
 * ТЕСТ 40: Автоматическое расширение массива
 * Проверяем, что массив корректно расширяется при добавлении >4 элементов
 */
TEST(ArrayTest, AutoResize) {
    Array arr;
    for (int i = 0; i < 10; i++) {
        arr.push(new Square());
    }
    EXPECT_EQ(arr.size(), 10);
}

// ===================================================================
// ГРУППА 9: ПОЛИМОРФИЗМ (Тесты 41-45)
// ===================================================================

/**
 * ТЕСТ 41: Полиморфизм - вызов виртуальных методов
 */
TEST(PolymorphismTest, VirtualMethods) {
    Figure* figures[3];
    figures[0] = new Square();
    figures[1] = new Rectangle();
    figures[2] = new Trapezoid();
    
    EXPECT_STREQ(figures[0]->getType(), "Square");
    EXPECT_STREQ(figures[1]->getType(), "Rectangle");
    EXPECT_STREQ(figures[2]->getType(), "Trapezoid");
    
    EXPECT_DOUBLE_EQ(figures[0]->area(), 1.0);
    EXPECT_DOUBLE_EQ(figures[1]->area(), 2.0);
    EXPECT_GT(figures[2]->area(), 0.0);
    
    for (int i = 0; i < 3; i++) {
        delete figures[i];
    }
}

/**
 * ТЕСТ 42: Полиморфизм - оператор приведения к double
 */
TEST(PolymorphismTest, DoubleOperatorPolymorphic) {
    Figure* fig = new Square();
    double area = (double)(*fig);
    EXPECT_DOUBLE_EQ(area, 1.0);
    delete fig;
}

/**
 * ТЕСТ 43: Полиморфизм - центр через базовый указатель
 */
TEST(PolymorphismTest, CenterPolymorphic) {
    Figure* fig = new Square();
    Point c = fig->center();
    EXPECT_DOUBLE_EQ(c.x, 0.5);
    EXPECT_DOUBLE_EQ(c.y, 0.5);
    delete fig;
}

/**
 * ТЕСТ 44: Полиморфизм - массив разных типов
 */
TEST(PolymorphismTest, MixedTypesArray) {
    Array arr;
    Point p1[4] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Point p2[4] = {Point(0, 0), Point(2, 0), Point(2, 1), Point(0, 1)};
    Point p3[4] = {Point(0, 0), Point(4, 0), Point(3, 2), Point(1, 2)};
    
    arr.push(new Square(p1));
    arr.push(new Rectangle(p2));
    arr.push(new Trapezoid(p3));
    
    EXPECT_NEAR(arr.totalArea(), 1.0 + 2.0 + 6.0, 0.1);
}

/**
 * ТЕСТ 45: Полиморфизм - удаление через базовый указатель
 * Проверяем, что виртуальный деструктор работает корректно
 */
TEST(PolymorphismTest, VirtualDestructor) {
    Figure* fig = new Square();
    delete fig;  // Должен вызваться ~Square(), а не только ~Figure()
    // Если бы деструктор не был виртуальным - была бы утечка памяти
    SUCCEED();  // Тест пройден, если программа не упала
}

/**
 * ИТОГО: 45 ТЕСТОВ
 * - 15 базовых тестов (конструкторы, площадь, центр)
 * - 10 тестов правила пяти (копирование, перемещение)
 * - 5 тестов операторов (<<, ==, double, самоприсваивание)
 * - 10 тестов массива (добавление, удаление, граничные случаи)
 * - 5 тестов полиморфизма
 */