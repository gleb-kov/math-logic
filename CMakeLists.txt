cmake_minimum_required(VERSION 3.14)
project(matlog)

set(CMAKE_CXX_STANDARD 17)

add_library(grammar STATIC
        grammar/lib.h

        grammar/grammar.h

        grammar/expression.h
        grammar/expression.cpp)

add_library(proof STATIC
        proof/lib.h

        proof/proof.h
        proof/proof.cpp

        proof/structures.h
        proof/structures.cpp)

add_library(parser STATIC
        parser/lib.h

        parser/errors.h

        parser/parser.h
        parser/parser.cpp

        parser/proof_parser.h
        parser/proof_parser.cpp)

target_link_libraries(parser grammar proof)

add_executable(tests test.cpp)

add_executable(task1 task1_parse.cpp)

add_executable(task2 task2_minimize.cpp)

add_executable(task3 task3_arithmetic.cpp)

add_executable(task4 task4_prove.cpp)

target_link_libraries(tests grammar parser)

target_link_libraries(task1 grammar parser)

target_link_libraries(task2 grammar parser)

target_link_libraries(task3 grammar parser)

target_link_libraries(task4 grammar parser)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb -std=c++17 -pedantic -O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG") #-fsanitize=address,undefined,leak
endif ()
