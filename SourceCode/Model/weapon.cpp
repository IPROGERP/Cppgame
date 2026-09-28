#include "weapon.h"
#include "character.h"

void Weapon::DiscardEffect(Character &character){

    character.GetStats() -= this -> GetStats();
    int currentDamage = character.GetDamage();
    int weaponDamage = this->GetDamage();
    character.SetDamage(currentDamage - weaponDamage);

}

void Weapon::ApplyEffect(Character &character){

    character.GetStats() += this -> GetStats();
	int currentDamage = character.GetDamage();
    int weaponDamage = this->GetDamage();
    character.SetDamage(currentDamage + weaponDamage);

}

std::unique_ptr<Item> Weapon::Clone() const {

    auto clone = std::make_unique<Weapon>();
    clone->SetModification(this->weaponModification);
    clone->SetRarity(this->GetRarity());
    clone->SetId(this->GetId());
    clone->GetStats() = this->GetStats();
    return clone;

}

int Weapon::GetDamage(){

    return int(this -> GetRarity()) * 3 + 3;

}

Weapon::Weapon(){

    SetId(WeaponTexture);
        switch(GetRarity()){
        case Common:
            GetStats() = {1, 0, 0};
            break;
        case Rare:
            GetStats() = {2, 1, 0};
            break;
        case Epic:
            GetStats() = {3, 2, 1};
            break;
        case Legendary:
            GetStats() = {4, 3, 2};
            break;
        case Champion:
            GetStats() = {5, 4, 3};
            break;
    }

}

