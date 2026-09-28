#ifndef DUNGEON_H
#define DUNGEON_H

#include "level.h"
#include "character.h"
#include <vector>

/**
 * @brief class that represent dungeon in game
 */

class Dungeon{

	private:

		/**
 		 * @brief character instance in game
 		*/
		Character character{};
		/**
 		 * @brief std::vector of levels generated already
 		*/
		std::vector<Level> level;
		/**
 		 * @brief current level index
 		*/
		size_t index{0};
		/**
 		 * @brief amount of already generated levels
 		*/
		size_t maxIndex{0};

	public:

		/**
 		 * @brief method for going to next level
 		*/
		void GoToNextLevel(){

			index++;
			if (index > maxIndex){

				maxIndex = index;
				level.push_back(Level(index));

			}

			GetCharacter().SpawnOnLevel(GetLevel().GetValidCoordinate());

		}

		/**
 		 * @brief method for going to previous level
 		*/
		void GoToPreviousLevel(){

			if (index > 0){

				index--;

			}
			GetCharacter().SpawnOnLevel(GetLevel().GetValidCoordinate());

		}

		/**
 		 * @brief getter for index of current level
 		*/
		size_t GetIndex(){

			return index;

		}

		/**
 		 * @brief getter for current level
 		*/
		Level &GetLevel(){

			return level[index];

		}

		/**
 		 * @brief getter for character
 		*/
		Character &GetCharacter(){

			return character;

		}

		/**
 		 * @brief default contstructor
 		*/
		Dungeon(){

			level.push_back(Level(index));
			GetCharacter().SpawnOnLevel(GetLevel().GetValidCoordinate());
			/*for (int i = 0; i < 10; i++){

				level[i] = Level(i);

			}*/

		}

};


#endif
