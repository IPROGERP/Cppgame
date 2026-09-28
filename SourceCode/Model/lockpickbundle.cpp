#include "lockpickbundle.h"
#include "character.h"
#include <iostream>

LockpickBundle::LockpickBundle(){

    lockpickAmount = 3;
    this -> SetRarity(Common);
    SetId(LockpickTexture);

}

void LockpickBundle::DiscardEffect(Character &character){

    if (lockpickAmount > 0){

        lockpickAmount--;
        
    }

}

void LockpickBundle::ApplyEffect(Character &character){

    int currentAmount = lockpickAmount;
    character.GetInventory().GetLockpicks() += currentAmount;
    lockpickAmount = 0;

}

std::unique_ptr<Item> LockpickBundle::Clone() const {

    auto clone = std::make_unique<LockpickBundle>();
    clone->SetRarity(this->GetRarity());
    clone->SetId(this->GetId());
    clone->GetStats() = this->GetStats();
    return clone;

}

LockpickBundle& LockpickBundle::operator-=(int amount){

    if (lockpickAmount >= amount){
        
        lockpickAmount -= amount;
        
    }else{

        lockpickAmount = 0;

    }
    return *this;
}

LockpickBundle& LockpickBundle::operator+=(int amount){

    lockpickAmount += amount;
    return *this;

}

int LockpickBundle::GetAmount(){

    return lockpickAmount;

}
int LockpickBundle::GetChance(){

    return 10;

}

void LockpickBundle::SetAmount(int amount){

    lockpickAmount = amount;

}