#include "DooDad.h"
#include "Unit.h"

DooDad::DooDad() : Sprite()
{
	init();
}

DooDad::DooDad(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : Sprite(textureKey, (GameScene*)gameScene)
{
	init(gameScene);
	tileCoords[0] = tileX;
	tileCoords[1] = tileY;
}

DooDad::DooDad(TileGridScene* gameScene, int tileX, int tileY) : Sprite(textureKey, (GameScene*)gameScene)
{
    init(gameScene);
    tileCoords[0] = tileX;
    tileCoords[1] = tileY;
}

DooDad::DooDad(TileGridScene* gameScene) : Sprite(textureKey, (GameScene*)gameScene)
{
    init(gameScene);
    scene = gameScene;
}

DooDad::DooDad(SaveObject saveObject, TileGridScene* gameScene) : Sprite(gameScene){
    init(gameScene);
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case DOODAD_TEXTURE_ID:
            textureKey = stoi(saveObject.attributes[i].valueString);
            break;
        case DOODAD_TYPE:
            type = stoi(saveObject.attributes[i].valueString);
            break;
        case DOODAD_PASSABLE:
            passable = stoi(saveObject.attributes[i].valueString);
            break;
        case DOODAD_ASSIGNED_TO_BUILDING:
            assignedToBuildingId = stoi(saveObject.attributes[i].valueString);
            break;
        case DOODAD_TILE_COORDS:
            tileCoords = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case DOODAD_ZONE_ID:
            zoneId = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void DooDad::walkOn(Unit* unit)
{

}

void DooDad::actionOn(Unit* unit, int actionType)
{
}

std::string DooDad::toSaveString(bool withHeaderAndFooter) {
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    if (withHeaderAndFooter)
    {
        saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(DOODAD) + "\n";
    }
    saveString += getAttributeString(getUniqueId(), DOODAD_TEXTURE_ID, textureKey);
    saveString += getAttributeString(getUniqueId(), DOODAD_TYPE, type);
    saveString += getAttributeString(getUniqueId(), DOODAD_PASSABLE, passable);
    saveString += getAttributeString(getUniqueId(), DOODAD_ZONE_ID, zoneId);
    if (assignedToBuilding != nullptr)
    {
        saveString += getAttributeString(getUniqueId(), DOODAD_ASSIGNED_TO_BUILDING, assignedToBuilding->id);
    }
    saveString += getAttributeString(getUniqueId(), DOODAD_TILE_COORDS, getIntVectorSaveString(tileCoords));
    if (withHeaderAndFooter)
    {
        saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(DOODAD) + "\n";
    }

    return saveString;
}

void DooDad::init()
{
	tileCoords = { 0, 0 };
	scene = nullptr;
    type = -1;
    passable = true;
    assignedToBuilding = nullptr;
    assignedToBuildingId = -1;
}

void DooDad::init(TileGridScene* gameScene)
{
    init();
    scene = gameScene;
}
