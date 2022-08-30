#include "Tree.h"
#include "Unit.h"

Tree::Tree() : DooDad()
{
    init();
}

Tree::Tree(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
	init();
}

Tree::Tree(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

Tree::Tree(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}

Tree::Tree(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
	init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case TREE_HEALTH:
            //health = stoi(saveObject.attributes[i].valueString);
            break;
        case TREE_MAX_HEALTH:
            //maxhealth = stoi(saveObject.attributes[i].valueString);
            break;
        case TREE_STATE:
            state = stoi(saveObject.attributes[i].valueString);
            break;
        case TREE_REGROW_TICK:
            regrowTick = stoi(saveObject.attributes[i].valueString);
            break;
        case DOODAD_PASSABLE:
            passable = stoi(saveObject.attributes[i].valueString);
        default:
            break;
        }
    }
}

void Tree::actionOn(Unit* unit, int actionType)
{
    switch (actionType)
    {
    case OVERWORLD_STRIKE:
        if (state == TREE_STATE_FULLY_GROWN)
        {
            health -= 1;
            if (health <= 0)
            {
                health = 0;
                passable = true;
                state = TREE_STATE_CUT;
                textureKey = TEXTURE_TREE_STUMP;
                regrowTick = 0;
                Item* logs = createNewItem(ITEM_WOOD);
                logs->stackSize = 5;
                unit->scene->addItemsToMap(unit->getZone(), tileCoords[0], tileCoords[1], { logs });
            }
        }
        break;
    default:
        break;
    }
}

void Tree::update()
{
    if (state == TREE_STATE_CUT)
    {
        regrowTick += 1;
        if (regrowTick >= TREE_REGROW_TIME && scene->getUnitAtLocation(zoneId, tileCoords[0], tileCoords[1]) == nullptr)
        {
            health = maxhealth;
            passable = false;
            state = TREE_STATE_FULLY_GROWN;
            textureKey = TREE;
            regrowTick = 0;
        }
    }
}

std::string Tree::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_TREE) + "\n";
    }
    saveString += DooDad::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), TREE_HEALTH, health);
    saveString += getAttributeString(getUniqueId(), TREE_MAX_HEALTH, maxhealth);
    saveString += getAttributeString(getUniqueId(), TREE_STATE, state);
    saveString += getAttributeString(getUniqueId(), TREE_REGROW_TICK, regrowTick);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_TREE) + "\n";
    }
    return saveString;
}

void Tree::init()
{
	type = DOODAD_TREE;
    //textureKey = TREE;
    passable = false;
    health = 10;
    maxhealth = 10;
    state = TREE_STATE_FULLY_GROWN;
    regrowTick = 0;
}

