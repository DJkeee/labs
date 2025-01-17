#pragma once

#include "MazeGrid.cpp"
#include <vector>

class Maze {
private:
    int height;
    int width;
    MazeGrid mazeGrid;

public:
    Maze(int height, int width, MazeGrid& mazeGrid) : height(height), width(width), mazeGrid(mazeGrid) {
    }


    int getCellCost(const Coordinate& coordinate) {
        return mazeGrid.getCellCost(coordinate);
    }

    int getHeight() const {
        return height;
    }

    int getWidth() const {
        return width;
    }

    Cell getCell(const Coordinate& coord) {
        return mazeGrid.getCell(coord);
    }

    CellType getType(const Coordinate& coord) {
        return mazeGrid.getCellType(coord);
    }

    void setCellType(const Coordinate& coord, CellType type) {
        mazeGrid.setCell(coord, type);
    }

    std::vector<Coordinate> getNeighbors(const Coordinate& coord) {
        return mazeGrid.getNeighbors(coord);
    }
};
