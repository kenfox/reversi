#include <iostream>
#include "game.h"

void Game::beginGame() {
    round = 1;
    gameOver = false;
    boardChanged = false;
    for (int x = 0; x <= 7; ++x) {
        for (int y = 0; y <= 7; ++y) {
            if (!board.openSquare(x, y)) {
                appendPossibleMoves(x, y);
            }
        }
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
            auto playedPosition = *i;
            boardChanged = true;
            possibleMove.erase(i);
            appendPossibleMoves(playedPosition.first, playedPosition.second);
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

void Game::appendPossibleMoves(int x, int y) {
    board.findOpenSquaresAround(x, y, [&](int x, int y) {
            auto mask = Board::bit(x, y);
            if (0 == (seen & mask)) {
                seen |= mask;
                possibleMove.emplace_back(x, y);
            }
        });
}
