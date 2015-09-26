#include "game.h"
#include "gtest/gtest.h"

TEST(GameTest, InitialState) {
    Game g;
    EXPECT_EQ(Board::WhiteSquare, g.square(3, 3));
    EXPECT_EQ(Board::BlackSquare, g.square(3, 4));
}

TEST(GameTest, TwoTurnsAutoPlay) {
    Game g;
    g.beginGame();
    EXPECT_TRUE(g.playNextMove());
    EXPECT_TRUE(g.playNextMove());
}
