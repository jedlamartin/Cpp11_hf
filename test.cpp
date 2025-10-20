#include <print>

#include "mystring.h"

int main() {
    MyString x = "hello";
    MyString y = x;
    y[0] = 'c';
    std::println("{}", x); /* hello */
    std::println("{}", y); /* cello */
}