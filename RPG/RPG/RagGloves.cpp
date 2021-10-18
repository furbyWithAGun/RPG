#include "RagGloves.h"

RagGloves::RagGloves() : Armour()
{
    init();
}

void RagGloves::init()
{
    name = "Rag Gloves";
    textureKey = ITEM_RAG_GLOVES;
    armour = 1;
    slot = HANDS_SLOT;
    value = 50;
}
