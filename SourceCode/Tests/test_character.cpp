#include <gtest/gtest.h>
#include "character.h"

class CharacterTest : public ::testing::Test {
protected:
    Character character;
};

TEST_F(CharacterTest, AddExperienceTest) {
    int initialExp = 0;
    character.AddExp(50);
        
    EXPECT_EQ(character.CheckLevelUp(), false);
}

TEST_F(CharacterTest, LevelUpTest) {
    character.AddExp(1000);
    
    int levelBefore = 1;
}

TEST_F(CharacterTest, InventoryAccessTest) {
    auto& inventory = character.GetInventory();
    EXPECT_NE(&inventory, nullptr);
}

TEST_F(CharacterTest, StatsAccessTest) {
    auto& stats = character.GetStats();
    EXPECT_EQ(stats.strength, 10);
    EXPECT_EQ(stats.agility, 10);
    EXPECT_EQ(stats.endurance, 10);
}