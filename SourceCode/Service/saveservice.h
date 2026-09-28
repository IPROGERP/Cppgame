#ifndef SAVESERVICE_H
#define SAVESERVICE_H

#include <string>   
#include "../Model/character.h"
#include "nlohmann/json.hpp"
#include "../Model/dungeon.h"

class SaveManager{

    public:

        SaveManager();
        bool SaveGame(Character &character, Dungeon &dungeon);
        bool LoadGame(Character &character, Dungeon &dungeon);

};


#endif