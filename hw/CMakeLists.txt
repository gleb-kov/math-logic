cmake_minimum_required(VERSION 3.14)
project(recursive)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_SRC
        ${PROJECT_SOURCE_DIR}/gtest/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/gtest/gtest.h
        ${PROJECT_SOURCE_DIR}/gtest/gtest_main.cc)

add_executable(task1 typelist.h recursive.h task1.cpp)

add_executable(task2 godel.h task2.cpp)

add_executable(ackermann ackermann.h ackermann.cpp)

add_executable(test1 typelist.h recursive.h ${GTEST_SRC} test1.cpp)

add_executable(test2 typelist.h godel.h recursive.h ${GTEST_SRC} test2.cpp)

add_executable(test3 ackermann.h ${GTEST_SRC} test3.cpp)

add_executable(tuple ct_tuple.h tuple.cpp)

if (UNIX AND NOT APPLE)
    target_link_libraries(test1 pthread)
    target_link_libraries(test2 pthread)
    target_link_libraries(test3 pthread)
endif (UNIX AND NOT APPLE)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
endif ()
