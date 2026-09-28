#ifndef MENU_H
#define MENU_H

#include <cstddef>

enum State{

	NewGame,
	Continue,
	LoadGame,
	Options,
	Exit,
	Menu,
	GameOver,
	Game

};

class MenuService{

	public:

		State states[5] = {NewGame, Continue, LoadGame, Options, Exit};
		size_t currentState = 0;

		State GetState(){

			return states[currentState];

		}

		void operator++(int){

			currentState = (currentState + 1) % 5;

		}
	
		void operator--(int){

			currentState = (currentState - 1 + 5) % 5;

		}

		const char *ConvertStateToChar(State state){

			switch (state){

				case NewGame : return "New game";
				case Continue : return "Continue";
				case LoadGame : return "LoadGame";
				case Options : return "Options";
				case Exit : return "Exit";
				default : return "Error Text";
			}

		}

};

#endif
