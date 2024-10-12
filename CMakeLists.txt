cmake_minimum_required(VERSION 3.27)
project(MEPHI_LAB)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Enable Address and Undefined Behavior Sanitizers
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")

# Add the executable
add_executable(MEPHI_LAB main.cpp)
target_link_libraries(MEPHI_LAB gtest)