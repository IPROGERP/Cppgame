#include "../Model/enemy.h"
#include "../Model/item.h"
#include "../Model/level.h"
#include "collisionservice.h"

bool EnemyCollisionCheck(std::vector<Enemy> &enemies, Creature &creature){

	for (auto &enemy : enemies){

		if (CheckCollisionRecs(enemy.GetCollisionBox(), creature.GetCollisionBox())){

			return false;

		}

	}

	return true;

}

Item* EnteractItemCollisionCheck(const std::vector<std::unique_ptr<Item>> &items, Creature &creature){

    for (const auto &item : items){

        if (item && CheckCollisionRecs(item->GetCollisionBox(), creature.GetEnteractionBox())){

            return item.get();

        }

    }

    return nullptr;

}

bool VoidCollisionCheck(Creature &creature, Level &level){

	int x = int(creature.GetCoordinate().x) / 32;
	int y = int(creature.GetCoordinate().y) / 32;

	int rows = level.GetMap().GetRows();
	int columns = level.GetMap().GetColumns();


	for (int i = -1; i <= 1; i++){

		for (int j = -1; j <= 1; j++){

			if (x + i >= 0 && y + j >= 0 && x + i < rows && y + j < columns){
				
				if (CheckCollisionRecs(creature.GetCollisionBox(), level.GetMap()(x + i, y + j).GetCollisionBox()) &&  level.GetMap()(x + i, y + j).GetId() == VoidTexture){ return false; };
				//level.GetMap()(x + i, y + j).SetId(DefaultTexture);
			}

		}

	}
/*
	for (size_t i = 0; i < level.GetMap().size(); i++){

		
		if (CheckCollisionRecs(creature.GetCollisionBox(), level.GetMap()[i].GetCollisionBox()) && level.GetMap()[i].GetId() == VoidTexture){

			return false;

		}

	}

*/
	return true;

}
