#ifndef ARMOR_H
#define ARMOR_H

#include "item.h"

/**
 * @brief Class that represent armor item in game
 */
class Armor : public Item {

	private:

		/**
		 * @brief Type of armor defined in item header file (Head,Chest,Legs,Feet)
		 */
		ArmorType armorType;

	public:

		/**
		 * @brief default constructor
		 */
		Armor();
		/**
		 * @brief constructor with certain type
		 */
		explicit Armor(ArmorType iArmorType);

		/**
		 * @brief Armor type getter
		 */
		ArmorType GetArmorType() const;
		/**
		 * @brief damage reduction getter
		 */
		int GetDamageReduction();

		/**
		 * override method for applying effect
		 */
		void ApplyEffect(Character &character) override;
		/**
		 * override method for discarding effect
		 */
		void DiscardEffect(Character &character) override;
		/**
		 * override method for cloning
		 */
		std::unique_ptr<Item> Clone() const override;

};

#endif
