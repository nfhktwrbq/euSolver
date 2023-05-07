#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H
#include <iostream>
#include <string>
typedef float real_t;

struct Point
{
    real_t x;
    real_t y;

    Point(real_t x = 0.0, real_t y = 0.0) : x(x), y(y) {}
};

#define GD_EPSILON  (0.000001)

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
