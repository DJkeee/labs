#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include "../Primitives/Primitives.hpp"

    class MazeGrid {
    private:
        std::vector<std::vector<Cell>> grid;

        void initGridWithWalls() {
            for (int row = 0; row < getRows(); row++) {
                for (int col = 0; col < getCols(); col++) {
                    Coordinate coord(row, col);
                    setCell(coord, CellType::WALL);
                }
            }
        }

    public:
        MazeGrid(int rows, int cols) : grid(rows, std::vector<Cell>(cols, Cell(Coordinate(0, 0), CellType::WALL))) {
            initGridWithWalls();
        }

        int getRows() const {
            return grid.size();
        }

        int getCols() const {
            return grid[0].size();
        }

        void setCell(const Coordinate& coord, CellType cell) {
            if (!isCorrectCoordinate(coord)) {
                return;
            }
            grid[coord.row][coord.col] = Cell(coord, cell);
        }

        int getCellCost(const Coordinate& coordinate) {
            if (!isCorrectCoordinate(coordinate)) {
                throw std::invalid_argument("Некорректные координаты");
            }
            return grid[coordinate.row][coordinate.col].getCost();
        }

        bool isCorrectCoordinate(const Coordinate& coord) const {
            return coord.row >= 0 && coord.row < getRows() &&
                   coord.col >= 0 && coord.col < getCols();
        }

        Cell getCell(const Coordinate& coord) {
            if (!isCorrectCoordinate(coord)) {
                throw std::invalid_argument("Неправильные координаты");
            }
            return grid[coord.row][coord.col];
        }

        CellType getCellType(const Coordinate& coord) {
            if (!isCorrectCoordinate(coord)) {
                throw std::invalid_argument("Неверные координаты");
            }
            return grid[coord.row][coord.col].getCellType();
        }

        std::vector<Coordinate> getNeighbors(const Coordinate& coord) {
            std::vector<Coordinate> neighbors;
            int x = coord.row;
            int y = coord.col;

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (std::abs(dx) + std::abs(dy) == 1) {
                        int newX = x + dx;
                        int newY = y + dy;
                        Coordinate neighbor(newX, newY);

                        if (isCorrectCoordinate(neighbor) && getCellType(neighbor) != CellType::WALL) {
                            neighbors.push_back(neighbor);
                        }
                    }
                }
            }
            return neighbors;
        }
    };