#include <iostream>
#include "raylib.h"
#include "SourceCode/Controller/controller.h"
#include "SourceCode/View/view.h"


int main(){

	try{

		Controller controller{};
		while (controller.RunGame()){

		}
	
	} catch (std::exception &e){

		std::cout << e.what();

	}

	return 0;

}
