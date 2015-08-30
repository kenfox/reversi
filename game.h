#ifndef GAME_H
#define GAME_H

#include <utility>
#include <vector>
#include "board.h"

class Game {
public:
    using Position = std::pair<int, int>;

    Game() : board(), possibleMove(), seen() {
        round = 0;
        boardChanged = false;
        gameOver = false;
    }

    void beginGame();
    bool isGameOver();
    void endRound();

    bool play(Board::Status who, Position p);
    bool playNextMove(Board::Status who);

    void print();
    Game &setup(int x, int y, Board::Status status);
    Board::Status square(int x, int y) {
        return board.square(x, y);
    }

private:

    Board board;
    std::vector<Position> possibleMove;
    Board::Grid seen;

    int round;
    bool boardChanged;
    bool gameOver;
};

#endif
