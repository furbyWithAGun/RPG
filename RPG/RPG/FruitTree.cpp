#include "FruitTree.h"
#include "Unit.h"

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

FruitTree::FruitTree(SaveObject saveObject, TileGridScene* gameScene) : Tree(saveObject, gameScene)
{
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case FRUIT_TREE_FRUIT_GROWN:
            fruitGrown = stoi(saveObject.attributes[i].valueString);
            break;
        case FRUIT_TREE_FRUIT_REGROW_TICK:
            fruitRegrowTick = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void FruitTree::actionOn(Unit* unit, int actionType)
{
    Tree::actionOn(unit, actionType);
}

void FruitTree::update()
{
    
}

std::string FruitTree::toSaveString(bool withHeaderAndFooter)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_TREE) + "\n";
    }
    saveString += Tree::toSaveString(false);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_FRUIT_GROWN, fruitGrown);
    saveString += getAttributeString(getUniqueId(), FRUIT_TREE_FRUIT_REGROW_TICK, fruitRegrowTick);
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(SAVED_TREE) + "\n";
    }
    return saveString;
}

void FruitTree::init()
{
    fruitGrown = -1;
}

