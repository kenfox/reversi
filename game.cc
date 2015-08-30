#include <iostream>
#include "game.h"

void Game::beginGame() {
    round = 1;
    gameOver = false;
    boardChanged = false;
    for (int x = 2; x <= 5; ++x) {
        seen |= Board::bit(x, 2); possibleMove.emplace_back(x, 2);
        seen |= Board::bit(x, 5); possibleMove.emplace_back(x, 5);
    }
    for (int y = 3; y <= 4; ++y) {
        seen |= Board::bit(2, y); possibleMove.emplace_back(2, y);
        seen |= Board::bit(5, y); possibleMove.emplace_back(5, y);
    }
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::endRound() {
    ++round;
    gameOver = !boardChanged;
    boardChanged = false;
}

bool Game::play(Board::Status who, Game::Position p) {
    return board.play(who, p.first, p.second);
}

bool Game::playNextMove(Board::Status who) {
    for (auto i = possibleMove.cbegin(); i != possibleMove.cend(); ++i) {
        if (play(who, *i)) {
            auto p = *i;
            boardChanged = true;
            possibleMove.erase(i);
            board.findOpenSquaresAround(p.first, p.second, [&](int x, int y) {
                    auto mask = Board::bit(x, y);
                    if (0 == (seen & mask)) {
                        seen |= mask;
                        possibleMove.emplace_back(x, y);
                    }
                });
            return true;
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
