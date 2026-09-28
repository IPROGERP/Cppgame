#include <gtest/gtest.h>
#include "weapon.h"
#include "character.h"

TEST(WeaponTest, ConstructorTest) {
    Weapon weapon;
    
    EXPECT_EQ(weapon.GetId(), WeaponTexture);
    EXPECT_GT(weapon.GetDamage(), 0);
}

TEST(WeaponTest, GetDamageTest) {
    Weapon weapon;
    weapon.SetRarity(ItemRarity::Epic);
    
    int damage = weapon.GetDamage();
    EXPECT_EQ(damage, 9);
}

TEST(WeaponTest, CloneTest) {
    Weapon original;
    original.SetRarity(ItemRarity::Rare);
    
    auto clone = original.Clone();
    EXPECT_NE(clone, nullptr);
    EXPECT_EQ(clone->GetRarity(), ItemRarity::Rare);
}

TEST(WeaponTest, ApplyDiscardEffectTest) {
    Weapon weapon;
    weapon.SetRarity(ItemRarity::Common);
    
    Character character;
    int initialDamage = character.GetDamage();
    
    weapon.ApplyEffect(character);
    EXPECT_GT(character.GetDamage(), initialDamage);
    
    weapon.DiscardEffect(character);
    EXPECT_EQ(character.GetDamage(), initialDamage);
}