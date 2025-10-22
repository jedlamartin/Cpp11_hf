#include <iostream>

#include "mystring.h"

int main() {
    MyString x = "hello";
    MyString y = x;
    y[0] = 'c';
    std::cout << x << std::endl; /* hello */
    std::cout << y << std::endl; /* cello */
}