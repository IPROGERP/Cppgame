#include <gtest/gtest.h>
#include "level.h"
#include "enemy.h"

class LevelTest : public ::testing::Test {
protected:
    Level level;
};

TEST_F(LevelTest, ConstructorTest) {
    EXPECT_GT(level.GetMap().GetRows(), 0);
    EXPECT_GT(level.GetMap().GetColumns(), 0);
}

TEST_F(LevelTest, GenerateEnemiesTest) {
    size_t initialCount = level.GetEnemies().size();
    level.GenerateEnemies(5);
    
    EXPECT_EQ(level.GetEnemies().size(), initialCount + 5);
}

TEST_F(LevelTest, AddEnemyTest) {
    Enemy enemy;
    size_t initialCount = level.GetEnemies().size();
    
    level.AddEnemy(std::move(enemy));
    
    EXPECT_EQ(level.GetEnemies().size(), initialCount + 1);
}

TEST_F(LevelTest, GetValidCoordinateTest) {
    Point coord = level.GetValidCoordinate();
    
    EXPECT_GE(coord.x, 0);
    EXPECT_GE(coord.y, 0);
}

TEST_F(LevelTest, SpawnLadderTest) {
    level.SpawnLadder();
    
    auto& ladder = level.GetLadder();
    EXPECT_NE(ladder->GetId(), 0);
}