#include "BerryBush.h"
#include "RpgUnit.h"
#include "RpgTileGridScene.h"

BerryBush::BerryBush() : DooDad()
{
    init();
}

BerryBush::BerryBush(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
    init();
}

BerryBush::BerryBush(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

BerryBush::BerryBush(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}

BerryBush::BerryBush(TileGridScene* gameScene, int berryToGrow) : DooDad(gameScene)
{
    init();
    berryGrown = berryToGrow;
}

BerryBush::BerryBush(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case DOODAD_TEXTURE_ID:
            textureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case BERRY_BUSH_BERRY_GROWN:
            berryGrown = stoi(saveObject.attributes[i].valueString);
            break;
        case BERRY_BUSH_BERRY_REGROW_TICK:
            berryRegrowTick = stoi(saveObject.attributes[i].valueString);
            break;
        case BERRY_BUSH_BERRY_STATE:
            berryState = stoi(saveObject.attributes[i].valueString);
            break;
        case BERRY_BUSH_GROWN_BERRY_TEXTURE_KEY:
            grownBerryTextureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case BERRY_BUSH_NO_BERRY_TEXTURE_KEY:
            noBerryTextureKey = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void BerryBush::actionOn(Unit* unit, int actionType)
{
    switch (actionType)
    {
    case OVERWORLD_USE:
        if (berryState == BERRY_BUSH_AVAILABLE_BERRIES)
        {
            ((RpgUnit*)unit)->addToInventory(createNewItem(berryGrown));
            berryState = BERRY_BUSH_NO_BERRIES;
            textureKey = noBerryTextureKey;
        }
        break;
    case OVERWORLD_STRIKE:
        if (berryState == BERRY_BUSH_AVAILABLE_BERRIES)
        {
            ((RpgUnit*)unit)->addToInventory(createNewItem(berryGrown));
            berryState = BERRY_BUSH_NO_BERRIES;
            textureKey = noBerryTextureKey;
        }
        break;
    default:
        break;
    }
}

void BerryBush::update()
{
    if (berryState == BERRY_BUSH_NO_BERRIES) {
        berryRegrowTick++;
        if (berryRegrowTick >= BERRY_BUSH_REGROW_TIME)
        {
            berryState = BERRY_BUSH_AVAILABLE_BERRIES;
            textureKey = grownBerryTextureKey;
            berryRegrowTick = 0;
        }
    }
}

std::string BerryBush::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BERRY_BUSH) + "\n";
    }
    saveString += DooDad::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), BERRY_BUSH_BERRY_GROWN, berryGrown);
    saveString += getAttributeString(getUniqueId(), BERRY_BUSH_BERRY_REGROW_TICK, berryRegrowTick);
    saveString += getAttributeString(getUniqueId(), BERRY_BUSH_BERRY_STATE, berryState);
    saveString += getAttributeString(getUniqueId(), BERRY_BUSH_GROWN_BERRY_TEXTURE_KEY, grownBerryTextureKey);
    saveString += getAttributeString(getUniqueId(), BERRY_BUSH_NO_BERRY_TEXTURE_KEY, noBerryTextureKey);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_BERRY_BUSH) + "\n";
    }
    return saveString;
}

void BerryBush::init()
{
    berryGrown = -1;
    berryState = BERRY_BUSH_AVAILABLE_BERRIES;
    passable = true;
}

