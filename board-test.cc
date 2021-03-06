#include "board.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Board is 8x8
// Players are White and Black
// Each player has 64 tokens

// Starting configuration is:
//  abcdefgh
// 1........0
// 2........1
// 3........2
// 4...wb...3
// 5...bw...4
// 6........5
// 7........6
// 8........7
//  01234567

// Board position is stated column then row, e.g. c6
// internal positions use 0..7 instead of a..h and 1..8

// Black moves first

TEST(BoardTest, InitialState) {
    Board b;
    EXPECT_EQ(Board::OpenSquare, b.square(0, 0));
    EXPECT_EQ(Board::OpenSquare, b.square(1, 0));
    EXPECT_EQ(Board::OpenSquare, b.square(7, 0));
    EXPECT_EQ(Board::OpenSquare, b.square(0, 1));
    EXPECT_EQ(Board::OpenSquare, b.square(1, 1));
    EXPECT_EQ(Board::OpenSquare, b.square(7, 1));
    EXPECT_EQ(Board::OpenSquare, b.square(0, 7));
    EXPECT_EQ(Board::OpenSquare, b.square(1, 7));
    EXPECT_EQ(Board::OpenSquare, b.square(7, 7));
    EXPECT_EQ(Board::WhiteSquare, b.square(3, 3));
    EXPECT_EQ(Board::BlackSquare, b.square(3, 4));
    EXPECT_EQ(Board::BlackSquare, b.square(4, 3));
    EXPECT_EQ(Board::WhiteSquare, b.square(4, 4));
}

TEST(BoardTest, BadValueBadPlay) {
    Board b;
    EXPECT_FALSE(b.play(Board::WhitePlayer, -1, 0));
    EXPECT_FALSE(b.play(Board::WhitePlayer, 8, 0));
    EXPECT_FALSE(b.play(Board::WhitePlayer, 0, -1));
    EXPECT_FALSE(b.play(Board::WhitePlayer, 0, 8));
}

TEST(BoardTest, TakenSquareBadPlay) {
    Board b;
    EXPECT_FALSE(b.play(Board::BlackPlayer, 3, 3));
    EXPECT_EQ(Board::WhiteSquare, b.square(3, 3));
    EXPECT_FALSE(b.play(Board::WhitePlayer, 3, 3));
}

TEST(BoardTest, NoFlipBadPlay) {
    Board b;
    EXPECT_FALSE(b.play(Board::BlackPlayer, 5, 3));
    EXPECT_EQ(Board::OpenSquare, b.square(5, 3));
    EXPECT_EQ(Board::WhiteSquare, b.square(3, 3));
    EXPECT_EQ(Board::BlackSquare, b.square(3, 4));
    EXPECT_EQ(Board::BlackSquare, b.square(4, 3));
    EXPECT_EQ(Board::WhiteSquare, b.square(4, 4));
}

TEST(BoardTest, PlayBlack) {
    Board b;
    EXPECT_TRUE(b.play(Board::BlackPlayer, 3, 2));
    EXPECT_EQ(Board::BlackSquare, b.square(3, 2));
    EXPECT_EQ(Board::BlackSquare, b.square(3, 3));
}

TEST(BoardTest, PlayWhite) {
    Board b;
    EXPECT_TRUE(b.play(Board::BlackPlayer, 3, 2));
    EXPECT_TRUE(b.play(Board::WhitePlayer, 2, 4));
    EXPECT_EQ(Board::WhiteSquare, b.square(2, 4));
    EXPECT_EQ(Board::WhiteSquare, b.square(3, 4));
}

TEST(BoardTest, BigPlayWhite) {
    Board b = Board()
        .setup(0, 3, Board::WhiteSquare)
        .setup(1, 3, Board::BlackSquare)
        .setup(2, 3, Board::BlackSquare)
        .setup(3, 3, Board::BlackSquare);
    EXPECT_EQ(Board::BlackSquare, b.square(3, 3));
    EXPECT_EQ(Board::BlackSquare, b.square(4, 3));
    EXPECT_TRUE(b.play(Board::WhitePlayer, 5, 3));
    EXPECT_EQ(Board::WhiteSquare, b.square(1, 3));
}

TEST(BoardTest, NoBoundBadPlay) {
    Board b = Board()
        .setup(0, 3, Board::BlackSquare)
        .setup(1, 3, Board::BlackSquare)
        .setup(2, 3, Board::BlackSquare)
        .setup(3, 3, Board::BlackSquare);
    EXPECT_FALSE(b.play(Board::WhitePlayer, 5, 3));
    EXPECT_EQ(Board::BlackSquare, b.square(1, 3));
}

TEST(BoardTest, OpenSquaresAroundSquare) {
    // ........0
    // ..ooo...1
    // ..o*o...2
    // ..owb...3
    // ...bw...4
    // ........5
    // ........6
    // ........7
    // 01234567

    Board b;
    std::vector<int> openSquares;
    b.findOpenSquaresAround(3, 2, [&](int x, int y) {
            openSquares.push_back(x * 10 + y);
        });
    EXPECT_EQ(openSquares.size(), 6);
    ASSERT_THAT(openSquares, testing::ElementsAre(21, 22, 23, 31, 41, 42));
}
