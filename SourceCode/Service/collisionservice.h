#ifndef COLLISIONSERVICE_H
#define COLLISIONSERVICE_H

bool EnemyCollisionCheck(std::vector<Enemy> &enemies, Creature &creature);

Item *EnteractItemCollisionCheck(const std::vector<std::unique_ptr<Item>> &items, Creature &creature);

bool VoidCollisionCheck(Creature &creature, Level &level);

#endif
