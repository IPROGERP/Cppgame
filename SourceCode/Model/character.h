#ifndef CHARACTER_H
#define CHARACTER_H

#include "creature.h"
#include "inventory.h"

/**
 * @brief dirative class from creature that represent character aka player
 */
class Character : public Creature {

	private:

		/**
		 * @brief current exp of player
		*/
		int exp{};
		/**
		 * @brief exp to upgrade level
		*/
		int expToNextLevel = 100;
		/**
		 * @brief current level of character
		*/
		int level = 1;
		/**
		 * @brief player stats
		*/
		Stats statsCharacter{};
		/**
		 * @brief player inventory
		*/
		Inventory inventoryCharacter;

	public:
		/**
		 * @brief getter for current hp
		*/
		int GetCurrentHp() const { return currentHp; }
		/**
		 * @brief getter for max hp
		*/
    	int GetMaxHp() const { return maxHp; }
		/**
		 * @brief setter for hp
		*/
		void SetCurrentHp(int hp){

        currentHp = hp; 
        if (currentHp > maxHp) currentHp = maxHp;
        if (currentHp < 0) currentHp = 0;
		
    	}
		/**
		 * @brief setter for max hp
		*/
    	void SetMaxHp(int hp) { maxHp = hp; }
		/**
		 * @brief getter for stats
		*/
		Stats &GetStats();

		/**
		 * @brief default construcor
		*/
		Character();
		/**
		 * @brief getter for inventory
		*/
		Inventory &GetInventory();
		/**
		 * @brief getter for exp
		*/
		int GetExp() const { return exp; }
		/**
		 * @brief setter for exp
		 */
		void SetExp(int iexp) { exp = iexp; }
		/**
		 * @brief setter for exp for next level
		 */
		void SetExpToNextLevel(int iexp) {expToNextLevel = iexp; }
		/**
		 * @brief getter for current level
		*/
		int GetLevel() const { return level; }
		/**
		 * @brief getter for amount of exp needed to upgrade level
		*/
		int GetExpToNextLevel() const { return expToNextLevel; }
		/**
		 * @brief adder for exp
		*/
		void AddExp(int amount);
		/**
		 * @brief method that upgrade level of player
		*/
		void LevelUp();
		/**
		 * @brief method that checks if pllayer should be upgraded
		*/
		bool CheckLevelUp();

};

#endif
