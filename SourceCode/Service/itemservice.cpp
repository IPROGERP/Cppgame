#include "itemservice.h"
#include <random>
#include <iostream>

std::mt19937& GetRandomEngine(){

    static std::mt19937 gen(std::random_device{}());
    return gen;

}

ItemRarity ItemFactory::GetRandomRarity(){

    auto& gen = GetRandomEngine();
    std::uniform_int_distribution<int> dist(0, 100);
    int chance = dist(gen);
    
    if (chance < 5) return Champion;
    if (chance < 10) return Legendary;
    if (chance < 20) return Epic;
    if (chance < 40) return Rare;
    return Common;

}

std::unique_ptr<Weapon> ItemFactory::CreateWeapon(ItemRarity rarity){

    auto weapon = std::make_unique<Weapon>();

    auto& gen = GetRandomEngine();
    std::uniform_int_distribution<int> modDist(0, 4);
    WeaponModification mod = static_cast<WeaponModification>(modDist(gen));
    
    if (rarity >= Epic){

        mod = static_cast<WeaponModification>((modDist(gen) % 3) + 1);

    }
    
    weapon->SetModification(mod);
    weapon->SetRarity(rarity);
    
    Stats stats{};
    switch (rarity){

        case Common:    stats.strength = 1; stats.agility = 1; break;
        case Rare:      stats.strength = 2; stats.agility = 2; stats.endurance = 1; break;
        case Epic:      stats.strength = 3; stats.agility = 3; stats.endurance = 2; break;
        case Legendary: stats.strength = 5; stats.agility = 4; stats.endurance = 3; break;
        case Champion:  stats.strength = 7; stats.agility = 5; stats.endurance = 4; break;

    }
    
    weapon->GetStats() = stats;
    
    return weapon;

}

std::unique_ptr<Armor> ItemFactory::CreateArmor(ItemRarity rarity){

    auto& gen = GetRandomEngine();
    std::uniform_int_distribution<int> typeDist(0, 3);
    ArmorType type = static_cast<ArmorType>(typeDist(gen));
    
    auto armor = std::make_unique<Armor>(type);
    armor->SetRarity(rarity);
    
    Stats stats{};
    switch (rarity){

        case Common:
            stats.endurance = 1;
            if (type == Chest) stats.endurance = 2;
            break;
        case Rare:
            stats.endurance = 2;
            if (type == Chest) stats.endurance = 3;
            break;
        case Epic:
            stats.endurance = 3;
            stats.strength = 1;
            if (type == Chest) { stats.endurance = 4; stats.strength = 2; }
            break;
        case Legendary:
            stats.endurance = 4;
            stats.strength = 2;
            stats.agility = 1;
            if (type == Chest) { stats.endurance = 5; stats.strength = 3; }
            break;
        case Champion:
            stats.endurance = 5;
            stats.strength = 3;
            stats.agility = 2;
            if (type == Chest) { stats.endurance = 6; stats.strength = 4; stats.agility = 2; }
            break;

    }
    
    armor->GetStats() = stats;
    
    return armor;

}

std::unique_ptr<Potion> ItemFactory::CreatePotion(ItemRarity rarity){

    auto potion = std::make_unique<Potion>();
    potion->SetRarity(rarity);
    
    Stats stats{};
    switch (rarity){

        case Common:    stats.endurance = 1; break;
        case Rare:      stats.endurance = 2; break;
        case Epic:      stats.endurance = 3; stats.agility = 1; break;
        case Legendary: stats.endurance = 4; stats.agility = 2; stats.strength = 1; break;
        case Champion:  stats.endurance = 5; stats.agility = 3; stats.strength = 2; break;

    }
    
    potion->GetStats() = stats;
    
    return potion;

}

std::unique_ptr<LockpickBundle> ItemFactory::CreateLockpicks(ItemRarity rarity){

    auto lockpicks = std::make_unique<LockpickBundle>();
    lockpicks->SetRarity(rarity);
    
    Stats stats{};
    switch (rarity){

        case Common:    stats.agility = 1; break;
        case Rare:      stats.agility = 2; break;
        case Epic:      stats.agility = 3; break;
        case Legendary: stats.agility = 4; stats.endurance = 1; break;
        case Champion:  stats.agility = 5; stats.endurance = 2; break;

    }
    
    lockpicks->GetStats() = stats;
    
    return lockpicks;

}

std::unique_ptr<Item> ItemFactory::CreateRandomItem(){

    auto& gen = GetRandomEngine();

    std::uniform_int_distribution<int> typeDist(0, 3);
    int itemType = typeDist(gen);

    ItemRarity rarity = GetRandomRarity();

    switch (itemType){

        case 0: return CreateWeapon(rarity);
        case 1: return CreateArmor(rarity);
        case 2: return CreatePotion(rarity);
        case 3: return CreateLockpicks(rarity);
        default: return CreateWeapon(Common);

    }
}

std::unique_ptr<Item> ItemFactory::CreateItemWithRarity(ItemRarity rarity){

    auto& gen = GetRandomEngine();
    std::uniform_int_distribution<int> typeDist(0, 3);
    int itemType = typeDist(gen);
    
    switch (itemType){
  
        case 0: return CreateWeapon(rarity);
        case 1: return CreateArmor(rarity);
        case 2: return CreatePotion(rarity);
        case 3: return CreateLockpicks(rarity);
        default: return CreateWeapon(rarity);

    }

}

std::unique_ptr<Item> ItemFactory::CreateItemForEnemy(){

    auto& gen = GetRandomEngine();
    
    std::uniform_int_distribution<int> dropChance(0, 99);
    if (dropChance(gen) >= 100){

        return nullptr;

    }
    std::uniform_int_distribution<int> rarityDist(0, 100);
    int roll = rarityDist(gen);
    
    ItemRarity rarity;
    if (roll < 2) rarity = Champion;
    else if (roll < 5) rarity = Legendary;
    else if (roll < 15) rarity = Epic;
    else if (roll < 40) rarity = Rare;
    else rarity = Common;
    
    return CreateItemWithRarity(rarity);
    
}