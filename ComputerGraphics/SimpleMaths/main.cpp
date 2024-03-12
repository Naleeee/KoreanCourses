#include "./Cyclone/core.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

int main() {
    // Exercise 1
    cyclone::Vector3 p(1, 4, -5);
    cyclone::Vector3 v(5, 1, 4);
    std::cout << (p + v).toString() << std::endl;

    // Exercise 2
    cyclone::Vector3 v1(1, 0, 0);
    cyclone::Vector3 v2(0, 1, 0);
    std::cout << (v1 + v2).toString() << std::endl;

    // Exercise 3
    std::cout << (v2 * 5.0f).toString() << std::endl;

    // Exercise 4
    cyclone::Vector3 p1(8, 2, 5);
    cyclone::Vector3 p2(1, -1, 4);
    std::cout << (p2 - p1).toString() << std::endl;

    // Exercise 5
    cyclone::Vector3 v3(1, 3, 4);
    v3.normalise();
    std::cout << p1.toString() << std::endl;
    return 0;
}
