#ifndef VILLAGER_H
#define VILLAGER_H

#include "NPC.h"

class Villager : public NPC {
private:
    std::string quest_flower; 

public:
    Villager();
    Villager(std::string npc_name, std::string npc_dialogue, std::string flower);
    void speak() override; 
};

#endif