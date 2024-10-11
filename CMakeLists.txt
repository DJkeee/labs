cmake_minimum_required(VERSION 3.27)
project(MEPHI_LAB)

set(CMAKE_CXX_STANDARD 20)
add_executable(MEPHI_LAB main.cpp
        Pointers/ShrdPtr.h
        Pointers/UnqPtr.h
        Sequence/List.h
        Sequence/ListSequence.h
        Sequence/ArraySequence.h
)
