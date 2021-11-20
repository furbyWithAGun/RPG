#include "FruitTree.h"
#include "RpgUnit.h"
#include "RpgTileGridScene.h"

FruitTree::FruitTree() : Tree()
{
    init();
}

FruitTree::FruitTree(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : Tree(gameScene, textureKey, tileX, tileY)
{
    init();
}

FruitTree::FruitTree(TileGridScene* gameScene, int tileX, int tileY) : Tree(gameScene, tileX, tileY)
{
    init();
}

FruitTree::FruitTree(TileGridScene* gameScene) : Tree(gameScene)
{
    init();
}

FruitTree::FruitTree(TileGridScene* gameScene, int fruitToGrow) : Tree(gameScene)
{
    init();
    fruitGrown = fruitToGrow;
}

FruitTree::FruitTree(SaveObject saveObject, TileGridScene* gameScene) : Tree(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case DOODAD_TEXTURE_ID:
            textureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case DOODAD_TYPE:
            type = stoi(saveObject.attributes[i].valueString);
            break;
        case FRUIT_TREE_FRUIT_GROWN:
            fruitGrown = stoi(saveObject.attributes[i].valueString);
            break;
        case FRUIT_TREE_FRUIT_REGROW_TICK:
            fruitRegrowTick = stoi(saveObject.attributes[i].valueString);
            break;
        case FRUIT_TREE_FRUIT_STATE:
            fruitState = stoi(saveObject.attributes[i].valueString);
            break;
        case FRUIT_TREE_GROWN_FRUIT_TEXTURE_KEY:
            grownFruitTextureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case FRUIT_TREE_NO_FRUIT_TEXTURE_KEY:
            noFruitTextureKey = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void FruitTree::actionOn(Unit* unit, int actionType)
{
    switch (actionType)
    {
    case OVERWORLD_USE:
        if (fruitState == FRUIT_TREE_AVAILABLE_FRUIT)
        {
            ((RpgUnit*)unit)->addToInventory(createNewItem(fruitGrown));
            fruitState = FRUIT_TREE_NO_FRUIT;
            textureKey = noFruitTextureKey;
        }
        else {
            Tree::actionOn(unit, actionType);
        }
        break;
    case OVERWORLD_STRIKE:
        if (fruitState == FRUIT_TREE_AVAILABLE_FRUIT)
        {
            ((RpgUnit*)unit)->addToInventory(createNewItem(fruitGrown));
            fruitState = FRUIT_TREE_NO_FRUIT;
            textureKey = noFruitTextureKey;
        }
        else {
            Tree::actionOn(unit, actionType);
        }
        break;
    default:
        break;
    }
}

void FruitTree::update()
{
    Tree::update();
    if (state == TREE_STATE_CUT)
    {
        fruitState = FRUIT_TREE_NO_FRUIT;
    }
    else if (state == TREE_STATE_FULLY_GROWN && fruitState == FRUIT_TREE_NO_FRUIT) {
        fruitRegrowTick++;
        if (fruitRegrowTick >= FRUIT_TREE_REGROW_TIME)
        {
            fruitState = FRUIT_TREE_AVAILABLE_FRUIT;
            textureKey = grownFruitTextureKey;
            fruitRegrowTick = 0;
        }
    }
    else if (state == TREE_STATE_FULLY_GROWN && fruitState == FRUIT_TREE_AVAILABLE_FRUIT) {
        textureKey = grownFruitTextureKey;
    }
    else{
        textureKey = noFruitTextureKey;
    }
}

std::string FruitTree::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_FRUIT_TREE) + "\n";
    }
    saveString += Tree::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_FRUIT_GROWN, fruitGrown);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_FRUIT_REGROW_TICK, fruitRegrowTick);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_FRUIT_STATE, fruitState);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_GROWN_FRUIT_TEXTURE_KEY, grownFruitTextureKey);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_NO_FRUIT_TEXTURE_KEY, noFruitTextureKey);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_FRUIT_TREE) + "\n";
    }
    return saveString;
}

void FruitTree::init()
{
    fruitGrown = -1;
    fruitState = FRUIT_TREE_AVAILABLE_FRUIT;
}

