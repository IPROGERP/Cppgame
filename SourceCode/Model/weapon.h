#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

/**
 * @brief class that represent item weapon in game
 */
class Weapon : public Item {

	private:
		/**
 		 * @brief weapon modification
 		*/
		WeaponModification weaponModification = None;
		/**
 		 * @brief base damage for weapon
 		*/
		int damage{10};

	public:
		/**
 		 * @brief default constructor
 		*/
		Weapon();
		/**
 		 * @brief override method for applying effect
 		*/
		void ApplyEffect(Character &character) override;
		/**
 		 * @brief override method for discarding effect
 		*/
		void DiscardEffect(Character &character) override;
		/**
 		 * @brief override method for cloning item
 		*/
		std::unique_ptr<Item> Clone() const override;

		/**
 		 * @brief getter for weapon modification
 		*/
		WeaponModification GetModification();
		/**
 		 * @brief setter for weapon modification
 		*/
		void SetModification(WeaponModification modification){weaponModification = modification;};
		/**
 		 * @brief getter for damage
 		*/
		int GetDamage();

};

#endif
