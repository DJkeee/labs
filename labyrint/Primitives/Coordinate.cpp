#pragma once

#include <functional>
#include <cstddef>

struct Coordinate {
    int row;
    int col;

    Coordinate(int r, int c) : row(r), col(c) {
    }

    Coordinate() : row(0), col(0) {
    }

    bool operator==(const Coordinate& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }

    struct HashFunction {
        size_t operator()(const Coordinate& c) const {
            return std::hash<int>()(c.row) ^ std::hash<int>()(c.col);
        }
    };
};
