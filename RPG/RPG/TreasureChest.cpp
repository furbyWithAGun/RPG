#include "TreasureChest.h"
#include "RpgUnit.h"
#include "RpgTileGridScene.h"


TreasureChest::TreasureChest() : DooDad()
{
    init();
}

TreasureChest::TreasureChest(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
    init();
}

TreasureChest::TreasureChest(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

TreasureChest::TreasureChest(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}


TreasureChest::TreasureChest(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case DOODAD_TEXTURE_ID:
            textureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case TREASURE_CHEST_CLOSED:
            closed = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void TreasureChest::actionOn(Unit* unit, int actionType)
{
    switch (actionType)
    {
    case OVERWORLD_USE:
        openChest();
        break;
    case OVERWORLD_STRIKE:
        openChest();
        break;
    default:
        break;
    }
}


std::string TreasureChest::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BERRY_BUSH) + "\n";
    }
    saveString += DooDad::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), TREASURE_CHEST_CLOSED, closed);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BERRY_BUSH) + "\n";
    }
    return saveString;
}

void TreasureChest::init()
{
    closed = true;
    passable = true;
    textureKey = TEXTURE_CHEST_CLOSED;
    type = DOODAD_TREASURE_CHEST;
}

void TreasureChest::openChest()
{
    if (closed)
    {
        closed = false;
        textureKey = TEXTURE_CHEST_OPEN;
        scene->addItemsToMap(zoneId, tileCoords[0], tileCoords[1], getDrops());
    }
}

std::vector<Item*> TreasureChest::getDrops()
{
    RpgTileGridScene* rpgScene = (RpgTileGridScene*)scene;
    std::vector<Item*> returnItems;
    
    if (rpgScene->chestDropTable[rpgScene->getZone(zoneId)->difficulty].size() > 0)
    {
        int numDrops = scene->engine->randomInt(1, rpgScene->chestDropNum[rpgScene->getZone(zoneId)->difficulty]);
        for (size_t i = 0; i < numDrops; i++)
        {
            returnItems.push_back(createNewItem(scene->engine->pickElementByProbability(rpgScene->chestDropTable[rpgScene->getZone(zoneId)->difficulty])));
        }
    }
    return returnItems;
}



