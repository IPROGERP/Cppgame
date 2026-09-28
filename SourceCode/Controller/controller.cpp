#include "controller.h"
#include "raylib.h"
#include "../Service/movementservice.h"
#include <iostream>
#include "../Service/collisionservice.h"
#include "../Service/damageservice.h"
#include "../Service/saveservice.h"

void Controller::SetState(State state){

	this -> state = state;

}

void Controller::MoveEnemies(std::vector<Enemy> &enemies, Level &level){

	for (auto &enemy : enemies){
	
		Point originalPosition = enemy.GetCoordinate();

		enemy.Update();
		MoveCreature(enemy, level, enemy.GetDirection());
		
		if (originalPosition.x == enemy.GetCoordinate().x && originalPosition.y == enemy.GetCoordinate().y){

			enemy.SwitchDirection(enemy.GetDirection());

		}

	}

}


/*
void Controller::ControlCharacter(Character & character, Level &level){

	Direction direction;

	if (IsKeyDown(KEY_W)){

		direction = Up;
		MoveCreature(character, level, direction);

	}
	if(IsKeyDown(KEY_S)){

		direction = Down;	
		MoveCreature(character, level, direction);

	}
	if(IsKeyDown(KEY_A)){

		direction = Left;
		MoveCreature(character, level, direction);

	}
	if(IsKeyDown(KEY_D)){

		direction = Right;
		MoveCreature(character, level, direction);

	}

}
*/

/*
void Controller::ControlEnemyCollision(std::vector<Enemy> &enemies, Creature &creature){

	if (!EnemyCollisionCheck(enemies, creature)){

		creature.TakeDamage(10);

	}

}
*/
void Controller::HandleSave(){

	SaveManager saveManager;
	saveManager.SaveGame(dungeon.GetCharacter(), dungeon);

}

void Controller::HandleDamage(){

	if (!EnemyCollisionCheck(dungeon.GetLevel().GetEnemies(), dungeon.GetCharacter())){

		dungeon.GetCharacter().TakeDamage(CollisionDamage);

	}

	for (auto it = dungeon.GetLevel().GetEnemies().begin(); it != dungeon.GetLevel().GetEnemies().end();){

		if (!it -> Alive()){

			dungeon.GetCharacter().AddExp(it->GetExp());
			std::unique_ptr<Item> enemyItem = it->GetItem();

			if (enemyItem != nullptr){
				
				enemyItem -> SetCoordinate(it -> GetCoordinate().x, it -> GetCoordinate().y);
				dungeon.GetLevel().AddItem(std::move(enemyItem));

				if (dungeon.GetLevel().GetEnemies().size() == 1){

					dungeon.GetLevel().SpawnLadder();

				}

				it =  dungeon.GetLevel().GetEnemies().erase(it);

			}

		}else{

			it++;

		}
	}

}

void Controller::HandleChests(){

	auto& chestPtr = dungeon.GetLevel().GetChester();

	if (chestPtr){

		if (CheckCollisionRecs(chestPtr->GetEnteractionBox(), dungeon.GetCharacter().GetCollisionBox())){
			
			std::unique_ptr<Item> chestItem = chestPtr->OpenChest();
			
			if (chestItem && dungeon.GetCharacter().GetInventory().GetLockpicks().GetAmount() > 0){

				chestItem->SetCoordinate(chestPtr->GetCoordinate().x, chestPtr->GetCoordinate().y);
				dungeon.GetLevel().AddItem(std::move(chestItem));
				dungeon.GetLevel().RemoveChest();

			}else{

				dungeon.GetCharacter().GetInventory().GetLockpicks().DiscardEffect(dungeon.GetCharacter());

			}

		}

	}

}

void Controller::HandleEnteraction(){

	Item* selectedItem = EnteractItemCollisionCheck(dungeon.GetLevel().GetItems(), dungeon.GetCharacter());
			
	if (selectedItem){
		

		if (LockpickBundle* lockpickBundle = dynamic_cast<LockpickBundle*>(selectedItem)){

			dungeon.GetCharacter().GetInventory().GetLockpicks() += lockpickBundle->GetAmount();
			auto& items = dungeon.GetLevel().GetItems();
			for (auto it = items.begin(); it != items.end(); ++it){
				if (it->get() == selectedItem){
					items.erase(it);
					break;
				}
			}
			return;

		}	
		
		std::unique_ptr<Item> oldItem = dungeon.GetCharacter().GetInventory().SwapItems(selectedItem);

		if (oldItem){

			selectedItem->ApplyEffect(dungeon.GetCharacter());
			oldItem -> DiscardEffect(dungeon.GetCharacter());
			oldItem->SetCoordinate(selectedItem->GetCoordinate().x, selectedItem->GetCoordinate().y);
			dungeon.GetLevel().AddItem(std::move(oldItem));

		}
		
		auto& items = dungeon.GetLevel().GetItems();

		for (auto it = items.begin(); it != items.end(); ++it){

			if (it->get() == selectedItem){

				items.erase(it);
				break;

			}

		}
	
	}

}

void Controller::HandleLadder(){

	auto& ladderPtr = dungeon.GetLevel().GetLadder();
	if (ladderPtr){

		if (CheckCollisionRecs(ladderPtr->GetEnteractionBox(), dungeon.GetCharacter().GetCollisionBox())){
			
			dungeon.GoToNextLevel();
			
		}

	}

}

void Controller::HandleInput(Character &character, Level &level){

	if (IsKeyPressed(KeyGenerateLevel)) { dungeon.GetLevel().GenerateLevel(); }
	if (IsKeyPressed(KeyNextLevel)) { dungeon.GoToNextLevel(); }
	if (IsKeyPressed(KeyPreviousLevel)) { dungeon.GoToPreviousLevel(); }

	if (IsKeyPressed(KeyEnteract)) { HandleEnteraction(); }
	if (IsKeyPressed(KeyOpenChest)) { HandleChests(); }
	if (IsKeyPressed(KeyUseLadder)) { HandleLadder(); }
	if (IsKeyPressed(KeyDealDamage)) { CalculateDamage(dungeon.GetLevel().GetEnemies(), dungeon.GetCharacter()); }
	
	if (IsKeyDown(KeyUp)) { MoveCreature(character, level, Up); }
	if (IsKeyDown(KeyDown)) { MoveCreature(character, level, Down); }
	if (IsKeyDown(KeyRight)) { MoveCreature(character, level, Right); }
	if (IsKeyDown(KeyLeft)) { MoveCreature(character, level, Left); }

	if (IsKeyPressed(KEY_F1)) { HandleSave(); }

}

void Controller::UpdateGameLogic(){

	dungeon.GetCharacter().Update();
	HandleDamage();
	if (!dungeon.GetCharacter().Alive()){

		state = Menu;
		dungeon.GetCharacter().Revive();

	}

}

void Controller::HandleEnemy(){

	MoveEnemies(dungeon.GetLevel().GetEnemies(), dungeon.GetLevel());

}

void Controller::HandleDrawing(){

	Item *selectedItem = EnteractItemCollisionCheck(dungeon.GetLevel().GetItems(), dungeon.GetCharacter());
	view.DrawGame(dungeon, selectedItem);

}

void Controller::HandleGame(){

	HandleInput(dungeon.GetCharacter(), dungeon.GetLevel());
	UpdateGameLogic();
	HandleEnemy();
	HandleDrawing();

}

bool Controller::RunGame(){

	if (WindowShouldClose() || state == Exit){

		state = Exit;
		return false;

	}else if(state == Menu){

		view.DrawMenu(menuService);

	}else if(state == Options){

		view.DrawOptions();

	}else if(state == Continue){

		view.DrawBlankBackground();
		state = Game;

	}else if(state == LoadGame){

		SaveManager saveManager;
		saveManager.LoadGame(dungeon.GetCharacter(), dungeon);
		state = Game;

	}else if(state == Game){
		
		HandleGame();

	}else if(state == NewGame){

		HandleGame();

	}else{

		view.DrawBlankBackground();
		
	}

	ControlInput();
	return true;

}

void Controller::ControlInput(){

	if (IsKeyPressed(KEY_W) && state == Menu){

		menuService--;

	}else if(IsKeyPressed(KEY_S) && state == Menu){

		menuService++;

	}else if(IsKeyPressed(KEY_ENTER) && state == Menu){

		SetState(menuService.GetState());

	}else if(state != Menu && IsKeyPressed(KEY_I)){

		state = Menu;

	}

}
