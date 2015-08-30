#include "board.h"

bool Board::play(Board::Status who, int x, int y) {
    auto mask = bit(x, y);

    if ((who == White || who == Black) &&
        (0 <= y && y <= 7 && 0 <= x && x <= 7) &&
        (0 == (taken & mask)))
    {
        auto toBlack = who == Black;
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

Board &Board::setup(int x, int y, Board::Status status) {
    auto mask = bit(x, y);
    if (status == Open) {
        taken &= ~mask;
    }
    else {
        taken |= mask;
        if (status == Black) {
            owner |= mask;
        }
        else {
            owner &= ~mask;
        }
    }
    return *this;
}
