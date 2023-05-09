cmake_minimum_required(VERSION 3.25)

include_directories(engine)
include_directories(shapes)

add_library(shapes shape.cpp dot.cpp line.cpp circle.cpp intersection.cpp test.cpp)
