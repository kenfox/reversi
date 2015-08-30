#include "game.h"
#include "gtest/gtest.h"

TEST(GameTest, InitialState) {
    Game g;
    EXPECT_EQ(Board::White, g.square(3, 3));
    EXPECT_EQ(Board::Black, g.square(3, 4));
}

TEST(GameTest, SimplePlay) {
    Game g;
    EXPECT_TRUE(g.play(Board::Black, std::make_pair(3, 2)));
    EXPECT_TRUE(g.play(Board::White, std::make_pair(2, 4)));
    EXPECT_EQ(Board::White, g.square(2, 4));
    EXPECT_EQ(Board::White, g.square(3, 4));
}

TEST(GameTest, TwoTurnsAutoPlay) {
    Game g;
    g.beginGame();
    EXPECT_TRUE(g.playNextMove(Board::Black));
    EXPECT_TRUE(g.playNextMove(Board::White));
}
