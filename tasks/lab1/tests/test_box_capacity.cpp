#include "box_capacity.h"
#include <gtest/gtest.h>

// Тест из задания
TEST(test_01, Task_test) {
    ASSERT_EQ(box_capacity(32, 64, 16), 13824);
}

// Минимальные размеры
TEST(test_02, minimal_dimensions) {
    ASSERT_EQ(box_capacity(1, 1, 1), 0);      // 12/16 = 0.75 → 0
    ASSERT_EQ(box_capacity(2, 2, 2), 1);      // 24/16 = 1.5 → 1
}

// Нулевые размеры
TEST(test_03, zero_dimensions) {
    ASSERT_EQ(box_capacity(0, 10, 10), 0);
    ASSERT_EQ(box_capacity(10, 0, 10), 0);
    ASSERT_EQ(box_capacity(10, 10, 0), 0);
    ASSERT_EQ(box_capacity(0, 0, 0), 0);
}

// Отрицательные размеры
TEST(test_04, negative_dimensions) {
    ASSERT_EQ(box_capacity(-1, 10, 10), 0);
    ASSERT_EQ(box_capacity(10, -1, 10), 0);
    ASSERT_EQ(box_capacity(10, 10, -1), 0);
    ASSERT_EQ(box_capacity(-5, -5, -5), 0);
}

// Точные кратные размеры
TEST(test_05, exact_multiples) {
    // 4 фута = 48 дюймов = 3 ящика (48/16 = 3)
    ASSERT_EQ(box_capacity(4, 4, 4), 27);      // 3×3×3 = 27
    
    // 8 футов = 96 дюймов = 6 ящиков (96/16 = 6)  
    ASSERT_EQ(box_capacity(8, 8, 8), 216);     // 6×6×6 = 216
    
    // 16 футов = 192 дюймов = 12 ящиков (192/16 = 12)
    ASSERT_EQ(box_capacity(16, 16, 16), 1728); // 12×12×12 = 1728
}

// Дробные количества ящиков (округление в меньшую сторону)
TEST(test_06, fractional_boxes) {
    // 1 фут = 12 дюймов = 0.75 ящика → 0
    ASSERT_EQ(box_capacity(1, 1, 1), 0);
    
    // 3 фута = 36 дюймов = 2.25 ящика → 2
    ASSERT_EQ(box_capacity(3, 3, 3), 8);       // 2×2×2 = 8
    
    // 5 футов = 60 дюймов = 3.75 ящика → 3
    ASSERT_EQ(box_capacity(5, 5, 5), 27);      // 3×3×3 = 27
}

// Разные размеры по осям
TEST(test_07, different_dimensions) {
    int expected = (10*12/16) * (20*12/16) * (30*12/16);
    ASSERT_EQ(box_capacity(10, 20, 30), expected);
    ASSERT_EQ(expected, 2310); 
}

// Большие размеры
TEST(test_08, large_warehouse) {
    int expected = (100*12/16) * (100*12/16) * (50*12/16);
    ASSERT_EQ(box_capacity(100, 100, 50), expected);
    ASSERT_EQ(expected, 208125); 
}


// Граничные случаи с округлением
TEST(test_09, edge_rounding) {
    // 1.333 фута = 16 дюймов = 1 ящик
    ASSERT_EQ(box_capacity(1, 1, 2), 0);      // 0×0×1 = 0
    ASSERT_EQ(box_capacity(2, 2, 2), 1);      // 1×1×1 = 1
    ASSERT_EQ(box_capacity(3, 3, 3), 8);      // 2×2×2 = 8
}

// Проверка математики
TEST(test_10, math_verification) {
    // Ручной расчет для проверки
    int expected = (32*12/16) * (64*12/16) * (16*12/16);
    ASSERT_EQ(box_capacity(32, 64, 16), expected);
    ASSERT_EQ(expected, 13824); // Двойная проверка
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}