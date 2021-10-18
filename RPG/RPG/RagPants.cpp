#include "RagPants.h"

RagPants::RagPants() : Armour()
{
    init();
}

void RagPants::init()
{
    name = "Rag Pants";
    textureKey = ITEM_RAG_PANTS;
    armour = 1;
    slot = LEGS_SLOT;
    value = 50;
}
