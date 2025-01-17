#pragma once
#include <iostream>
#include <locale>
#include <codecvt>

class GameUI {
public:
    static void askAboutMazeSize() {
        std::cout << "Выберите размер лабиринта:\n";
        std::cout << "1: 15 x 15\n";
        std::cout << "2: 20 x 20\n";
        std::cout << "3: 25 x 25\n\n";
    }

    static void askAboutGenerationAlgorithm() {
        std::cout << "Выберите тип лабиринта, что будет создан:\n";
        std::cout << "1: Классический лабиринт с равномерной заполненностью проходами и стенами\n";
        std::cout << "2: Лабиринт, похожий на пещеры из игр\n\n";
    }

    static void askAboutSolveAlgorithm() {
        std::cout << "Выберите тип поиска:\n";
        std::cout << "1: Поиск маршрута без учета типа клеток (бонусы не влияют на цену маршрута)\n";
        std::cout << "2: Поиск маршрута с учетом типа клетки (бонусы влияют на цену маршрута)\n\n";
    }

    static void askAboutStart() {
        std::cout << "Введите начальную точку поиска пути в лабиринте\n";
    }

    static void askAboutEnd() {
        std::cout << "Введите конечную точку поиска пути в лабиринте\n";
    }

    static void sayAboutCoordinatesInterval(int start, int end) {
        std::cout << "Введите координаты в диапазоне от " << start << " до " << end << "\n";
    }

    static void sayGameIntro() {
        std::cout << "Добро пожаловать в игру, позволяющую вам создавать лабиринты "
                << "и искать в них пути разными способами.\n";
    }

    static void sayAboutMazeSymbols() {
        std::cout << "Условные обозначения:\n";
        std::cout << "Вход и выход из лабиринта - 🚴\n";
        std::cout << "Стены - ⬛️\n";
        std::cout << "Проходы - ⬜️\n\n";
        std::cout << "Замедляющие путь бонусы:\n";
        std::cout << "Ловушки - ⚠️\n";
        std::cout << "Деревья - 🌲\n\n";
        std::cout << "Ускоряющие путь бонусы:\n";
        std::cout << "Монеты - 🪙\n";
    }
};
