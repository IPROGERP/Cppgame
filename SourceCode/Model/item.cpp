#include "item.h"
#include <random>

ItemRarity Item::GetRarity() const{

	return rarity;

}

void Item::SetRarity(ItemRarity itemRarity){

	this -> rarity = itemRarity;

}

Stats &Item::GetStats(){

	return stats;

}

const Stats &Item::GetStats() const {

	return stats;

}

ItemRarity Item::GenerateRarity(){

	static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 100);
	int chance = dist(gen);	
	if (chance < 5){

		stats = {10,10,10};
		return Champion;

	}else if(chance < 10){

		stats = {8,8,8};
		return Legendary;

	}else if(chance < 15){

		stats = {6,6,6};
		return Epic;

	}else if (chance < 20){

		stats = {4,4,4};
		return Rare;

	}else{

		stats = {2,2,2};
		return Common;

	}
}