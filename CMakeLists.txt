cmake_minimum_required(VERSION 3.14)
project(matlog)

set(CMAKE_CXX_STANDARD 17)

add_library(grammar STATIC utils/grammar.h utils/grammar.cpp)

add_executable(task1 task1_parse.cpp parser/parser.h parser/parser.cpp)

add_executable(task2 task2_minimize.cpp proof/proof_parser.h proof/proof_parser.cpp)

target_link_libraries(task1 grammar)