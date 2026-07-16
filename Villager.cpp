#include "Villager.h"
#include <iostream>

Villager::Villager() : NPC() {
    quest_flower = "Dandelion";
}

Villager::Villager(std::string npc_name, std::string npc_dialogue, std::string flower) 
    : NPC(npc_name, npc_dialogue) {
    quest_flower = flower;
}

void Villager::speak() {
    NPC::speak(); 
    std::cout << "(" << name << " seems to really want a " << quest_flower << ".)\n";
}