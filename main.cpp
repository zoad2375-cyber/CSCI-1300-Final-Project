#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "NPC.h"
#include "Villager.h"
#include "Item.h"

void displayMap(std::string currentLoc) {
    std::cout << "\n=================== MAP OF THE VALLEY ===================\n";
    std::cout << "             " << (currentLoc == "Mines" ? "[*Mines*]" : "[Mines]") << "\n";
    std::cout << "                |\n";
    std::cout << "  " << (currentLoc == "Farm" ? "[*Farm*]" : "[Farm]") << " ---- "
              << (currentLoc == "Town" ? "[*Town*]" : "[Town]") << " ---- "
              << (currentLoc == "Community Center" ? "[*Comm. Center*]" : "[Community Center]") << " ---- "
              << (currentLoc == "Beach" ? "[*Beach*]" : "[Beach]") << "\n";
    std::cout << "                |\n";
    std::cout << "             " << (currentLoc == "Forest" ? "[*Forest*]" : "[Forest]") << "\n";
    std::cout << "\n  * = Your Current Location\n";
    std::cout << "=========================================================\n";
}

int main() {
    Player player;

    int currentDay = 1;
    const int MAX_DAYS = 7; 
    int jojaInfluence = 0; 
    
    const int NUM_FLOWERS = 10;
    std::string flowersList[NUM_FLOWERS] = {
        "Daffodil", "Dandelion", "Wild Blue Phlox", "Sweet Violet", 
        "Spring Beauty", "Trillium", "Wood Anemone", "Marsh Marigold", 
        "Dutchman's Breeches", "Jack-in-the-pulpit"
    };
    bool donatedFlowers[NUM_FLOWERS] = {false}; 

    std::string mayorDialogue = ""; 
    std::ifstream inputFile("dialogue.txt"); 

    if (inputFile.is_open()) {
        std::getline(inputFile, mayorDialogue); 
        inputFile.close(); 
    } else {
        mayorDialogue = "Welcome to our valley! (Failed to load dialogue.txt)";
    }

    Villager mayor("Mayor Lewis", mayorDialogue, "Daffodil");
    Villager pierre("Pierre", "Clear weeds on the Farm to find domestic wildflowers!", "Dandelion");
    Villager willy("Willy", "Tide pools at the Beach hold beautiful coastal blooms!", "Marsh Marigold");
    Villager clint("Clint", "Mine deep in the Mines to find rare cave flowers!", "Wood Anemone");
    Villager morris("Morris", "Why search? Joja can import any flower for 40g!", "Joja Cola");

    int choice = 0;
    bool keep_playing = true;

    std::cout << "Welcome to the Flower Collecting Game!\n";

    while (keep_playing) {
        displayMap(player.getCurrentLocation());
        std::cout << "Current Location: " << player.getCurrentLocation() << "\n";

        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "Day: " << currentDay << " / " << MAX_DAYS << " | Energy: " << player.getEnergy() << " | Money: " << player.getMoney() << "g\n";
        std::cout << "1. Check Player Stats & Inventory\n";
        std::cout << "2. Forage for Flowers / Talk to Townspeople\n";
        std::cout << "3. Travel to another location (Costs 1 Energy)\n";
        std::cout << "4. Donate Flowers to Community Exhibition\n";
        std::cout << "5. Rest / End Day (Restores Energy, Advances Day, Grants 20g)\n";
        std::cout << "6. Quit Game\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            player.displayStats();
        } 
        else if (choice == 2) {
            std::string currentLoc = player.getCurrentLocation();

            if (currentLoc == "Town") {
                std::cout << "\n[Town Square]\n";
                mayor.speak(); 
                std::cout << "Lewis says: \"We need 10 unique wild flowers for the Exhibition! Have you checked the wild areas?\"\n";
            }
            else if (currentLoc == "Beach") {
                std::cout << "\n[The Beach]\n";
                willy.speak();
                std::cout << "\n1. Forage Beach Flowers\n2. Just chatting\nChoice: ";
                int willyChoice;
                std::cin >> willyChoice;
                if (willyChoice == 1) {
                    if (player.getEnergy() >= 2) {
                        player.setEnergy(player.getEnergy() - 2);
                        std::string foundFlower = (player.getMoney() % 2 == 0) ? "Dutchman's Breeches" : "Marsh Marigold";
                        Item flower(foundFlower, "Flower");
                        if (player.addItem(flower)) {
                            std::cout << "You found a wild " << foundFlower << " growing in the salty grass!\n";
                        }
                    } else {
                        std::cout << "You are too tired to forage here!\n";
                    }
                }
            }
            else if (currentLoc == "Mines") {
                std::cout << "\n[The Mines Entrance]\n";
                clint.speak();
                std::cout << "\n1. Search Deep Crevices\n2. Just chatting\nChoice: ";
                int clintChoice;
                std::cin >> clintChoice;
                if (clintChoice == 1) {
                    if (player.getEnergy() >= 3) {
                        player.setEnergy(player.getEnergy() - 3);
                        std::string foundFlower = (player.getMoney() % 2 == 0) ? "Wood Anemone" : "Jack-in-the-pulpit";
                        Item flower(foundFlower, "Flower");
                        if (player.addItem(flower)) {
                            std::cout << "You mined past some stone and found a delicate " << foundFlower << "!\n";
                        }
                    } else {
                        std::cout << "You are too tired to climb down there!\n";
                    }
                }
            }
            else if (currentLoc == "Farm") {
                std::cout << "\n[The Farm]\n";
                pierre.speak();
                std::cout << "\n1. Clear Weeds for Flowers\n2. Just chatting\nChoice: ";
                int pierreChoice;
                std::cin >> pierreChoice;
                if (pierreChoice == 1) {
                    if (player.getEnergy() >= 1) {
                        player.setEnergy(player.getEnergy() - 1);
                        std::string foundFlower = (player.getEnergy() % 2 == 0) ? "Daffodil" : "Dandelion";
                        Item flower(foundFlower, "Flower");
                        if (player.addItem(flower)) {
                            std::cout << "You cleared away some brush and uncovered a " << foundFlower << "!\n";
                        }
                    } else {
                        std::cout << "You don't have enough energy!\n";
                    }
                }
            }
            else if (currentLoc == "Forest") {
                std::cout << "\n[The Forest]\n";
                std::cout << "1. Forage in the deep woods (Costs 1 Energy)\n";
                std::cout << "2. Visit Morris (JojaMart Outpost)\n";
                std::cout << "Choice: ";
                int forestChoice;
                std::cin >> forestChoice;

                if (forestChoice == 1) {
                    if (player.getEnergy() >= 1) {
                        player.setEnergy(player.getEnergy() - 1);
                        int randIndex = (player.getEnergy() + player.getMoney()) % 4 + 2; 
                        std::string foundFlower = flowersList[randIndex];
                        Item flower(foundFlower, "Flower"); 
                        
                        if (player.addItem(flower)) {
                            std::cout << "You found a lovely " << foundFlower << " in the forest shade!\n";
                        }
                    } else {
                        std::cout << "You are too tired to forage in the forest!\n";
                    }
                }
                else if (forestChoice == 2) {
                    morris.speak();
                    std::cout << "\n1. Buy Rare Flower (40g)\n2. Leave\nChoice: ";
                    int morrisChoice;
                    std::cin >> morrisChoice;
                    
                    if (morrisChoice == 1) {
                        if (player.getMoney() >= 40) {
                            player.setMoney(player.getMoney() - 40);
                            jojaInfluence++; 
                            std::string jojaFlower = flowersList[jojaInfluence % NUM_FLOWERS];
                            Item flower(jojaFlower, "Flower");
                            player.addItem(flower);
                            std::cout << "Morris hands you a slightly wilted " << jojaFlower << ". Joja influence increased!\n";
                        } else {
                            std::cout << "You don't have enough gold for Morris's shortcuts!\n";
                        }
                    }
                }
            }
            else {
                std::cout << "There is nobody around here to talk to.\n";
            }
        }
        else if (choice == 3) {
            if (player.getEnergy() <= 0) {
                std::cout << "You are too tired to travel! You need to rest.\n";
            } else {
                std::cout << "\nWhere would you like to travel?\n";
                std::cout << "1. Farm\n";
                std::cout << "2. Town\n";
                std::cout << "3. Community Center\n";
                std::cout << "4. Beach\n";
                std::cout << "5. Mines\n";
                std::cout << "6. Forest\n";
                std::cout << "Enter choice: ";
                int moveChoice;
                std::cin >> moveChoice;

                std::string newLoc = player.getCurrentLocation();
                if (moveChoice == 1) newLoc = "Farm";
                else if (moveChoice == 2) newLoc = "Town";
                else if (moveChoice == 3) newLoc = "Community Center";
                else if (moveChoice == 4) newLoc = "Beach";
                else if (moveChoice == 5) newLoc = "Mines";
                else if (moveChoice == 6) newLoc = "Forest";
                else {
                    std::cout << "Invalid location selection.\n";
                }

                if (newLoc != player.getCurrentLocation()) {
                    player.setCurrentLocation(newLoc);
                    player.setEnergy(player.getEnergy() - 1);
                    std::cout << "You traveled to the " << newLoc << ". (Used 1 Energy)\n";
                }
            }
        }
        else if (choice == 4) {
            if (player.getCurrentLocation() != "Community Center") {
                std::cout << "You must be at the Community Center to donate flowers!\n";
            } else {
                std::cout << "\n=== FLOWER EXHIBITION PROGRESS ===\n";
                int totalDonated = 0;
                for (int i = 0; i < NUM_FLOWERS; i++) {
                    std::cout << "- " << flowersList[i] << ": " 
                              << (donatedFlowers[i] ? "[✓] Donated" : "[ ] Missing") << "\n";
                    if (donatedFlowers[i]) totalDonated++;
                }
                std::cout << "Total Progress: " << totalDonated << " / " << NUM_FLOWERS << " unique flowers.\n";
                
                std::cout << "\nWould you like to donate a flower from your inventory?\n";
                std::cout << "1. Yes, attempt donation\n2. Back\nChoice: ";
                int donateChoice;
                std::cin >> donateChoice;

                if (donateChoice == 1) {
                    std::cout << "\nWhich flower do you want to submit? (Enter number 1-10): \n";
                    for(int i = 0; i < NUM_FLOWERS; i++) {
                        std::cout << i + 1 << ". " << flowersList[i] << "\n";
                    }
                    int flowerIndex;
                    std::cin >> flowerIndex;
                    flowerIndex--;

                    if (flowerIndex >= 0 && flowerIndex < NUM_FLOWERS) {
                        std::string targetFlower = flowersList[flowerIndex];
                        
                        if (donatedFlowers[flowerIndex]) {
                            std::cout << "That flower has already been donated!\n";
                        } 
                        else if (player.hasItem(targetFlower)) {
                            donatedFlowers[flowerIndex] = true;
                            player.removeItem(targetFlower); 
                            std::cout << "Successfully donated a " << targetFlower << " from your inventory to the exhibition!\n";
                        } 
                        else {
                            std::cout << "You do not have a " << targetFlower << " in your inventory to donate!\n";
                        }
                    } else {
                        std::cout << "Invalid selection.\n";
                    }
                }
            }
        }
        else if (choice == 5) {
            std::cout << "You head to bed. Day ends, energy restored!\n";
            player.setEnergy(10); 
            player.setMoney(player.getMoney() + 20); 
            currentDay++;
            
            if (currentDay > MAX_DAYS) {
                std::cout << "\nTime has run out! The season is over.\n";
                keep_playing = false;
            }
        }
        else if (choice == 6) {
            std::cout << "Thank you for playing!\n";
            keep_playing = false;
        }
    } 

    std::cout << "\n=========================================\n";
    std::cout << "               GAME OVER                 \n";
    std::cout << "=========================================\n";

    bool wonGame = true;
    for (int i = 0; i < NUM_FLOWERS; i++) {
        if (!donatedFlowers[i]) {
            wonGame = false;
        }
    }

    if (wonGame) {
        if (jojaInfluence == 0) {
            std::cout << "SUCCESS: You restored the Community Center purely with local wild flowers!\n";
            std::cout << "Ending: FLOWER BOTANIST HERO ENDING! The valley flourishes beautifully.\n";
        } else {
            std::cout << "SUCCESS: The exhibition is complete, but JojaMart imported flowers for you.\n";
            std::cout << "Ending: JOJA CORPORATE GARDEN ENDING. The valley is colorful, but under Morris's thumb.\n";
        }
    } else {
        std::cout << "FAILURE: You ran out of time before gathering all 10 unique wild flowers.\n";
        std::cout << "Ending: DRY SEASON ENDING. The flower exhibition has failed.\n";
    }

    return 0;
}