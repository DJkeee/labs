cmake_minimum_required(VERSION 3.27)
project(MEPHI_LAB)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined")

if (MSVC)
    # Для MSVC используйте флаг для установки кода страницы
    add_compile_options(/utf-8)
else ()
    # Для GCC или Clang
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif ()

find_package(wxWidgets REQUIRED COMPONENTS core base net)

add_executable(MEPHI_LAB
        main.cpp
        labyrint/Maze/MazeGrid.cpp
        labyrint/Primitives/Coordinate.cpp
        labyrint/Primitives/Cell.cpp
        labyrint/Primitives/CellType.cpp
        labyrint/Primitives/Primitives.hpp
        labyrint/Maze/Maze.cpp
        labyrint/Generators/IGenerator.cpp
        labyrint/Generators/TunelBasedGenerator.cpp
        labyrint/Generators/BonusSetter.cpp
        labyrint/Solvers/ISolver.cpp
        labyrint/Solvers/Astar.cpp
        labyrint/Render.cpp
        labyrint/Generators/RandDGen.cpp
        labyrint/Solvers/WaveSolver.cpp
        labyrint/Inputs.cpp
        labyrint/App/GameUI.cpp
        labyrint/App/GameLogic.cpp
        labyrint/App/Game.cpp
)

target_link_libraries(MEPHI_LAB PRIVATE gtest ${wxWidgets_LIBRARIES})

include_directories(${wxWidgets_INCLUDE_DIRS})