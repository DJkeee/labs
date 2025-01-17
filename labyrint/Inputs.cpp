#pragma once

#include "../labyrint/Maze/Maze.cpp"
#include <limits>

class IntervalValidator {
private:
    int min;
    int max;

public:
    IntervalValidator(int min, int max) : min(min), max(max) {
    }

    bool isValid(int number) const {
        return number >= min && number <= max;
    }
};

class CoordinateValidator {
private:
    int maxRow;
    int maxCol;

public:
    CoordinateValidator(int maxRow, int maxCol) : maxRow(maxRow), maxCol(maxCol) {
    }

    bool isValid(const Coordinate& coord) const {
        return coord.row >= 0 && coord.row < maxRow && coord.col >= 0 && coord.col < maxCol;
    }
};

class Input {
public:
    static int inputFromInterval(int min, int max) {
        IntervalValidator validator(min, max);
        int number = 0;

        do {
            std::cout << "Введите число от " << min << " до " << max << ": ";
            std::cin >> number;

            if (std::cin.fail()) {
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
                std::cout << "Некорректный ввод. Введите число из диапазона." << std::endl;
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование остатка строки

            if (!validator.isValid(number)) {
                std::cout << "Число вне диапазона. Попробуйте еще раз." << std::endl;
            }
        } while (!validator.isValid(number));

        return number;
    }

    static Coordinate inputCoordinate(int maxRow, int maxCol) {
        CoordinateValidator validator(maxRow, maxCol);
        Coordinate coordinate(-1, -1);

        do {
            std::cout << "Введите координаты (строка, столбец) разделенные пробелом: ";
            int row, col;

            // Считываем ввод и проверяем, удалось ли считать два числа
            std::cin >> row >> col;

            // Проверка на корректность ввода
            if (std::cin.fail()) {
                std::cin.clear(); // Сброс состояния потока
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорирование некорректного ввода
                std::cout << "Некорректный ввод. Введите два числа, разделенные пробелом." << std::endl;
                continue;
            }

            // Приведение к 0-индексации
            coordinate = Coordinate(row - 1, col - 1);

            // Проверка валидности координат
            if (!validator.isValid(coordinate)) {
                std::cout << "Координаты вне допустимого диапазона. Попробуйте еще раз." << std::endl;
            }

            // Игнорируем остаток строки, чтобы избежать проблем с последующим вводом
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (!validator.isValid(coordinate)); // Продолжаем, пока координаты не будут валидны

        return coordinate;
    }
};
