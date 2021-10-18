#include "RagBody.h"

RagBody::RagBody() : Armour()
{
    init();
}

void RagBody::init()
{
    name = "Rag Shirt";
    textureKey = ITEM_RAG_BODY;
    armour = 1;
    slot = BODY_SLOT;
    value = 50;
}
