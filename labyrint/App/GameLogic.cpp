#pragma once
#include "../Maze/Maze.cpp"
#include "../Generators/RandDGen.cpp"
#include "../App/GameUI.cpp"
#include "../Render.cpp"
#include <bits/unique_ptr.h>
#include <algorithm>
#include "../Solvers/Astar.cpp"
#include "../Generators/IGenerator.cpp"
#include "../Solvers/ISolver.cpp"
#include "../Generators/TunelBasedGenerator.cpp"
#include "../Inputs.cpp"


class GameLogic {
private:
    Maze maze;
    std::unique_ptr<ISolver> solver;
    RealRender renderInterface;

public:
    GameLogic(Maze maze, std::unique_ptr<ISolver> solver)
        : maze(maze), solver(std::move(solver)) {
    }

    static int gridSizeChoose(int choice) {
        switch (choice) {
            case 1: return 15;
            case 3: return 25;
            default: return 20;
        }
    }

    static Maze mazeBuilding(int row, int col, IGenerator* generator) {
        return generator->generate(row, col);
    }

    static IGenerator* mazeGeneratorChoose(int choice) {
        switch (choice) {
            case 2: return new TunelBaseGenerator();
            default: return new RandDecisionGenerator();
        }
    }

    static std::unique_ptr<ISolver> mazeSolverChoose(int choice) {
        switch (choice) {
            case 2:
                return std::make_unique<AStarSolver>();
            case 1:
                return std::make_unique<AStarSolver>();
        }
    }

    void renderMazeWithoutPass() {
        GameUI::sayAboutCoordinatesInterval(maze.getHeight(), maze.getWidth());
        std::string mazeRender = renderInterface.render(maze);
        GameUI::sayAboutMazeSymbols();
        std::cout << mazeRender << std::endl;
    }

    // Метод для отрисовки типа ячейки
    void renderMazeWithPath(const Coordinate& start, const Coordinate& end) {
        std::string mazeRender = renderInterface.render(maze, solver->solve(maze, start, end), start, end);
        GameUI::sayAboutMazeSymbols();
        std::cout << mazeRender << std::endl;
    }

    void renderMazeWithPath() {
        GameUI::askAboutStart();
        GameUI::sayAboutCoordinatesInterval(1, maze.getHeight());
        Coordinate start = Input::inputCoordinate(maze.getWidth(), maze.getHeight());

        GameUI::askAboutEnd();
        GameUI::sayAboutCoordinatesInterval(1, maze.getHeight());
        Coordinate end = Input::inputCoordinate(maze.getWidth(), maze.getHeight());

        renderMazeWithPath(start, end);
    }

    static GameLogic gameLogicCreator() {
        GameUI::sayGameIntro();
        GameUI::askAboutMazeSize();
        int sizeOfLabyrint = gridSizeChoose(Input::inputFromInterval(1, 3));

        GameUI::askAboutGenerationAlgorithm();
        IGenerator* generator = mazeGeneratorChoose(Input::inputFromInterval(1, 2));
        Maze maze = mazeBuilding(sizeOfLabyrint, sizeOfLabyrint, generator);

        GameUI::askAboutSolveAlgorithm();
        auto solver = mazeSolverChoose(Input::inputFromInterval(1, 2));
        return GameLogic(maze, std::move(solver));
    }
};
