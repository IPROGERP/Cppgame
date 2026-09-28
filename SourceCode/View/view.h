#ifndef VIEW_H
#define VIEW_H

#include <unordered_map>
#include <vector>
#include "../Service/menuservice.h"
#include "../Model/dungeon.h"
#include "../Model/enemy.h"

/**
 * @brief view class which managing game drawing
*/

class View{

	private:	

		using TextureMap = std::unordered_map<TextureID, Texture2D>;

		/**
		 * @brief height of screen		
		*/
		int height = 900;
		/**
		 * @brief width of screen		
		*/
		int width = 1440;
		/**
		 * @brief width of one block of map(in pixels)
		*/
		float rectWidth = 32;
		/**
		 * @brief height of one block of map(in pixels)		
		*/
		float rectHeight = 32;
		/**
		 * @brief unordered map for textures which stores them in format {id : texture}		
		*/
		TextureMap textures{};

	public:
		/**
		 * @brief default constructor which initialize width and height, load textures and set fps lock
		*/
		View();
		/**
		 * @brief destructor which unload textures and close window
		*/
		~View();
		/**
		 * @brief method that draws blank background		
		*/
		void DrawBlankBackground();
		/**
		 * @brief method that draws menu with current choosen option		
		*/
		void DrawMenu(MenuService &menuservice);
		/**
		 * @brief method that draw new game menu	
		*/
		void DrawNewGame();
		/**
		 * @brief method that draws level with collision box and interaction box		
		*/
		void DrawLevelDebug(Level &level);
		/**
		 * @brief method that draws all neccesary UI and level	
		*/
		void DrawGame(Dungeon &dungeon, Item *selectedItem);
		/**
		 * @brief method that draws character stats and UI	
		*/
		void DrawCharacter(Character &character, float offsetx, float offsety);
		/**
		 * @brief height setter
		*/
		void SetHeight(int height);
		/**
		 * @brief width setter		
		*/
		void SetWidth(int width);
		/**
		 * @brief method that loads all textures		
		*/
		bool LoadTextures();
		/**
		 * @brief method that unloads all textures	
		*/
		void UnloadTextures();
		/**
		 * @brief method that draws all enemies		
		*/
		void DrawEnemies(std::vector<Enemy> &enemies, float offsetx, float offsety);
		/**
		 * @brief method that draws all items	
		*/
		void DrawItems(std::vector<std::unique_ptr<Item>> &items, float offsetx, float offsety);
		/**
		 * @brief method that draws level (items, map)
		*/
		void DrawLevelNew(Level &level, float offsetx, float offsety);
		/**
		 * @brief method that draw one gameobject		
		*/
		void DrawGameObject(float x, float y, GameObject &gameobject);
		/**
		 * @brief method that draws one item		
		*/
		void DrawItem(float x, float y, Item &item);
		/**
		 * @brief method that draws character UI		
		*/
		void DrawCharacterUI(float offsetx, float offsety, Character &character);
		/**
		 * @brief method that draws which item player can pick up		
		*/
		void DrawSelectedOption(Item *item, float offsetx, float offsety, Character &character);
		/**
		 * @brief method that draws chest on level		
		*/
		void DrawObstacle(std::unique_ptr<Chester> &chester, float offsetx, float offsety);
		/**
		 * @brief method that draws ladder	
		*/
		void DrawLadder(std::unique_ptr<GameObject> &ladder, float offsetx, float offsety);
		/**
		 * @brief method that draws character stats	
		*/
		void DrawCharacterStats(float offsetx, float offsety, Character &character);
		/**
		 * @brief helper method that draws text on screen		
		*/
		void DrawTextInt(int input, float x, float y, std::string text);
		/**
		 * @brief method that draw options menu	
		*/
		void DrawOptions();
};

#endif
