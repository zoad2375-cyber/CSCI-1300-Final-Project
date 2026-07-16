#ifndef NPC_H
#define NPC_H

#include <string>

class NPC {
protected:
    std::string name;
    std::string dialogue;

public:
    NPC();
    NPC(std::string npc_name, std::string npc_dialogue);
    virtual void speak(); 
};

#endif