#include "armor.h"
#include "item.h"
#include "character.h"
#include <random>

void Armor::DiscardEffect(Character &character){

    character.GetStats() -= this -> GetStats();

}

void Armor::ApplyEffect(Character &character){

    character.GetStats() += this -> GetStats();

}

int Armor::GetDamageReduction(){

    return int(this -> GetRarity()) + 1 * 3;

}

ArmorType Armor::GetArmorType() const {

    return armorType;

}

std::unique_ptr<Item> Armor::Clone() const {
    auto clone = std::make_unique<Armor>(this->armorType);
    clone->SetRarity(this->GetRarity());
    clone->SetId(this->GetId());
    clone->GetStats() = this->GetStats();
    return clone;
}

Armor::Armor(){
    
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> typeDist(0, 3);

    ArmorType armorTypeOption = Chest;
    int typeOption = typeDist(gen);

    switch(typeOption){

        case 0:

            armorType = ArmorType::Head;
            SetId(ArmorHeadTexture);
            break;

        case 1:

            armorType = ArmorType::Chest;
            SetId(ArmorChestTexture);
            break;

        case 2:

            armorType = ArmorType::Legs;
            SetId(ArmorLegsTexture);
            break;

        case 3:

            armorType = ArmorType::Feet;
            SetId(ArmorFeetTexture);
            break;

    }

}

Armor::Armor(ArmorType iArmorType){

    ArmorType armorTypeOption = Chest;

    switch(iArmorType){

        case Chest:

            armorTypeOption = Chest;
            SetId(ArmorChestTexture);
            break;

        case Legs:

            armorTypeOption = Legs;
            SetId(ArmorLegsTexture);
            break;

        case Feet:

            armorTypeOption = Feet;
            SetId(ArmorFeetTexture);
            break;

        case Head:

            armorTypeOption = Head;
            SetId(ArmorHeadTexture);
            break;

    }

    armorType = armorTypeOption;

}