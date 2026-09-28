#include "potion.h"
#include "character.h"
#include <iostream>

void Potion::DiscardEffect(Character &character){

    character.GetStats() -= this -> GetStats();

}

void Potion::ApplyEffect(Character &character){

    character.GetStats() += this -> GetStats();

}

std::unique_ptr<Item> Potion::Clone() const {

    auto clone = std::make_unique<Potion>();
    clone->SetRarity(this->GetRarity());
    clone->SetId(this->GetId());
    clone->GetStats() = this->GetStats();
    return clone;

}

Potion::Potion(){

    ItemRarity rarity = this->GenerateRarity();
    this->SetRarity(rarity);
    SetId(PotionTexture);

}

