
#include "GameLogic.cpp"
class Game {
public:
    Game() {}

    void start() {
        GameLogic game = GameLogic::gameLogicCreator();
        game.renderMazeWithoutPass();
        game.renderMazeWithPath();
    }
};