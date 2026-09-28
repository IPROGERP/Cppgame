#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>
#include "gameobject.h"

class Character;

enum ItemRarity{

	Common,
	Rare,
	Epic,
	Legendary,
	Champion

};

enum ArmorType{

	Head,
	Chest,
	Legs,
	Feet,

};

enum WeaponModification{

	Holy,
	Ice,
	Fire,
	Sharp,
	None

};

/**
 * @brief stats struct 
 */
struct Stats{

	/**
 	* @brief instance of streangth
 	*/
	int strength{0};
	/**
 	* @brief instance of agility
 	*/
	int agility{0};
	/**
 	* @brief instance of instance on endurance
 	*/
	int endurance{0};

	/**
 	* @brief overload operator +=
 	*/
	Stats &operator += (const Stats &other){

		strength += other.strength;
		agility += other.agility;
		endurance += other.endurance;
		return *this;

	}

	/**
 	* @brief overload operator -=
 	*/
	Stats &operator -= (const Stats &other){

		strength -= other.strength;
		agility -= other.agility;
		endurance -= other.endurance;
		return *this;

	}

	/**
 	* @brief method for resetting stats
 	*/
	void Reset(){

		strength = 0;
		agility = 0;
		endurance = 0;

	}

};

/**
 * @brief method that represent items in game
*/
class Item : public GameObject { 
	

	private:
		/**
 		* @brief default stats for every item
 		*/
		Stats stats{1,1,1};
		/**
 		* @brief default rarity for item
 		*/
		ItemRarity rarity{Common};

	public:

	/**
 	* @brief default constructor
 	*/
	Item(){this -> GenerateRarity();};
	/**
 	* @brief virtual method for destructor
 	*/
	virtual ~Item() = default;

	/**
 	* @brief virtual method for applying effect
 	*/
	virtual void ApplyEffect(Character &character) = 0;
	/**
 	* @brief virtual method for discarding effect
 	*/
	virtual void DiscardEffect(Character &character) = 0;
	/**
 	* @brief virual method for cloning item
 	*/
	virtual std::unique_ptr<Item> Clone() const = 0;

	/**
 	* @brief getter for stats
 	*/
	Stats &GetStats();
	/**
 	* @brief const getter for stats
 	*/
	const Stats &GetStats() const;

	/**
 	* @brief setter for rarity
 	*/
	void SetRarity(ItemRarity iitemRarity);
	/**
 	* @brief getter for rarity
 	*/
	ItemRarity GetRarity() const;

	/**
 	* @brief method for generating rarity
 	*/
	ItemRarity GenerateRarity();

};


#endif
