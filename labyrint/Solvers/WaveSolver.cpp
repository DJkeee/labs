#pragma once

#include "../Maze/Maze.cpp"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include "ISolver.cpp"

class WaveSolver : ISolver {
public:
    std::vector<Coordinate> solve(Maze& maze, Coordinate start, Coordinate end) override {
        std::queue<Coordinate> queue;
        std::unordered_map<Coordinate, Coordinate, Coordinate::HashFunction> cameFrom;
        std::unordered_set<Coordinate, Coordinate::HashFunction> visited;

        queue.push(start);
        visited.insert(start);

        while (!queue.empty()) {
            Coordinate current = queue.front();
            queue.pop();

            if (current == end) {
                return reconstructPath(cameFrom, current);
            }

            for (const auto& neighbor: maze.getNeighbors(current)) {
                if (visited.insert(neighbor).second) {
                    // Если neighbor не был посещен
                    cameFrom[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }

        return {}; // Возвращаем пустой вектор, если путь не найден
    }

private:
    std::vector<Coordinate> reconstructPath(
        const std::unordered_map<Coordinate, Coordinate, Coordinate::HashFunction>& cameFrom,
        const Coordinate& current) {
        std::vector<Coordinate> path;
        Coordinate currentNode = current;

        while (cameFrom.find(currentNode) != cameFrom.end()) {
            path.push_back(currentNode);
            currentNode = cameFrom.at(currentNode);
        }

        std::reverse(path.begin(), path.end());
        return path;
    }
};
