#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "../Model/item.h"
#include "../Model/weapon.h"
#include "../Model/armor.h"
#include "../Model/potion.h"
#include "../Model/lockpickbundle.h"
#include <memory>

class ItemFactory {
public:

    static std::unique_ptr<Item> CreateRandomItem();
    
    static std::unique_ptr<Item> CreateItemWithRarity(ItemRarity rarity);

    static std::unique_ptr<Item> CreateItemForEnemy();
    
private:
    static ItemRarity GetRandomRarity();

    static std::unique_ptr<Weapon> CreateWeapon(ItemRarity rarity);
    static std::unique_ptr<Armor> CreateArmor(ItemRarity rarity);
    static std::unique_ptr<Potion> CreatePotion(ItemRarity rarity);
    static std::unique_ptr<LockpickBundle> CreateLockpicks(ItemRarity rarity);
};

#endif