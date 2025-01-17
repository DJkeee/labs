#pragma once

#include <random>
#include "../Maze/MazeGrid.cpp"

class BonusSetter {
public:
    BonusSetter()
        : random_engine(std::random_device{}()),
          trapProbability(0.10),
          coinProbability(0.12),
          treeProbability(0.15) {
    }

    void setAllBonusFields(MazeGrid& mazeGrid) {
        for (int x = 0; x < mazeGrid.getRows(); ++x) {
            for (int y = 0; y < mazeGrid.getCols(); ++y) {
                Coordinate coord(x, y);
                if (mazeGrid.getCellType(coord) != CellType::WALL) {
                    CellType bonusField = generateBonusField();
                    mazeGrid.setCell(coord, bonusField);
                }
            }
        }
    }

private:
    std::mt19937 random_engine;
    const double trapProbability;
    const double coinProbability;
    const double treeProbability; // Make this const if it should not change

    CellType generateBonusField() {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double randomValue = distribution(random_engine);

        if (randomValue < trapProbability) {
            return CellType::TRAP;
        } else if (randomValue < trapProbability + coinProbability) {
            return CellType::COIN;
        } else if (randomValue < trapProbability + coinProbability + treeProbability) {
            return CellType::TREE;
        } else {
            return CellType::PASSAGE;
        }
    }
};