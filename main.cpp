#include <iostream>
#include "dot.h"
#include "test.h"
#include "test_engine.h"

int main(int argc, char **argv) {
    DebugOutput() << "Debug enabled\n";

    TestEngine test;
    cout << test.run();

//    cout << "sdfsd\n";
//    cout << "sdfsd2\n";
//    cout << "sdfsd3\n";
    return 0;
}
