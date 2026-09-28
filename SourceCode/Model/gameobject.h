#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"
#include <string>

enum TextureID{

	DefaultTexture,
	FloorTexture,
	VoidTexture,
	CharacterTexture,
	EnemyTexture,
	WeaponTexture,
	PotionTexture,
	LockpickTexture,
	ArmorChestTexture,
	ArmorHeadTexture,
	ArmorFeetTexture,
	ArmorLegsTexture,
	EnemyHumanTexture,
	EnemyInsectTexture,
	EnemyDemonTexture,
	EnemyUndeadTexture,
	EnemyAnimalTexture,
	ChesterTexture,
	LadderTexture

};

/**
 * @brief struct for gameobject coordinate
 */
struct Point{

	float x{};
	float y{};

};

/**
 * @brief class for gameobject almost every class dirives from gameobject
 */
class GameObject{

	protected:

		/**
 		 * @brief texture id for drawing
 		*/
		TextureID id = DefaultTexture;	
		/**
 		 * @brief collision box
 		*/		
		Rectangle collisionBox{};
		/**
 		 * @brief interaction box (another typo)
 		*/
		Rectangle enteractionBox{};
		/**
 		 * @brief coordinate of gameobject
 		*/
		Point coordinate{};

	public:

		/**
 		 * @brief getter for id
 		*/
		TextureID &GetId(){

			return id;

		}

		/**
 		 * @brief const getter for id
 		*/
		const TextureID &GetId() const {

			return id;

		}

		/**
 		 * @brief setter for id
 		*/
		void SetId(TextureID iid){

			id = iid;

		}

		/**
 		 * @brief setter for collison box
 		*/
		void SetCollisionBox(float x, float y, float width, float height){

			collisionBox = Rectangle{coordinate.x, coordinate.y, width, height};

		}

		/**
 		 * @brief setter for interaction box
 		*/
		void SetEnteractionBox(float x, float y, float width, float height){

			enteractionBox = Rectangle{coordinate.x - width/4, coordinate.y - height/4, width, height};

		}

		/**
 		 * @brief setter for coordinate via x and y
 		*/
		void SetCoordinate(float x, float y){

			coordinate.x = x;
			coordinate.y = y;
			SetCollisionBox(x, y, 32, 32);
			SetEnteractionBox(x, y, 62, 64);

		}

		/**
 		 * @brief setter for coordinate via Point struct
 		*/
		void SetCoordinate(Point &point){

			coordinate.x = point.x;
			coordinate.y = point.y;
			SetCollisionBox(point.x, point.y, 32, 32);
			SetEnteractionBox(point.x, point.y, 62, 64);

		}

		/**
 		 * @brief getter for collision box
 		*/
		Rectangle &GetCollisionBox(){

			return collisionBox;
	
		}

		/**
 		 * @brief getter for interaction box
 		*/
		Rectangle &GetEnteractionBox(){

			return enteractionBox;
	
		}

		/**
 		 * @brief getter for coordinate
 		*/
		Point &GetCoordinate(){

			return coordinate;

		}
};

#endif
