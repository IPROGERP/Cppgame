#ifndef TILE_H
#define TILE_H

#include <string>
#include "gameobject.h"

enum TileType{

	Floor,
	Wall,
	Void

};

class Tile : public GameObject {

	private:

		TileType tile = Floor;

	public:
	
		Tile(){

			this -> tile = Floor;

		}
	
		Tile(TileType tile){

			this -> tile = tile;

		}

		std::string ConvertToString(TileType tile) const {

			switch (tile){

				case Floor : return "Floor";
				case Wall : return "Wall";
				case Void : return "Void";
				default : return "Error text";

			}

		}

		friend std::ostream &operator<<(std::ostream &os, const Tile &other){

			os << other.ConvertToString(other.GetTileType()); 
			return os;

		}

		TileType GetTileType() const {

			return tile;

		}

};

#endif 
