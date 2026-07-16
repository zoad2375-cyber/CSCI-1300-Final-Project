#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Item.h" 

class Player {
private:
    std::string name;
    int energy;
    int money;                  
    std::string currentLocation; 

    static const int MAX_INV = 5; 
    Item inventory[MAX_INV];     
    int inventoryCount;           

public:
    Player(); 

    int getEnergy() const;
    void setEnergy(int newEnergy);

    int getMoney() const;
    void setMoney(int newMoney);

    std::string getCurrentLocation() const;
    void setCurrentLocation(std::string location);

    bool addItem(Item newItem);   
    void displayInventory() const; 
    void displayStats();     
    
    bool hasItem(std::string itemName) const;
    void removeItem(std::string itemName);
};

#endif