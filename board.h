#ifndef BOARD_H
#define BOARD_H

#include <functional>

class Board {
public:
    enum Status {
        Open, White, Black
    };

#define GRID(R1,R2,R3,R4,R5,R6,R7,R8) 0b##R1##R2##R3##R4##R5##R6##R7##R8

    Board() {
        taken = GRID(00000000,
                     00000000,
                     00000000,
                     00011000,
                     00011000,
                     00000000,
                     00000000,
                     00000000);
        owner = GRID(00000000,
                     00000000,
                     00000000,
                     00001000,
                     00010000,
                     00000000,
                     00000000,
                     00000000);
    }

    Status square(int x, int y) {
        auto mask = bit(x, y);
        if (taken & mask) {
            return (owner & mask) ? Black : White;
        }
        else {
            return Open;
        }
    }

    using Callback = const std::function<void(int, int)>&;

    void ifOpenSquare(int x, int y, Callback f);
    void findOpenSquaresAround(int x, int y, Callback f);

    bool play(Status who, int x, int y);

    void print();
    Board &setup(int x, int y, Status status);

    using Grid = unsigned long long;

    static Grid bit(int x, int y) {
        return 1L << (63 - (y * 8 + x));
    }

private:

    Grid taken; // bit set when a square is taken
    Grid owner; // bit set when owner is black

    static Grid flip(Grid taken, Grid owner, bool toBlack,
                     int x, int y, int dx, int dy);
};

#endif
