cmake_minimum_required(VERSION 3.25)

include_directories(engine)
include_directories(shapes)

add_library(engine engine.cpp test_engine.cpp)

target_link_libraries(engine shapes)

