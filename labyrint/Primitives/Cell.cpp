
#pragma once
#include "../Primitives/Coordinate.cpp"
#include "../Primitives/CellType.cpp"

struct Cell {
    Coordinate coord;
    CellType cellType;

    Cell(Coordinate c, CellType type) : coord(c), cellType(type) {
    }

    Coordinate getCoordinate() { return coord; }

    CellType getCellType() { return cellType; }

    [[nodiscard]] int getCost() const {
        switch (cellType) {
            case CellType::WALL: return 1000;
            case CellType::PASSAGE: return 4;
            case CellType::TRAP: return 10;
            case CellType::COIN: return 1;
            case CellType::TREE: return 6;
            default: return 0;
        }
    }
};