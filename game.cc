#include <iostream>
#include "game.h"

void Game::beginGame() {
    round = 1;
    gameOver = false;
    boardChanged = false;
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::endRound() {
    ++round;
    gameOver = !boardChanged;
    boardChanged = false;
}

bool Game::playNextMove(Board::Status who) {
    for (int y = 0; y <= 7; ++y) {
        for (int x = 0; x <= 7; ++x) {
            if (play(who, x, y)) {
                boardChanged = true;
                return true;
            }
        }
    }
    return false;
}

void Game::print() {
    std::cout << "--------------------- Round " << round << std::endl;
    board.print();
}

Game &Game::setup(int x, int y, Board::Status status) {
    board.setup(x, y, status);
    return *this;
}
