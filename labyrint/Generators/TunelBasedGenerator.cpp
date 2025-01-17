#pragma once

#include <random>
#include <ctime>
#include "../Maze/Maze.cpp"
#include "../Generators/IGenerator.cpp"
#include "../Generators/BonusSetter.cpp"


class TunelBaseGenerator : public IGenerator {
private:
    static constexpr double CHANCE_OF_PASS = 0.5;
    static constexpr int DIR_MAX_VALUE = 3;
    static constexpr int OFFSET = 2;

public:
    Maze generate(int row, int col) override {
        MazeGrid mazeGrid(row, col);
        std::mt19937 engine;
        engine.seed(std::time(nullptr));

        std::uniform_int_distribution<> col_dist(OFFSET, mazeGrid.getCols() - 2 * OFFSET - 1);
        // -1 для корректного диапазона
        std::uniform_int_distribution<> dir_dist(0, DIR_MAX_VALUE - 1);
        std::uniform_real_distribution<> double_dist(0.0, 1.0);


        for (int x = OFFSET; x < mazeGrid.getRows() - OFFSET; x++) {
            int endX = col_dist(engine);
            while (endX < mazeGrid.getCols() - OFFSET) {
                Coordinate coord(x, endX);
                mazeGrid.setCell(coord, CellType::PASSAGE);
                if (double_dist(engine) < CHANCE_OF_PASS) {
                    int dir = dir_dist(engine);
                    if ((dir == 0) && (x > OFFSET)) {
                        Coordinate upCoord(x - 1, endX);
                        mazeGrid.setCell(upCoord, CellType::PASSAGE);
                    }
                }
                endX++;
            }
        }
        BonusSetter setter;
        setter.setAllBonusFields(mazeGrid);
        return Maze(row, col, mazeGrid);
    }
};

