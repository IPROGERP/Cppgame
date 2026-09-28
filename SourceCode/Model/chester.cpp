#include "chester.h"
#include <memory>
#include <random>

Chester::Chester(std::unique_ptr<Item> item) : item(std::move(item)){

	SetId(ChesterTexture);

}

Chester::Chester(){

	SetId(ChesterTexture);

}

void Chester::SetItem(std::unique_ptr<Item> newItem){

    item = std::move(newItem);

}

std::unique_ptr<Item> Chester::OpenChest(){

    if (rand() % 100 > 50 && item){

        return std::move(item);

    }

    return nullptr;

}

std::unique_ptr<Item> Chester::GetItem(){

    if (item){

        return std::move(item);

    }

    return nullptr;
    
}
