#include "inventory.h"
#include <iostream>
#include <typeinfo>
#include <memory>

LockpickBundle &Inventory::GetLockpicks(){

    return lockpicks;

}

std::unique_ptr<Armor> Inventory::SwapArmor(Armor& newArmor){

    std::unique_ptr<Armor> oldItem;
    
    switch (newArmor.GetArmorType()){

        case Head:

            oldItem = std::make_unique<Armor>(helmet);
            helmet = newArmor;
            break;

        case Chest:

            oldItem = std::make_unique<Armor>(chest);
            chest = newArmor;
            break;

        case Legs:

            oldItem = std::make_unique<Armor>(legs);
            legs = newArmor;
            break;

        case Feet:

            oldItem = std::make_unique<Armor>(feet);
            feet = newArmor;
            break;

    }
    
    return oldItem;

}

std::unique_ptr<Weapon> Inventory::SwapWeapon(Weapon& newWeapon){

    auto oldItem = std::make_unique<Weapon>(weapon);
    weapon = newWeapon;
    return oldItem;

}

void Inventory::AddPotion(Potion& newPotion){

    potions.push_back(newPotion);

}

void Inventory::AddLockpicks(LockpickBundle& newLockpicks){

    lockpicks += newLockpicks.GetAmount();

}

std::unique_ptr<Item> Inventory::SwapItems(std::unique_ptr<Item> newItem){

    if (!newItem) return nullptr;
    
    std::unique_ptr<Item> oldItem;
    
    if (auto* armor = dynamic_cast<Armor*>(newItem.get())){

        oldItem = SwapArmor(*armor);

    }else if (auto* weapon = dynamic_cast<Weapon*>(newItem.get())){

        oldItem = SwapWeapon(*weapon);

    }else if (auto* potion = dynamic_cast<Potion*>(newItem.get())){

        AddPotion(*potion);

    }else if (auto* lockpickBundle = dynamic_cast<LockpickBundle*>(newItem.get())){

        AddLockpicks(*lockpickBundle);

    }
    
    return oldItem;

}

std::unique_ptr<Item> Inventory::SwapItems(Item* newItem){

    if (!newItem) return nullptr;
    
    std::unique_ptr<Item> itemClone = newItem->Clone();
    return SwapItems(std::move(itemClone));
    
}