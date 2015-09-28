#include <iostream>
#include <climits>
#include "board.h"

void Board::setup(char *state) {
}

void Board::ifOpenSquare(int x, int y, Board::Callback f) {
    if (hasOpenSquare(x, y)) {
        f(x, y);
    }
}

void Board::findOpenSquaresAround(int x, int y, Board::Callback f) {
    ifOpenSquare(x-1, y-1, f);
    ifOpenSquare(x-1, y,   f);
    ifOpenSquare(x-1, y+1, f);

    ifOpenSquare(x,   y-1, f);
    ifOpenSquare(x,   y+1, f);

    ifOpenSquare(x+1, y-1, f);
    ifOpenSquare(x+1, y,   f);
    ifOpenSquare(x+1, y+1, f);
}

bool Board::play(Board::Player who, int x, int y) {
    auto mask = bit(x, y);

    if ((0 <= y && y <= 7 && 0 <= x && x <= 7) &&
        (0 == (taken & mask)))
    {
        auto toBlack = who == BlackPlayer;
        auto changed = owner;

        changed = flip(taken, changed, toBlack, x, y, -1, -1);
        changed = flip(taken, changed, toBlack, x, y, -1,  0);
        changed = flip(taken, changed, toBlack, x, y, -1,  1);

        changed = flip(taken, changed, toBlack, x, y,  0, -1);
        changed = flip(taken, changed, toBlack, x, y,  0,  1);

        changed = flip(taken, changed, toBlack, x, y,  1, -1);
        changed = flip(taken, changed, toBlack, x, y,  1,  0);
        changed = flip(taken, changed, toBlack, x, y,  1,  1);

        if (changed != owner) {
            taken |= mask;
            owner = toBlack ? changed | mask : changed;
            return true;
        }
    }

    return false;
}

Board::Grid Board::flip(Board::Grid taken, Board::Grid owner, bool toBlack,
                        int x, int y, int dx, int dy)
{
    auto rollback = owner;

    for (;;) {
        x += dx;
        y += dy;

        if (0 <= y && y <= 7 && 0 <= x && x <= 7) {
            auto mask = bit(x, y);
            if (taken & mask) {
                if (owner & mask) {
                    if (toBlack) {
                        return owner;
                    }
                    else {
                        owner &= ~mask;
                    }
                }
                else {
                    if (toBlack) {
                        owner |= mask;
                    }
                    else {
                        return owner;
                    }
                }
            }
            else {
                return rollback;
            }
        }
        else {
            return rollback;
        }
    }
}

void Board::print() {
    std::cout << "  abcdefgh\n";
    for (int y = 0; y <= 7; ++y) {
        std::cout << (char)('1' + y) << ' ';
        for (int x = 0; x <= 7; ++x) {
            switch (square(x, y)) {
            case OpenSquare:
                std::cout << ' ';
                break;
            case WhiteSquare:
                std::cout << 'o';
                break;
            case BlackSquare:
                std::cout << '#';
                break;
            }
        }
        std::cout << '\n';
    }
}

Board &Board::setup(int x, int y, Board::SquareStatus status) {
    auto mask = bit(x, y);
    if (status == OpenSquare) {
        taken &= ~mask;
    }
    else {
        taken |= mask;
        if (status == BlackSquare) {
            owner |= mask;
        }
        else {
            owner &= ~mask;
        }
    }
    return *this;
}

Board::Grid Board::reverseBits(Board::Grid v) {
    // http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
    auto r = v;
    auto s = sizeof(v) * CHAR_BIT - 1;
    for (v >>= 1; v; v >>= 1) {
        r <<= 1;
        r |= v & 1;
        s--;
    }
    r <<= s;
    return r;
}
