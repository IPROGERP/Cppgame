#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "types.h"
#include "matrix.h"
#include "item.h"
#include "enemy.h"
#include "memory"
#include "chester.h"
#include "tile.h"

/**
 * @brief class that represent level 
 */

class Level{

	private:
		/**
		 * @brief vector of enemies on level
		 */
		std::vector<Enemy> enemies;
		/**
		 * @brief vector of unique_ptr Items on level
		 */
		std::vector<std::unique_ptr<Item>> items; 
		/**
		 * @brief unique_ptr chest on level
		 */
		std::unique_ptr<Chester> chest;
		/**
		 * @brief unique_ptr ladder to the next level
		 */
		std::unique_ptr<GameObject> ladder;
		/**
		 * @brief template class for map 
		 */
		MatrixType map{};

	public:

		/**
		 * @brief default constructor 
		 */
		Level();
		/**
		 * @brief constructor with size
		 */
		explicit Level(size_t difficulty);

		/**
		 * @brief enemies getter
		 */
		std::vector<Enemy> &GetEnemies();
		/**
		 * @brief enemies const getter
		 */
		const std::vector<Enemy> &GetEnemies() const;

		/**
		 * @brief chest getter
		 */
		std::unique_ptr<Chester> &GetChester();
		/**
		 * @brief chest const getter
		 */
		const std::unique_ptr<Chester> &GetChester() const;

		/**
		 * @brief items getter
		 */
		std::vector<std::unique_ptr<Item>> &GetItems();
		/**
		 * @brief item const getter
		 */
		const std::vector<std::unique_ptr<Item>> &GetItems() const;

		/**
		 * @brief map getter 
		 */
		MatrixType &GetMap();
		/**
		 * @brief map const getter
		 */	
		const MatrixType &GetMap() const;

		/**
		 * @brief method that generates level 
		 */
		void GenerateLevel();
		/**
		 * @brief method that return struct Point() with valid coordinate for placement
		 */
		Point GetValidCoordinate();
		/**
		 * @brief method that adds one item to level
		 */
		void AddItem(std::unique_ptr<Item> item);
		/**
		 * @brief method that adds amount items to level
		 */
		void GenerateItems(size_t amount);
 			
		/**
		 * @brief method that adds one enemy to level 
		 */
		void AddEnemy(Enemy enemy);
		/**
		 * @brief method that adds amount enemies to level
		 */
		void GenerateEnemies(size_t amount);

		/**
		 * @brief method that adds chest to level
		 */
		void AddChest(std::unique_ptr<Chester> ichest);
		/**
		 * @brief method that removes chest from level
		 */
		void RemoveChest();

		/**
		 * @brief method that spawns ladder on level 
		 */
		void SpawnLadder();
		/**
		 * @brief ladder getter
		 */
		std::unique_ptr<GameObject> &GetLadder();

};

#endif
