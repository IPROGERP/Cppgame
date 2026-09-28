#include <gtest/gtest.h>
#include "potion.h"
#include "character.h"

TEST(PotionTest, ConstructorTest) {
    Potion potion;
    
    EXPECT_EQ(potion.GetId(), PotionTexture);
    EXPECT_NE(potion.GetRarity(), ItemRarity::Champion);
}

TEST(PotionTest, ApplyDiscardEffectTest) {
    Potion potion;
    potion.GetStats() = {5, 5, 5};
    
    Character character;
    Stats initialStats = character.GetStats();
    
    potion.ApplyEffect(character);
    Stats afterApply = character.GetStats();
    
    EXPECT_EQ(afterApply.strength, initialStats.strength + 5);
    EXPECT_EQ(afterApply.agility, initialStats.agility + 5);
    EXPECT_EQ(afterApply.endurance, initialStats.endurance + 5);
    
    potion.DiscardEffect(character);
    Stats afterDiscard = character.GetStats();
    
    EXPECT_EQ(afterDiscard.strength, initialStats.strength);
    EXPECT_EQ(afterDiscard.agility, initialStats.agility);
    EXPECT_EQ(afterDiscard.endurance, initialStats.endurance);
}

TEST(PotionTest, CloneTest) {
    Potion original;
    original.SetRarity(ItemRarity::Rare);
    
    auto clone = original.Clone();
    EXPECT_NE(clone, nullptr);
    EXPECT_EQ(clone->GetRarity(), ItemRarity::Rare);
    EXPECT_EQ(clone->GetId(), PotionTexture);
}