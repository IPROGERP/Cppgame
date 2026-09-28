#ifndef POTION_H
#define POTION_H

#include "item.h"

/**
 * @brief class that reperesent item potion in game
 */
class Potion : public Item {

	private:

	public:

		/**
 		 * @brief default constructor 
 		*/
		Potion();

		/**
 		 * @brief override method for applying effect
 		*/
		void ApplyEffect(Character &character) override;
		/**
 		 * @brief override method for discarding effect
 		*/
		void DiscardEffect(Character &character) override;
		/**
 		 * @brief override method for cloning
 		*/
		std::unique_ptr<Item> Clone() const override;

};

#endif
