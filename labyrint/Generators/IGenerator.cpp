#pragma once
#include "../Maze/Maze.cpp"

class IGenerator {
public:
    virtual Maze generate(int height, int width) = 0;
    virtual ~IGenerator() = default;
};

