#include "RagHat.h"
RagHat::RagHat() : Armour()
{
    init();
}

void RagHat::init()
{
    name = "Rag Hat";
    textureKey = ITEM_RAG_HAT;
    armour = 1;
    slot = HEAD_SLOT;
    value = 50;
}
