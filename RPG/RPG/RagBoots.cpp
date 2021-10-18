#include "RagBoots.h"
RagBoots::RagBoots() : Armour()
{
    init();
}

void RagBoots::init()
{
    name = "Rag Boots";
    textureKey = ITEM_RAG_BOOTS;
    armour = 1;
    slot = FEET_SLOT;
    value = 50;
}