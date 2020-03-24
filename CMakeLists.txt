cmake_minimum_required(VERSION 3.14)
project(matlog)

set(CMAKE_CXX_STANDARD 17)

add_library(grammar STATIC
        grammar/lib.h

        grammar/grammar.h
        grammar/grammar.cpp

        grammar/proof.h
        grammar/proof.cpp

        grammar/expression.h
        grammar/expression.cpp)

add_executable(tests test.cpp
        parser/parser.h
        parser/parser.cpp)

add_executable(task1 task1_parse.cpp
        parser/parser.h
        parser/parser.cpp
        parser/parser_error.h)

add_executable(task2 task2_minimize.cpp
        parser/parser.h
        parser/parser.cpp
        proof/proof_parser.h
        proof/proof_parser.cpp
        parser/parser_error.h)

target_link_libraries(tests grammar)

target_link_libraries(task1 grammar)

target_link_libraries(task2 grammar)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb -std=c++11 -pedantic -O2 -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG  -fsanitize=address,undefined,leak")
endif ()
