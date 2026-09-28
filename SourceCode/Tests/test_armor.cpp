#include <gtest/gtest.h>
#include "armor.h"
#include "character.h"

TEST(ArmorTest, ConstructorTest) {
    Armor armor;
    
    EXPECT_TRUE(armor.GetId() == ArmorHeadTexture ||
                armor.GetId() == ArmorChestTexture ||
                armor.GetId() == ArmorLegsTexture ||
                armor.GetId() == ArmorFeetTexture);
}

TEST(ArmorTest, SpecificTypeConstructorTest) {
    Armor chestArmor(ArmorType::Chest);
    EXPECT_EQ(chestArmor.GetArmorType(), ArmorType::Chest);
    
    Armor headArmor(ArmorType::Head);
    EXPECT_EQ(headArmor.GetArmorType(), ArmorType::Head);
}

TEST(ArmorTest, CloneTest) {
    Armor original(ArmorType::Legs);
    original.SetRarity(ItemRarity::Epic);
    
    auto clone = original.Clone();
    auto* armorClone = dynamic_cast<Armor*>(clone.get());
    
    EXPECT_NE(armorClone, nullptr);
    EXPECT_EQ(armorClone->GetArmorType(), ArmorType::Legs);
    EXPECT_EQ(armorClone->GetRarity(), ItemRarity::Epic);
}