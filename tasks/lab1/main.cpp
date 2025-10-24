#include <iostream>
#include "include/box_capacity.h"

int main(){
    int length,width,height;
    std:: cout << "Введите длину, ширину и высоту склада:";
    std:: cin >> length >> width >> height;
    //std:: cout << length << width << height << '\n';
    std:: cout << box_capacity(length,width,height) << std:: endl;
    return 0;
}