#include "NPC.h"
#include <iostream>

NPC::NPC() {
    name = "Default NPC";
    dialogue = "Hello there!";
}

NPC::NPC(std::string npc_name, std::string npc_dialogue) {
    name = npc_name;
    dialogue = npc_dialogue;
}

void NPC::speak() {
    std::cout << name << ": \"" << dialogue << "\"\n";
} 