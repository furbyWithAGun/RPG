#include "ZonePortal.h"
#include <string>
#include "BaseGameEngine.h"
#include "SaveFile.h"
#include "RpgGameConstants.h"

ZonePortal::ZonePortal() {
    init();
}

ZonePortal::ZonePortal(int newtextureId, std::vector <int> newTileCoords, int newExitZoneId, std::vector <int> newExitTileCoords) {
    init();
    textureId = newtextureId;
    tileCoords = newTileCoords;
    exitZoneId = newExitZoneId;
    exitTileCoords = newExitTileCoords;
}

ZonePortal::ZonePortal(SaveObject saveObject) {
    init();
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case ZONE_PORTAL_TEXTURE_ID:
            textureId = stoi(saveObject.attributes[i].valueString);
            break;
        case TILE_COORDS:
            tileCoords = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        case EXIT_ZONE_ID:
            exitZoneId = stoi(saveObject.attributes[i].valueString);
            break;
        case EXIT_TILE_COORDS:
            exitTileCoords = getIntVectorFromSaveString(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
}

void ZonePortal::init() {
    textureId = -1;
    exitZoneId = -1;
    tileCoords = { -1, -1 };
    exitTileCoords = { -1, -1 };
}

ZonePortal::~ZonePortal() {
    textureId = 0;
    tileCoords.clear();
    exitZoneId = 0;
    exitTileCoords.clear();
}

std::string ZonePortal::toSaveString() {
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(LOCATION) + "\n";
    saveString += getAttributeString(getUniqueId(), ZONE_PORTAL_TEXTURE_ID, textureId);
    saveString += getAttributeString(getUniqueId(), TILE_COORDS, getIntVectorSaveString(tileCoords));
    saveString += getAttributeString(getUniqueId(), EXIT_ZONE_ID, exitZoneId);
    saveString += getAttributeString(getUniqueId(), EXIT_TILE_COORDS, getIntVectorSaveString(exitTileCoords));
    saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(LOCATION) + "\n";

    return saveString;
}