#include <gtest/gtest.h>
#include "inventory.h"
#include "armor.h"
#include "weapon.h"
#include "potion.h"
#include "lockpickbundle.h"

class InventoryTest : public ::testing::Test {
protected:
    Inventory inventory;
    
    void SetUp() override {
        
    }
};

TEST_F(InventoryTest, AddLockpicksTest) {
    LockpickBundle lockpicks;
    int initialAmount = inventory.GetLockpicks().GetAmount();
    
    inventory.AddLockpicks(lockpicks);
    
    EXPECT_GT(inventory.GetLockpicks().GetAmount(), initialAmount);
}

TEST_F(InventoryTest, SwapItemsWithArmor) {
    std::unique_ptr<Item> armor = std::make_unique<Armor>(ArmorType::Chest);
    auto oldItem = inventory.SwapItems(std::move(armor));
    
    EXPECT_NE(oldItem, nullptr);
}