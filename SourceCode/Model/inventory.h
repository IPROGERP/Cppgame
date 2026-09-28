#ifndef INVENTORY_H
#define INVENTORY_H

#include "armor.h"
#include "weapon.h"
#include "potion.h"
#include "memory"
#include "lockpickbundle.h"
#include "vector"

/**
 * @brief class that represent inventory in game
 */
class Inventory {
    public:
        /**
        * @brief helmet instance
        */
        Armor helmet{Head};
        /**
        * @brief chestplate instance
        */
        Armor chest{Chest};
        /**
        * @brief legs instance
        */
        Armor legs{Legs};
        /**
        * @brief feet instance
        */
        Armor feet{Feet};
        /**
        * @brief weapon instance
        */
        Weapon weapon{};
        /**
        * @brief potion instance
        */
        std::vector<Potion> potions{};
        /**
        * @brief lockpicks instance
        */
        LockpickBundle lockpicks{};
        /**
        * @brief method for swaping items via unique_ptr
        */
        std::unique_ptr<Item> SwapItems(std::unique_ptr<Item> newItem);
        /**
        * @brief method for swaping items via ptr
        */
        std::unique_ptr<Item> SwapItems(Item* newItem);
        /**
        * @brief method for swapping armor
        */
        std::unique_ptr<Armor> SwapArmor(Armor& newArmor);
        /**
        * @brief method for swapping weapon
        */
        std::unique_ptr<Weapon> SwapWeapon(Weapon& newWeapon);
        /**
        * @brief method for adding potions
        */
        void AddPotion(Potion& newPotion); 
        /**
        * @brief method for adding lockpicks
        */
        void AddLockpicks(LockpickBundle& newLockpicks); 
        /**
        * @brief getter for lockpicks
        */
        LockpickBundle &GetLockpicks();
    };

#endif
