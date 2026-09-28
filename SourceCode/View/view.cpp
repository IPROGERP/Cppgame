#include "view.h"
#include "../Model/types.h"
#include "../Model/item.h"
#include "raylib.h"
#include <string>
#include <utility>
#include <vector>
#include "../Service/collisionservice.h"

Color GetRarityColor(ItemRarity rarity){

	switch(rarity){

		case Common:
			return GRAY;

		case Rare:
			return ORANGE;
	
		case Epic:
			return VIOLET;

		case Legendary:
			return WHITE;

		case Champion:
			return GOLD;

	}

}
//for time 
void View::DrawBlankBackground(){

	BeginDrawing();
	ClearBackground(BLACK);
	EndDrawing();

}

void View::DrawItem(float x, float y, Item &item){

	Rectangle itemLine{x, y, 32.0f, 32.0f};
	DrawRectangleLinesEx(itemLine,3,GetRarityColor(item.GetRarity()));

}

void View::DrawGameObject(float x, float y, GameObject &gameobject){

	DrawTextureEx(textures[gameobject.GetId()], {x, y}, 0.0f, rectWidth / textures[gameobject.GetId()].width, WHITE);

}

void View::DrawMenu(MenuService &menuservice){

	BeginDrawing();
	ClearBackground(BLACK);

	int fontSize = 40;
	int space = 20;

	DrawText("Rigby journey", width/2 - MeasureText("Rigby journey", 100)/2, height/4, 100, RED);

	int optionLength = MeasureText(menuservice.ConvertStateToChar(menuservice.states[menuservice.currentState]), fontSize);
	DrawRectangle(0, height/2 + menuservice.currentState * (fontSize + space), width/2 - optionLength/2 - 30, fontSize, MAROON);

	DrawRectangle(width/2 + optionLength/2 + 30, height/2 + menuservice.currentState * (fontSize + space), width/2 - optionLength/2 - 30, fontSize, MAROON);
	for (int i = 0; i < 5; i++){

		const char *line = menuservice.ConvertStateToChar(menuservice.states[i]);
		DrawText(line, width/2 - MeasureText(line, fontSize)/2, height/2 + i * (fontSize + space), fontSize, RED);

	}

	EndDrawing();

}

void View::DrawNewGame(){

	BeginDrawing();
	DrawTextureEx(textures[CharacterTexture], {0,0}, 0.0f, 1.0f, WHITE);
	ClearBackground(BLACK);
	DrawText("New Game", int(this -> width/2), int(this -> height/2), 20, RED);
	EndDrawing();

}

void View::DrawLevelNew(Level &level, float offsetx, float offsety){

	float x = 0;
	float y = 0;

	for (auto &value : level.GetMap()){

		x = value.GetCoordinate().x + offsetx;
		y = value.GetCoordinate().y + offsety;

		//DrawTextureEx(textures[value.GetId()], {x, y}, 0.0f, rectWidth / textures[value.GetId()].width, WHITE);
		DrawGameObject(x,y,value);
		DrawRectangleLines(x,y,32,32,WHITE);

	}		

}

void View::DrawLevelDebug(Level &level){

	float x = 0;
	float y = 0;

	for (size_t i = 0; i < level.GetMap().GetRows(); i++){

		for (size_t j = 0; j < level.GetMap().GetColumns(); j++){

			x = i * rectWidth;
			y = j * rectHeight;
			//DrawTextureEx(textures[level.GetMap()(i,j).GetId()], {x, y},0.0f, rectWidth / textures[level.GetMap()(i,j).GetId()].width, WHITE);
			if (level.GetMap()(i,j).GetId() == VoidTexture){

				DrawRectangleRec(level.GetMap()(i,j).GetCollisionBox(),RED);
			
			}

		}

	}

}

void View::DrawOptions(){

	BeginDrawing();
	ClearBackground(BLACK);

	DrawText("movement - w,a,s,d", width/2 - MeasureText("movement - w,a,s,d", 32)/2, height/4, 32, RED);
	DrawText("enteract with ladder - g", width/2 - MeasureText("go to next level - g", 32)/2, height/4 + 32, 32, RED);
	DrawText("open chest - o", width/2 - MeasureText("open chest - o", 32)/2, height/4 + 32*2, 32, RED);
	DrawText("deal damage - y", width/2 - MeasureText("deal damage - y", 32)/2, height/4 + 32*3, 32, RED);
	DrawText("go to next level - k", width/2 - MeasureText("go to next level - k", 32)/2, height/4 + 32*4, 32, RED);
	DrawText("go to previous level - j", width/2 - MeasureText("go to previous level - j", 32)/2, height/4 + 32*5, 32, RED);
	
	EndDrawing();

}

void View::DrawSelectedOption(Item *item, float offsetx, float offsety, Character &character){

	if (item != nullptr){
		DrawRectangle(item -> GetCoordinate().x + offsetx + 16 - 5, item -> GetCoordinate().y + offsety - 10, 10,  10, RED);
	}

}

void View::DrawObstacle(std::unique_ptr<Chester> &chester, float offsetx, float offsety){

	if (chester){

        float x = chester->GetCoordinate().x + offsetx;
        float y = chester->GetCoordinate().y + offsety;
        DrawGameObject(x, y, *chester);

    }

}

void View::DrawLadder(std::unique_ptr<GameObject> &ladder, float offsetx, float offsety){

	if (ladder){

        float x = ladder->GetCoordinate().x + offsetx;
        float y = ladder->GetCoordinate().y + offsety;
        DrawGameObject(x, y, *ladder);
		
    }

}

void View::DrawGame(Dungeon &dungeon, Item *selectedItem){

	float offsetx = width / 2 - rectWidth * dungeon.GetLevel().GetMap().GetColumns() / 2;
	float offsety = height / 2 - rectHeight * dungeon.GetLevel().GetMap().GetRows() / 2;

	BeginDrawing();
	ClearBackground(BLACK);
	DrawText(std::to_string(dungeon.GetIndex()).c_str(), 0, 0, 40, RED);
	DrawLevelNew(dungeon.GetLevel(), offsetx, offsety);
	//DrawLevelDebug(dungeon.GetLevel()); //for now turned off
	DrawCharacter(dungeon.GetCharacter(), offsetx, offsety);
	DrawEnemies(dungeon.GetLevel().GetEnemies(), offsetx, offsety);
	DrawItems(dungeon.GetLevel().GetItems(), offsetx, offsety);
	DrawObstacle(dungeon.GetLevel().GetChester(), offsetx, offsety);
	DrawLadder(dungeon.GetLevel().GetLadder(),offsetx, offsety);
	DrawSelectedOption(selectedItem, offsetx, offsety, dungeon.GetCharacter());
	EndDrawing();

}

void View::DrawEnemies(std::vector<Enemy> &enemies, float offsetx, float offsety){

	int healthBarWidth = 32;
	int healthBarHeight = 5;

	for (auto &enemy : enemies){
	
		float procentHealth = float(enemy.GetCurrentHp()) / float(enemy.GetMaxHp());
		float x = enemy.GetCoordinate().x;
		float y = enemy.GetCoordinate().y;
		DrawTextureEx(textures[enemy.GetId()],{x + offsetx, y + offsety}, 0.0f, 32.0f / textures[enemy.GetId()].width, WHITE);
		DrawRectangle(x + offsetx, y - healthBarHeight + offsety, healthBarWidth, healthBarHeight, RED);
		DrawRectangle(x + offsetx, y - healthBarHeight + offsety, healthBarWidth * procentHealth, healthBarHeight, GREEN);

	}

}

void View::DrawItems(std::vector<std::unique_ptr<Item>> &items, float offsetx, float offsety){

	for (auto &item : items){

		float x = item -> GetCoordinate().x;
		float y = item -> GetCoordinate().y;
		
		DrawTextureEx(textures[item -> GetId()],{x + offsetx, y + offsety}, 0.0f, 32.0f / textures[item -> GetId()].width, WHITE);
		Rectangle itemLine{x + offsetx, y + offsety, 32.0f, 32.0f};
		DrawRectangleLinesEx(itemLine,3,GetRarityColor(item -> GetRarity()));

	}

}


View::View(): height(800), width(1440){

	InitWindow(width, height, "DungeonLooter");
	LoadTextures();
	SetTargetFPS(60);

}

View::~View(){

	UnloadTextures();
	CloseWindow();

}

void View::SetHeight(int height){

	this -> height = height;

}

void View::SetWidth(int width){

	this -> width = width;

}

void View::DrawTextInt(int input, float x, float y, std::string text){

	std::string amount = std::to_string(input);
	const char *line = amount.c_str();
	const char *textC = text.c_str();
	DrawText(line, MeasureText(textC, 30), y, 30, RED);

}
void View::DrawCharacterStats(float offsetx, float offsety, Character &character){

	Stats stats = character.GetStats();
	DrawText("Agility : ", 0, 32*7, 30, RED);
	DrawTextInt(stats.agility, offsetx, offsety, "Agility : ");

	DrawText("Strength : ", 0, 32*8, 30, RED);
	DrawTextInt(stats.strength, offsetx, offsety + 32, "Strength : ");

	DrawText("Endurance : ", 0, 32*9, 30, RED);
	DrawTextInt(stats.endurance, offsetx, offsety + 32 * 2, "Endurance : ");

	DrawText("Damage : ", 0, 32*10, 30, RED);
	DrawTextInt(character.GetDamage(), offsetx, offsety + 32 * 3, "Damage : ");

	DrawText(("Level: " + std::to_string(character.GetLevel())).c_str(), 0, 32*11, 30, YELLOW);

	DrawText(("Exp: " + std::to_string(character.GetExp()) + "/" + std::to_string(character.GetExpToNextLevel())).c_str(), 0, 32*12, 30, YELLOW);

}


void View::DrawCharacterUI(float offsetx, float offsety, Character &character){

	DrawGameObject(0, 32, character.GetInventory().helmet);
	DrawItem(0,32,character.GetInventory().helmet);

	DrawGameObject(0, 32*2, character.GetInventory().chest);
	DrawItem(0,32*2,character.GetInventory().chest);

	DrawGameObject(0, 32*3, character.GetInventory().legs);
	DrawItem(0, 32*3, character.GetInventory().legs);

	DrawGameObject(0, 32*4, character.GetInventory().feet);
	DrawItem(0, 32*4, character.GetInventory().feet);

	DrawGameObject(0, 32*5, character.GetInventory().weapon);
	DrawItem(0, 32*5, character.GetInventory().weapon);

	DrawText("Lockpicks : ", 0, 32*6, 30, RED);
	std::string amount = std::to_string(character.GetInventory().lockpicks.GetAmount());
	const char *line = amount.c_str();
	DrawText(line, MeasureText("Lockpicks : ", 30), 32*6, 30, RED);
	DrawCharacterStats(0 , 32 * 7, character);

}

void View::DrawCharacter(Character &character, float offsetx, float offsety){

	float x = character.GetCoordinate().x;
	float y = character.GetCoordinate().y;
	int healthBarWidth = 300;
	int healthBarHeight = 30;
	float procentHealth = float(character.GetCurrentHp()) / float(character.GetMaxHp());

	//DrawRectangleRec(character.GetEnteractionBox(), GREEN);
	DrawText(("Hp: " + std::to_string(character.GetCurrentHp()) + "/" + std::to_string(character.GetMaxHp())).c_str(), 0, 32*13, 30, RED);
	DrawTextureEx(textures[character.GetId()],{x + offsetx, y + offsety}, 0.0f, 32.0f / textures[character.GetId()].width, WHITE);
	DrawRectangle(width - healthBarWidth, 0, healthBarWidth, healthBarHeight, RED);
	DrawRectangle(width - healthBarWidth, 0, healthBarWidth * procentHealth, healthBarHeight, GREEN);
	
	DrawCharacterUI(offsetx, offsety, character);

	//DrawTextureEx(textures[character.GetId()],{x, y}, 0.0f, 32.0f / textures[character.GetId()].width, WHITE);

}

bool View::LoadTextures(){

	Texture2D defaultTexture = LoadTexture("../SourceTexture/defaultTexture.png");
	Texture2D floorTexture = LoadTexture("../SourceTexture/floorTexture.png");
	Texture2D characterTexture = LoadTexture("../SourceTexture/characterTexture.png");
	Texture2D voidTexture = LoadTexture("../SourceTexture/voidTexture.png");
	Texture2D enemyTexture = LoadTexture("../SourceTexture/enemyTexture.png");
	Texture2D weaponTexture = LoadTexture("../SourceTexture/weaponTexture.png");
	Texture2D lockpickTexture = LoadTexture("../SourceTexture/lockpickTexture.png");
	Texture2D potionTexture = LoadTexture("../SourceTexture/potionTexture.png");
	Texture2D armorChestTexture = LoadTexture("../SourceTexture/chestTexture.png");
	Texture2D armorLegsTexture = LoadTexture("../SourceTexture/legsTexture.png");
	Texture2D armorHeadTexture = LoadTexture("../SourceTexture/headTexture.png");
	Texture2D armorFeetTexture = LoadTexture("../SourceTexture/feetTexture.png");

	Texture2D enemyHumanTexture = LoadTexture("../SourceTexture/enemyTexture.png");
	Texture2D enemyInsectTexture = LoadTexture("../SourceTexture/insectTexture.png");
	Texture2D enemyDemonTexture = LoadTexture("../SourceTexture/demonTexture.png");
	Texture2D enemyUndeadTexture = LoadTexture("../SourceTexture/undeadTexture.png");
	Texture2D enemyAnimalTexture = LoadTexture("../SourceTexture/animalTexture.png");

	Texture2D chesterTexture = LoadTexture("../SourceTexture/chesterTexture.png");
	Texture2D ladderTexture = LoadTexture("../SourceTexture/ladderTexture.png");
	
	textures[DefaultTexture] = defaultTexture;
	textures[FloorTexture] = floorTexture;
	textures[CharacterTexture] = characterTexture;
	textures[VoidTexture] = voidTexture;
	textures[EnemyTexture] = enemyTexture;

	textures[WeaponTexture] = weaponTexture;
	textures[PotionTexture] = potionTexture;
	textures[LockpickTexture] = lockpickTexture;
	textures[ArmorChestTexture] = armorChestTexture;
	textures[ArmorLegsTexture] = armorLegsTexture;
	textures[ArmorHeadTexture] = armorHeadTexture;
	textures[ArmorFeetTexture] = armorFeetTexture;

	textures[EnemyHumanTexture] = enemyHumanTexture;
	textures[EnemyInsectTexture] = enemyInsectTexture;
	textures[EnemyDemonTexture] = enemyDemonTexture;
	textures[EnemyAnimalTexture] = enemyAnimalTexture ;
	textures[EnemyUndeadTexture] = enemyUndeadTexture;

	textures[ChesterTexture] = chesterTexture;
	textures[LadderTexture] = ladderTexture;

	return true;

}	

void View::UnloadTextures(){

	for (auto &pair : textures){

		UnloadTexture(pair.second);

	}
	textures.clear();

}		
