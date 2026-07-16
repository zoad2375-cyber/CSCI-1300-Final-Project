#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
    std::string type; 

public:
    Item();

    Item(std::string itemName, std::string itemType);

    // Getters
    std::string getName() const;
    std::string getType() const;
};

#endif