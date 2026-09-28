#include "character.h"
#include <iostream>

void Character::AddExp(int amount){

    exp += amount;
    
    while (CheckLevelUp()){

        LevelUp();

    }

}

bool Character::CheckLevelUp(){

    return exp >= expToNextLevel;

}

void Character::LevelUp(){

    level++;
    exp -= expToNextLevel;
    expToNextLevel = static_cast<int>(expToNextLevel * 1.5);
    
    
    int statChoice = rand() % 3;
    switch(statChoice){

        case 0: statsCharacter.strength += 2; break;
        case 1: statsCharacter.agility += 2; break;
        case 2: statsCharacter.endurance += 2; break;
        
    }
    
    SetCurrentHp(GetMaxHp());

}

Inventory &Character::GetInventory(){

	return inventoryCharacter;
			
}

Character::Character(){

	SetCoordinate(0,0);
	SetId(CharacterTexture);
    SetInvincibleFrame(10000);
    SetDamage(100);
    statsCharacter = {10, 10, 10};

}


Stats &Character::GetStats(){

	return statsCharacter;

}