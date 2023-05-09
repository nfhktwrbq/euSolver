cmake_minimum_required(VERSION 3.25)

project(eusolver)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(shapes)
include_directories(shapes)

add_subdirectory(engine)
include_directories(engine)

add_executable(eusolver main.cpp)

target_link_libraries(eusolver shapes engine)

set_property(TARGET eusolver PROPERTY CXX_STANDARD 26)


install(TARGETS eusolver RUNTIME DESTINATION bin)
