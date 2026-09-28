#include <gtest/gtest.h>
#include "item.h"
#include <memory>

class ItemTest : public ::testing::Test {
protected:
    class TestItem : public Item {
    public:
        void DiscardEffect(Character&) override {}
        void ApplyEffect(Character&) override {}
        std::unique_ptr<Item> Clone() const override {
            return std::make_unique<TestItem>();
        }
    };
};

TEST_F(ItemTest, RarityTest) {
    TestItem item;
    item.SetRarity(ItemRarity::Epic);
    
    EXPECT_EQ(item.GetRarity(), ItemRarity::Epic);
}

TEST_F(ItemTest, StatsTest) {
    TestItem item;
    item.GetStats() = {10, 20, 30};
    
    EXPECT_EQ(item.GetStats().strength, 10);
    EXPECT_EQ(item.GetStats().agility, 20);
    EXPECT_EQ(item.GetStats().endurance, 30);
}

TEST_F(ItemTest, GenerateRarityTest) {
    TestItem item;
    auto rarity = item.GenerateRarity();
    
    EXPECT_TRUE(rarity >= ItemRarity::Common && rarity <= ItemRarity::Champion);
}