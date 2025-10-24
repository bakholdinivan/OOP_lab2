#include "box_capacity.h"

int box_capacity(int length, int width, int height){
    int a = length * 12 / 16; // переводим из футов в дюймы и делим на сторону ящика в дюймах
    int b = width * 12 / 16;
    int c = height * 12 / 16;
    if (a <= 0 || b <= 0 || c <= 0) return 0; // проверка на некорректный ввод(отрицательные стороны)
    return (a * b * c); // возвращаем вместимость
}