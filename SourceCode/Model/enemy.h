#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "item.h"
#include "creature.h"

enum EnemyType{

	Human,
	Insect,
	Animal,
	Undead,
	Demon,

};

/**
 * @brief Class that represent enemy in game
 */
class Enemy : public Creature {

	private:

		/**
 		 * @brief direction where enemy is heading
 		*/
		Direction direction;
		/**
 		 * @brief enemy type ()
 		*/
		EnemyType enemyType;
		/**
 		 * @brief item enemy holding 
 		*/	
		std::unique_ptr<Item> item{};
		/**
 		 * @brief exp enemy giving
 		*/
		int exp{};
		/**
 		 * @brief damage enemy dealing
 		*/
		int damage{10};

	public:

		/**
 		 * @brief default constructor
 		*/
		Enemy();
		/**
 		 * @brief constructor with type
 		*/
		explicit Enemy(EnemyType enemyType);

		/**
 		 * @brief getter for exp
 		*/
		int GetExp();
		/**
 		 * @brief setter for exp
 		*/
		void SetExp(int newExp);

		/**
 		 * @brief getter for damage
 		*/
		int GetDamage();
		/**
 		 * @brief setter for damage
 		*/
		void SetDamage(int dmg);

		/**
 		 * @brief getter for item
 		*/
		std::unique_ptr<Item> GetItem();
		/**
 		 * @brief setter for item
 		*/
		void SetItem(std::unique_ptr<Item> newItem);
		

		/**
 		 * @brief getter for damage
 		*/
		int DealDamage();

		/**
 		 * @brief setter for direction
 		*/
		void SetDirection(Direction idirection);
		/**
 		 * @brief getter for direction
 		*/
		Direction &GetDirection();

		/**
 		 * @brief getter for enemy type
 		*/
		EnemyType GetEnemyType();
		/**
 		 * @brief setter for enemy type
 		*/
		void SetEnemyType(EnemyType type);

		/**
 		 * @brief method that changes direction of enemy if it hits wall
 		*/
		void SwitchDirection(Direction &direction);


};

#endif
