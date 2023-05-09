#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H
#include <iostream>
#include <string>
typedef double real_t;

struct Point
{
    real_t x;
    real_t y;

    Point(real_t x, real_t y) : x(x), y(y) {}
    Point()  {}
};

#define GD_EPSILON  (0.001)

class DebugOutput {
public:
    DebugOutput() {}

    template<typename T>
    DebugOutput& operator<<(const T& value) {
#ifndef NDEBUG
        std::cout << value;
#endif
        return *this;
    }
};

#endif
