#pragma once

#include <string>
#include <vector>
#include "../labyrint/Maze/Maze.cpp"
#include "Primitives/Primitives.hpp"
#include <algorithm>

class RealRender {
public:
    std::string render(Maze& maze) {
        return renderMaze(maze, {}, Coordinate(-1, -1), Coordinate(-1, -1));
    }

    std::string render(Maze& maze, const std::vector<Coordinate>& path, const Coordinate start,
                       const Coordinate end) {
        return renderMaze(maze, path, start, end);
    }

private:
    std::string renderMaze(Maze& maze, const std::vector<Coordinate>& path, const Coordinate start,
                           const Coordinate end) {
        std::string result;
        for (int row = 0; row < maze.getHeight(); row++) {
            for (int col = 0; col < maze.getWidth(); col++) {
                Coordinate currentCoord(row, col);
                result += renderCell(maze.getCell(currentCoord), currentCoord, path, start, end);
            }
            result += '\n';
        }
        return result;
    }

    std::string renderCell(const Cell& cell, const Coordinate& currentCoord, const std::vector<Coordinate>& path,
                           const Coordinate start, const Coordinate end) {
        if (start == currentCoord) {
            return "🚴";
        } else if (end == currentCoord) {
            return "🏁";
        } else if (!path.empty() && std::find(path.begin(), path.end(), currentCoord) != path.end()) {
            return "🟫"; // Путь
        } else {
            return renderCellType(cell);
        }
    }

    std::string renderCellType(const Cell& cell) {
        switch (cell.cellType) {
            case CellType::WALL:
                return "⬛️"; // Стена
            case CellType::COIN:
                return "🟨"; // Монета
            case CellType::TRAP:
                return "⚠️"; // Ловушка
            case CellType::TREE:
                return "🌲"; // Дерево
            default:
                return "⬜️"; // Пустая ячейка
        }
    }
};
