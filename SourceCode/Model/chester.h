#ifndef CHEST_H
#define CHEST_H

#include <memory>
#include "item.h"

/**
 * @brief class that represent chest in game (named so because chest was used before and also as easter egg to DST)
 */
class Chester : public GameObject{
private:
    /**
     * @brief unique_ptr item stored in chest
    */
    std::unique_ptr<Item> item;

public:
    /**
     * @brief default constructor
    */
    Chester();
    /**
     * @brief constructor with item
    */
    explicit Chester(std::unique_ptr<Item> item);
    
    /**
     * @brief setter for item
    */
    void SetItem(std::unique_ptr<Item> newItem);
    /**
     * @brief method for opening chest
    */
	std::unique_ptr<Item> OpenChest();
    /**
     * @brief getter for item
    */
    std::unique_ptr<Item> GetItem();
    
};

#endif