#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include "raylib.h"
#include "gameobject.h"

enum Direction{

	Up,
	Down,
	Right,
	Left

};

/**
 * @brief class that represent creature in game
 */
class Creature : public GameObject {
		
	protected:

		/**
 		 * @brief max creature hp
 		*/
		int maxHp{100};
		/**
 		 * @brief current creature hp
 		*/
		int currentHp{100};
		/**
 		 * @brief creature speed
 		*/
		int speed{2};
		/**
 		 * @brief creature base damage
 		*/
		int damage{10};
		/**
 		 * @brief bool variable if creature alive or not
 		*/
		bool alive = true;
		/**
 		 * @brief bool variable if creature invincible
 		*/
		bool invinsable{false};
		/**
 		 * @brief variable for current invincible frame
 		*/
		int currentFrame{0};
		/**
 		 * @brief amount if invincible frames
 		*/
		int invincibleFrame{30};

	public:

		/**
 		 * @brief setter for invincibility frames
 		*/
		void SetInvincibleFrame(int amount){

			invincibleFrame = amount;

		}

		/**
 		 * @brief getter if creature alive
 		*/
		bool Alive(){

			return alive;

		}

		/**
 		 * @brief getter for max hp
 		*/
		int GetMaxHp(){

			return maxHp;

		}

		/**
 		 * @brief getter for current hp
 		*/
		int GetCurrentHp(){
			
			return currentHp;

		}

		/**
 		 * @brief method that kill creature
 		*/
		void Die(){

			alive = false;

		}

		/**
 		 * @brief method that revives creature
 		*/
		void Revive(){
		
			alive = true;
			currentHp = maxHp;

		}

		/**
 		 * @brief method for taking damage
 		*/
		void TakeDamage(int damage){

			if (invinsable == true){
				
				return;

			}
			invinsable = true;
			if (currentHp >= damage){

				currentHp -= damage;

			}else{

				currentHp = 0;

			}
			if (currentHp <= 0){

				Die();

			}

		}

		/**
 		 * @brief getter for damage
 		*/
		int GetDamage(){

			return damage;

		}

		/**
 		 * @brief setter for damage
 		*/
		void SetDamage(int idamage){

			damage = idamage;

		}

		/**
 		 * @brief method for updating invincibility frames
 		*/
		void Update(){

			if (invinsable == true){
				currentFrame++;

				if (currentFrame > invincibleFrame){

					invinsable = false;
					currentFrame = 0;

				}

			}

		}

		/**
 		 * @brief method that moves creature in certain direction
 		*/
		void Move(Direction direction){

			switch (direction){

				case Up:

					coordinate.y -= speed;
					break;

				case Down:

					coordinate.y += speed;
					break;
		
				case Right:

					coordinate.x += speed;
					break;

				case Left:

					coordinate.x -= speed;
					break;
				
			}

			SetCoordinate(coordinate.x, coordinate.y);

		}

		/**
 		 * @brief method that spawns creature on level
 		*/
		void SpawnOnLevel(Point point){
			
			SetCoordinate(point.x * 32, point.y * 32);


		}

};
#endif
