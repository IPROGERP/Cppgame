#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "raylib.h"
#include <iostream>
#include <utility>
#include "../View/view.h"
#include "../Model/dungeon.h"
#include "../Service/menuservice.h"

/**
 * @brief controller class which managing game flow, input handling and state transition
 * Controller acts as central coordinator between game Model(Dungeon) and view(View), and varius setvices
*/
class Controller{

	private:

		#define KeyEnteract KEY_E
		#define KeyOpenChest KEY_O
		#define KeyUseLadder KEY_G
		#define KeyNextLevel KEY_K
		#define KeyPreviousLevel KEY_J
		#define KeyDealDamage KEY_Y
		#define KeyUp KEY_W
		#define KeyDown KEY_S
		#define KeyLeft KEY_A
		#define KeyRight KEY_D
		#define KeyGenerateLevel KEY_R

		#define CollisionDamage 10
		/**
		 * @brief current game state
		 */
		State state = Menu;
		/**
		 * @brief service for menu management
		 */
		MenuService menuService{};	
		/**
		 * @brief view component
		 */
		View view{};
		/**
		 * @brief game model
		 */
		Dungeon dungeon{};
		
		
	public:

		/**
		 * @brief method that runs main loop, controls states and calls other method for game logic 
		 */
		bool RunGame();
		/**
		 * @brief method that controls user input in menu
		 */
		void ControlInput();
		/**
		 * @brief method for changing state of game
		 */
		void SetState(State state);
		/**
		 * @brief method that moves enemies in game
		 */
		void MoveEnemies(std::vector<Enemy> &enemies, Level &level);
		/**
		 * @brief method for handling game logic
		 */
		void HandleGame();
		/**
		 * @brief method for handling interaction(i know there is typo in enteraction, but i dont want to change it and who cares :))
		 */
		void HandleEnteraction();
		/**
		 * @brief method for handling damage in game
		 */
		void HandleDamage();
		/**
		 * @brief method for handling opening chests
		 */
		void HandleChests();
		/**
		 * @brief method for handling ladder interaction
		 */
		void HandleLadder();
		/**
		 * @brief method for handling user input during game
		 */
		void HandleInput(Character &character, Level &level);
		/**
		 * @brief method for updating game logic
		 */
		void UpdateGameLogic();
		/**
		 * @brief method for handling enemy movement
		 */
		void HandleEnemy();
		/**
		 * @brief method for drawing selected item for picking up
		 */
		void HandleDrawing();
		/**
		 * @brief method that handles saves in game
		 */
		void HandleSave();

};
#endif
