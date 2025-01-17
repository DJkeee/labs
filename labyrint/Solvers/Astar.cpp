#pragma once

#include "../Maze/Maze.cpp"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include "ISolver.cpp"

class AStarSolver : public ISolver {
public:
    std::vector<Coordinate> solve(Maze& maze, Coordinate start, Coordinate end) override {
        auto cmp = [](const Node& a, const Node& b) { return a.fScore > b.fScore; };
        std::priority_queue<Node, std::vector<Node>, decltype(cmp)> openPriorityQueue(cmp);
        std::unordered_set<Coordinate, Coordinate::HashFunction> closedSet;
        std::unordered_map<Coordinate, double, Coordinate::HashFunction> gScore;
        std::unordered_map<Coordinate, Coordinate, Coordinate::HashFunction> cameFrom;

        gScore[start] = 0.0;
        openPriorityQueue.emplace(start, heuristic(start, end));

        while (!openPriorityQueue.empty()) {
            Node currentNode = openPriorityQueue.top();
            openPriorityQueue.pop();
            Coordinate current = currentNode.coordinate;

            if (current == end) {
                return reconstructPath(cameFrom, current);
            }

            closedSet.insert(current);

            for (const Coordinate& neighbor: maze.getNeighbors(current)) {
                if (closedSet.find(neighbor) != closedSet.end()) {
                    continue;
                }

                double moveCost = maze.getCellCost(neighbor);
                double tentativeGScore = gScore[current] + moveCost;

                if (gScore.find(neighbor) == gScore.end() || tentativeGScore < gScore[neighbor]) {
                    cameFrom[neighbor] = current;
                    gScore[neighbor] = tentativeGScore;
                    double fScore = tentativeGScore + heuristic(neighbor, end);
                    openPriorityQueue.emplace(neighbor, fScore);
                }
            }
        }

        return {};
    }

private:
    struct Node {
        Coordinate coordinate;
        double fScore;

        Node(const Coordinate& coord, double f) : coordinate(coord), fScore(f) {
        }
    };

    std::vector<Coordinate> reconstructPath(
        const std::unordered_map<Coordinate, Coordinate, Coordinate::HashFunction>& cameFrom,
        Coordinate current) {
        std::vector<Coordinate> path;
        while (cameFrom.find(current) != cameFrom.end()) {
            path.push_back(current);
            current = cameFrom.at(current);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    double heuristic(const Coordinate& a, const Coordinate& b) {
        return std::abs(a.row - b.row) + std::abs(a.col - b.col);
    }
};
