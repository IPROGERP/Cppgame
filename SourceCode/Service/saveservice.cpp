#include "saveservice.h"
#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

SaveManager::SaveManager(){

    std::filesystem::create_directories("../Saves/");

}

bool SaveManager::SaveGame(Character &character, Dungeon &dungeon){

    json data;

    data["character"]["exp"] = character.GetExp();
    data["character"]["expToNextLevel"] = character.GetExpToNextLevel();

    data["character"]["strength"] = character.GetStats().strength;
    data["character"]["agility"] = character.GetStats().agility;
    data["character"]["endurance"] = character.GetStats().endurance;

    data["character"]["head"] = character.GetInventory().helmet.GetRarity();
    data["character"]["chest"] = character.GetInventory().chest.GetRarity();
    data["character"]["legs"] = character.GetInventory().legs.GetRarity();
    data["character"]["feet"] = character.GetInventory().feet.GetRarity();

    data["character"]["weapon"] = character.GetInventory().weapon.GetRarity();
    data["character"]["lockpicks"] = character.GetInventory().lockpicks.GetAmount();

    data["dungeon"]["index"] = dungeon.GetIndex();

    try{

        std::ofstream file("../Saves/1.json");
        if (!file.is_open()){

            std::cout << "could not create file 1.json\n";

            return false;

        }

        file << data.dump(4);
        file.close();

        std::cout << "game saved correctly\n";

        return true;

    } catch (const std::exception& e){

            std::cout << "Error saving game: " << e.what() << std::endl;

            return false;

    }

}

bool SaveManager::LoadGame(Character &character, Dungeon &dungeon){

    try{

        std::ifstream file("../Saves/1.json");

        if (!file.is_open()){

            std::cout << "Could not open save file 1.json\n";
            return false;

        }
        
        json data;
        file >> data;
        file.close();
        
        if (data.contains("character") && data["character"].contains("exp")){

            character.SetExp(data["character"]["exp"].get<int>());

        }
        
        if (data.contains("character") && data["character"].contains("expToNextLevel")){

            character.SetExpToNextLevel(data["character"]["expToNextLevel"].get<int>());

        }

        if (data.contains("character")){

            auto& charData = data["character"];
            
            if (charData.contains("strength")){

                character.GetStats().strength = charData["strength"].get<int>();

            }
            if (charData.contains("agility")){

                character.GetStats().agility = charData["agility"].get<int>();

            }
            if (charData.contains("endurance")){

                character.GetStats().endurance = charData["endurance"].get<int>();

            }

        }

        if (data.contains("character")){

            auto& charData = data["character"];
            auto& inventory = character.GetInventory();

            if (charData.contains("head")){

                int rarityValue = charData["head"].get<int>();
                inventory.helmet.SetRarity(static_cast<ItemRarity>(rarityValue));

            }

            if (charData.contains("chest")){

                int rarityValue = charData["chest"].get<int>();
                inventory.chest.SetRarity(static_cast<ItemRarity>(rarityValue));

            }

            if (charData.contains("legs")){

                int rarityValue = charData["legs"].get<int>();
                inventory.legs.SetRarity(static_cast<ItemRarity>(rarityValue));

            }

            if (charData.contains("feet")){

                int rarityValue = charData["feet"].get<int>();
                inventory.feet.SetRarity(static_cast<ItemRarity>(rarityValue));

            }

            if (charData.contains("weapon")){

                int rarityValue = charData["weapon"].get<int>();
                inventory.weapon.SetRarity(static_cast<ItemRarity>(rarityValue));

            }
            
            if (charData.contains("lockpicks")){

                inventory.lockpicks.SetAmount(charData["lockpicks"].get<int>());

            }

        }
        
        if (data.contains("dungeon") && data["dungeon"].contains("index")){

            size_t savedIndex = data["dungeon"]["index"].get<size_t>();
            
            size_t currentIndex = dungeon.GetIndex();
            
            if (savedIndex > currentIndex){

                for (size_t i = currentIndex; i < savedIndex; i++){

                    dungeon.GoToNextLevel();

                }

            } else if (savedIndex < currentIndex){

                for (size_t i = currentIndex; i > savedIndex; i--){

                    dungeon.GoToPreviousLevel();

                }

            }
            
        }
        
        character.SpawnOnLevel(dungeon.GetLevel().GetValidCoordinate());
        
        character.SetCurrentHp(character.GetMaxHp());
        
        return true;
        
    } catch (const json::exception& e){

        std::cout << "JSON parsing error: " << e.what() << std::endl;
        return false;

    } catch (const std::exception& e){

        std::cout << "Error loading game: " << e.what() << std::endl;
        return false;

    }
    
}