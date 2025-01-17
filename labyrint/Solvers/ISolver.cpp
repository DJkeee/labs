#pragma once
#include <vector>
#include "../Primitives/Primitives.hpp"
#include "../Maze/Maze.cpp"

class ISolver {
public:
    virtual ~ISolver() = default;

    virtual std::vector<Coordinate> solve(Maze& maze, Coordinate start, Coordinate end) = 0;
};