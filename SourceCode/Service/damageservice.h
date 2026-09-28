#ifndef DAMAGESERVICE_H
#define DAMAGESERVICE_H

#include "../Model/gameobject.h"

void CalculateDamage(std::vector<Enemy> &enemies, Creature &creature){

	for (auto &enemy : enemies){

		if (CheckCollisionRecs(enemy.GetCollisionBox(), creature.GetEnteractionBox())){

			enemy.TakeDamage(creature.GetDamage());

		}

	}

}

#endif
