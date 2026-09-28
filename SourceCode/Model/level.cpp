#include <random>

#include "iostream"

#include "level.h"
#include "types.h"
#include "matrix.h"
#include "item.h"
#include "enemy.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include "lockpickbundle.h"
#include "../Service/itemservice.h"

void Level::GenerateEnemies(size_t amount){

	for (int i = 0; i < amount; i++){

		Enemy enemy{};
		AddEnemy(std::move(enemy));

	}

}

void Level::AddEnemy(Enemy enemy){

	Point position = GetValidCoordinate();
	position.x *= 32.0f;
	position.y *= 32.0f;
	enemy.SetCoordinate(position);
	enemies.push_back(std::move(enemy));

}

void Level::GenerateItems(size_t amount){

	for (int i = 0; i < amount; i++){

		std::unique_ptr<Item> item{};
		AddItem(std::move(item));

	}

}

void Level::AddItem(std::unique_ptr<Item> item){

	if (item){

		Point position = item -> GetCoordinate();

		if (position.x == 0 && position.y == 0){

			Point position2 = GetValidCoordinate();
			position2.x *= 32.0f;
			position2.y *= 32.0f;
			item -> SetCoordinate(position2);

		}

	items.push_back(std::move(item));

	}

}

MatrixType &Level::GetMap(){

	return map;

}

std::unique_ptr<Chester> &Level::GetChester(){

    return chest;

}

const std::unique_ptr<Chester> &Level::GetChester() const {

    return chest;
	
}


const MatrixType &Level::GetMap() const {

	return map;

}

std::vector<std::unique_ptr<Item>> &Level::GetItems(){

	return items;

}

const std::vector<std::unique_ptr<Item>> &Level::GetItems() const {

	return items;

}

Level::Level(){

	size_t tileAmount = 5;
	map = MyMatrix::Matrix<Tile>{tileAmount, tileAmount, Void};
	this -> GenerateLevel();
	ladder = std::make_unique<GameObject>();
	ladder -> SetCoordinate(-1000,-1000);
	
}

void Level::AddChest(std::unique_ptr<Chester> ichest){

	Point position2 = GetValidCoordinate();
	position2.x *= 32.0f;
	position2.y *= 32.0f;
	ichest -> SetCoordinate(position2);

	chest = std::move(ichest);

}

void Level::RemoveChest(){

    chest.reset();

}

Level::Level(size_t difficulty){

	size_t tileAmount = difficulty * 2 + 11;
	if (tileAmount > 23){

		tileAmount = 23;

	}
	map = MyMatrix::Matrix<Tile>{tileAmount, tileAmount, Void};
	this -> GenerateLevel();
	std::unique_ptr<Item> item;

	chest = std::make_unique<Chester>();
	item = ItemFactory::CreateItemForEnemy();
	chest -> SetItem(std::move(item));

	AddChest(std::move(chest));
	GenerateEnemies(5);
	ladder = std::make_unique<GameObject>();
	ladder -> SetCoordinate(-1000,-1000);

}

std::vector<Enemy> &Level::GetEnemies(){

	return enemies;

}

const std::vector<Enemy> &Level::GetEnemies() const {

	return enemies;

}

void Level::GenerateLevel(){
	
    static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> rand_dist(0, RAND_MAX);

	size_t chance{};
	size_t allowPercent = 50;

	size_t x = map.GetRows() / 2;
	size_t y = map.GetColumns() / 2;
	size_t maxr = std::max(map.GetRows(), map.GetColumns());
	size_t r = maxr / 2.5 + 1;

	size_t offset{};
	size_t nx{};
	size_t ny{};

	for (size_t i = 0; i < map.GetRows(); i++){

		offset = rand_dist(gen) % r;
		chance = rand_dist(gen) % 100;

		for (size_t j = 0; j < map.GetColumns(); j++){

			nx = x - i;
			ny = y - j;

			map(i,j).SetId(VoidTexture);

			if (chance > allowPercent){

				ny += 2;

			}

			if (nx * nx + ny * ny <= r * r && i != map.GetColumns()-1 && i != 0 && j != map.GetRows()-1 && j != 0){

				map(i,j).SetId(FloorTexture);

			}

			if (chance > allowPercent){

				ny -= 2;

			}	
			
			map(i,j).SetCoordinate(i * 32, j * 32);

		}

	}

}

Point Level::GetValidCoordinate(){

	float x = std::rand() % this -> GetMap().GetColumns();
	float y = std::rand() % this -> GetMap().GetRows();

	while (this -> GetMap()(x,y).GetId() != FloorTexture){

		x = std::rand() % this -> GetMap().GetColumns();
		y = std::rand() % this -> GetMap().GetRows();

	}

	Point point{x,y};
	
	return point;

}

void Level::SpawnLadder(){

	ladder -> SetId(LadderTexture);

	Point point = this -> GetValidCoordinate();
	point.x *= 32.0f;
	point.y *= 32.0f;
	ladder -> SetCoordinate(point);

}

std::unique_ptr<GameObject> &Level::GetLadder(){

	return ladder;

}