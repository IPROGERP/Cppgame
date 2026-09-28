#include "enemy.h"
#include "../Service/itemservice.h"
#include "types.h"

void Enemy::SwitchDirection(Direction &direction){

	direction = Direction(rand() % 4);
	
}

Enemy::Enemy(EnemyType enemyType) : enemyType(enemyType), direction(Direction::Down), exp(0), damage(10){
	SetId(EnemyTexture);
	switch(enemyType){
		case Human:  exp = 10; break;
		case Insect: exp = 15; break;
		case Animal: exp = 20; break;
		case Undead: exp = 25; break;
		case Demon:  exp = 30; break;
	}
	SetInvincibleFrame(0);
	int direction = rand()%4;
	item = ItemFactory::CreateItemForEnemy();
    if (item == nullptr){

        std::cout << "No Item\n";

    }

	SetDirection(Direction(direction));
	
}

int Enemy::GetExp(){

    return exp;

}

void Enemy::SetExp(int newExp){

    exp = newExp;

}

int Enemy::GetDamage(){

    return damage;

}

void Enemy::SetDamage(int dmg){

    damage = dmg;

}

std::unique_ptr<Item> Enemy::GetItem(){

    return std::move(item); 

}

EnemyType Enemy::GetEnemyType(){

    return enemyType;

}

void Enemy::SetEnemyType(EnemyType type){

    enemyType = type;

}

int Enemy::DealDamage(){

    return this->damage;

}

void Enemy::SetItem(std::unique_ptr<Item> newItem){

    item = std::move(newItem); 

}

Direction &Enemy::GetDirection(){

    return direction;

}

Enemy::Enemy(){

	EnemyType enemytype = EnemyType(rand()%5);

	switch(enemytype){
    case Human:  exp = 10; break;
    case Insect: exp = 15; break;
    case Animal: exp = 20; break;
    case Undead: exp = 25; break;
    case Demon:  exp = 30; break;
	}

	SetInvincibleFrame(0);
	int direction = rand()%4;
    item = ItemFactory::CreateItemForEnemy();

    if (item == nullptr){

        std::cout << "No Item\n";

    }

	SetDirection(Direction(direction));
	SetEnemyType(enemytype);

	switch (enemytype){

		case Human :

			SetId(EnemyTexture);
			break;

		case Insect :

			SetId(EnemyInsectTexture);
			break;

		case Animal:

			SetId(EnemyAnimalTexture);
			break;

		case Undead:

			SetId(EnemyUndeadTexture);
			break;

		case Demon:

			SetId(EnemyDemonTexture);
			break;

		}
}

void Enemy::SetDirection(Direction idirection){

    direction = idirection;
	
}
