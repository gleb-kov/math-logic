cmake_minimum_required(VERSION 3.14)
project(recursive)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_SRC
        ${PROJECT_SOURCE_DIR}/gtest/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/gtest/gtest.h
        ${PROJECT_SOURCE_DIR}/gtest/gtest_main.cc)

# TODO: fix with include_dir

add_executable(sample1 lib/typelist.h lib/recursive.h samples/task1.cpp)

add_executable(sample2 lib/godel.h samples/task3.cpp)

add_executable(sample3 lib/ackermann.h samples/task3.cpp)

add_executable(test1 lib/typelist.h lib/recursive.h ${GTEST_SRC} tests/test1.cpp)

add_executable(test2 lib/typelist.h lib/godel.h lib/recursive.h ${GTEST_SRC} tests/test2.cpp)

add_executable(test3 lib/ackermann.h ${GTEST_SRC} tests/test3.cpp)

add_executable(tuple extra/ct_tuple.h extra/tuple.cpp)

if (UNIX AND NOT APPLE)
    target_link_libraries(test1 pthread)
    target_link_libraries(test2 pthread)
    target_link_libraries(test3 pthread)
endif (UNIX AND NOT APPLE)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG") # TODO: add sanitizers
endif ()

