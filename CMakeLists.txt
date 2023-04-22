cmake_minimum_required(VERSION 3.0)

project(eusolver)

add_executable(eusolver main.cpp)

install(TARGETS eusolver RUNTIME DESTINATION bin)
