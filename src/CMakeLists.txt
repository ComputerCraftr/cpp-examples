cmake_minimum_required(VERSION 3.10)

project(test_solutions)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "-Wall -O3" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-Wall -O3" CACHE STRING "" FORCE)
#set(CMAKE_C_FLAGS "-Wall -fsanitize=undefined" CACHE STRING "" FORCE)
#set(CMAKE_CXX_FLAGS "-Wall -fsanitize=undefined" CACHE STRING "" FORCE)
message(${CMAKE_C_FLAGS})
message(${CMAKE_CXX_FLAGS})

add_executable(test_solutions test.cpp solutions.cpp solutions.h)

target_include_directories(test_solutions PRIVATE .)
