#ifndef LOCKPICKBUNDLE_H
#define LOCKPICKBUNDLE_H

#include "item.h"

/**
 * @brief
 */

class LockpickBundle : public Item {

	private:

		/**
		 * @brief amount of lockpicks in bundle
		 */
		int lockpickAmount{};

	public:

		/**
		 * @brief default constructor
		 */
		LockpickBundle();

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
		 * @brief getter for amount of lockpicks
		 */
		int GetAmount();
		/**
		 * @brief setter for amount of lockpicks
		 */
		void SetAmount(int amount);

		int GetChance();
		
		/**
		 * @brief override operator for operator -=
		 */
		LockpickBundle& operator-=(int amount);
		/**
		 * @brief override operator for operator +=
		 */
		LockpickBundle& operator+=(int amount);

};

#endif
