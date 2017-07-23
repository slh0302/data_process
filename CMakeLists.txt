cmake_minimum_required(VERSION 3.8)
project(data_process)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        create.cpp
        test.cpp
        test_8000.cpp
        test_bread.cpp
        test_bread2.cpp
        test_read.cpp
)

add_executable(data_process ${SOURCE_FILES})