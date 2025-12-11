/**
 * @file main.cpp
 * @brief Example program using math_utils.
 */

#include <iostream>
#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

/**
 * @brief Main entry
 */
int main() {
    int x = 3, y = 4;
    std::cout << "x + y = " << add(x,y) << "\n";
    std::cout << "x * y = " << multiply(x,y) << "\n";
    return 0;
}
