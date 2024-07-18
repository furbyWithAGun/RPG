#include "MineBlock.h"

#include "Unit.h"

MineBlock::MineBlock() : DooDad()
{
    init();
}

MineBlock::MineBlock(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
    init();
}

MineBlock::MineBlock(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

MineBlock::MineBlock(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}

MineBlock::MineBlock(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
            case DOODAD_TEXTURE_ID:
                textureKey = stoi(saveObject.attributes[i].valueString);
                break;
            case MINEBLOCK_HEALTH:
                //health = stoi(saveObject.attributes[i].valueString);
                break;
            case MINEBLOCK_MAX_HEALTH:
                //maxhealth = stoi(saveObject.attributes[i].valueString);
                break;
            case MINEBLOCK_STATE:
                state = stoi(saveObject.attributes[i].valueString);
                break;
            case MINEBLOCK_REGROW_TICK:
                regrowTick = stoi(saveObject.attributes[i].valueString);
                break;
            case DOODAD_PASSABLE:
                passable = stoi(saveObject.attributes[i].valueString);
            default:
                break;
        }
    }
}

void MineBlock::actionOn(Unit* unit, int actionType)
{
    switch (actionType)
    {
    case OVERWORLD_STRIKE:
        if (state == MINEBLOCK_STATE_FULL)
        {
            health -= 1;
            if (health <= 0)
            {
                health = 0;
                passable = true;
                state = MINEBLOCK_STATE_DEPLETED;
                textureKey = BLANK_PORTAL;
                regrowTick = 0;
                //Item* bronze = createNewItem(ITEM_BRONZE_BODY);
                std::vector<ChanceObject> potentialFinds = { 
                    {0.7, ITEM_STONE}, 
                    {0.1, ITEM_COAL}, 
                    {0.1, ITEM_TIN_ORE}, 
                    {0.1, ITEM_COPPER_ORE}, 
                };
                Item* item = createNewItem(scene->engine->pickElementByProbability(potentialFinds));
                item->stackSize = 5;
                unit->scene->addItemsToMap(unit->getZone(), tileCoords[0], tileCoords[1], { item });
            }
        }
        break;
    default:
        break;
    }
}

void MineBlock::update()
{
    if (state == MINEBLOCK_STATE_DEPLETED)
    {
        regrowTick += 1;
        if (regrowTick >= MINEBLOCK_REGROW_TIME && scene->getUnitAtLocation(zoneId, tileCoords[0], tileCoords[1]) == nullptr)
        {
            health = maxhealth;
            passable = false;
            state = MINEBLOCK_STATE_FULL;
            textureKey = TEXTURE_MINEBLOCK;
            regrowTick = 0;
        }
    }
}

std::string MineBlock::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_MINEBLOCK) + "\n";
    }
    saveString += DooDad::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), MINEBLOCK_HEALTH, health);
    saveString += getAttributeString(getUniqueId(), MINEBLOCK_MAX_HEALTH, maxhealth);
    saveString += getAttributeString(getUniqueId(), MINEBLOCK_STATE, state);
    saveString += getAttributeString(getUniqueId(), MINEBLOCK_REGROW_TICK, regrowTick);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_MINEBLOCK) + "\n";
    }
    return saveString;
}

void MineBlock::init()
{
    type = DOODAD_MINEBLOCK;
    textureKey = TEXTURE_MINEBLOCK;
    passable = false;
    health = 10;
    maxhealth = 10;
    state = MINEBLOCK_STATE_FULL;
    regrowTick = 0;
}

