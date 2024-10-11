cmake_minimum_required(VERSION 3.27)
project(MEPHI_LAB)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")
set(SANITIZERS "-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZERS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZERS}")

set(CMAKE_CXX_STANDARD 20)

add_executable(MEPHI_LAB main.cpp)