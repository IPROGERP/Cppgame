#ifndef MOVEMENTSERVICE_H
#define MOVEMENTSERVICE_H

#include "iostream"
#include "../Model/creature.h"
#include "raylib.h"
#include "../Model/level.h"
#include "collisionservice.h"

void MoveCreature(Creature &creature, Level &level, Direction direction){

	Point originalCoordinate = creature.GetCoordinate();

	creature.Move(direction);

	if (!VoidCollisionCheck(creature, level)){

		creature.SetCoordinate(originalCoordinate);

	}

}

#endif
