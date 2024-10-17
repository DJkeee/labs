cmake_minimum_required(VERSION 3.27)
project(MEPHI_LAB)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined")

add_executable(MEPHI_LAB
       # TimeComparator/TimeComparator.cpp
        SequenceTests/ListSequenceTest.cpp
        Sequence/SmartList.h
        Sequence/List.h
        Sequence/ListSequence.h
        #  Sequence/SmartDinArray.h
)

target_link_libraries(MEPHI_LAB gtest)

#add_executable(MEPHI_LAB
#        SequenceTests/ArraySequenceTest.cpp
#        SequenceTests/ListSequenceTest.cpp)