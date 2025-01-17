#pragma once
#include <random>
#include <ctime>
#include <set>
#include "../Maze/Maze.cpp"
#include "IGenerator.cpp"
#include "BonusSetter.cpp"

class RandDecisionGenerator : public IGenerator {
public:
    RandDecisionGenerator() {
        engine.seed(std::time(nullptr));
    }

    Maze generate(int row, int col) override {
        BonusSetter setter;
        MazeGrid mazeGrid(row, col);
        std::vector<std::vector<Coordinate>> rows(row);

        for (int x = 0; x < row; ++x) {
            for (int y = 0; y < col; ++y) {
                if (y > 0 && engine() % 2 == 0) { // Используем % 2 для имитации nextBoolean()
                    mazeGrid.setCell(Coordinate(x, y - 1), CellType::PASSAGE);
                    mazeGrid.setCell(Coordinate(x, y), CellType::PASSAGE);
                }
                rows[x].emplace_back(x, y); // Добавляем координаты в вектор
            }

            if (x < row - 1) {
                Coordinate northCell = getRandomCell(rows[x]);
                mazeGrid.setCell(Coordinate(x, northCell.col), CellType::PASSAGE);
                mazeGrid.setCell(Coordinate(x + 1, northCell.row), CellType::PASSAGE);
            }
        }

        setter.setAllBonusFields(mazeGrid);
        return Maze(row, col, mazeGrid);
    }

private:
    std::mt19937 engine; // Генератор случайных чисел

    Coordinate getRandomCell(const std::vector<Coordinate>& cells) {
        int index = engine() % cells.size(); // Получаем случайный индекс
        return cells[index]; // Возвращаем элемент по индексу
    }
};
