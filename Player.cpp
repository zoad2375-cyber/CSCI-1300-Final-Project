#include <iostream>
#include "Player.h"

Player::Player() {
    name = "Farmer";
    energy = 10;
    money = 100;
    currentLocation = "Farm";
    inventoryCount = 0; 
}

bool Player::addItem(Item newItem) {
    if (inventoryCount < MAX_INV) {
        inventory[inventoryCount] = newItem; 
        inventoryCount++;
        return true;
    } else {
        std::cout << "Your inventory is full!\n";
        return false;
    }
}

void Player::displayInventory() const {
    std::cout << "=== INVENTORY ===\n";
    if (inventoryCount == 0) {
        std::cout << "(Empty)\n";
        return;
    }
    for (int i = 0; i < inventoryCount; i++) {
        std::cout << i + 1 << ". " << inventory[i].getName() 
                  << " (" << inventory[i].getType() << ")\n";
    }
}

void Player::displayStats() {
    std::cout << "\n=== PLAYER STATS ===\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Location: " << currentLocation << "\n";
    std::cout << "Energy: " << energy << "/10\n";
    std::cout << "Money: " << money << "g\n";
    std::cout << "--------------------\n";
    
    displayInventory();
}

int Player::getEnergy() const {
    return energy;
}

void Player::setEnergy(int newEnergy) {
    energy = newEnergy;
}

std::string Player::getCurrentLocation() const {
    return currentLocation;
}

void Player::setCurrentLocation(std::string location) {
    currentLocation = location;
}

int Player::getMoney() const {
    return money;
}

void Player::setMoney(int newMoney) {
    money = newMoney;
}

bool Player::hasItem(std::string itemName) const {
    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].getName() == itemName) {
            return true;
        }
    }
    return false;
}

void Player::removeItem(std::string itemName) {
    int indexToRemove = -1;
    
    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].getName() == itemName) {
            indexToRemove = i;
            break;
        }
    }
    
    if (indexToRemove != -1) {
        for (int i = indexToRemove; i < inventoryCount - 1; i++) {
            inventory[i] = inventory[i + 1];
        }
        inventoryCount--; 
    }
}