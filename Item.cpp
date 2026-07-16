#include "Item.h"

Item::Item() {
    name = "Empty";
    type = "None";
}

Item::Item(std::string itemName, std::string itemType) {
    name = itemName;
    type = itemType;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getType() const {
    return type;
}