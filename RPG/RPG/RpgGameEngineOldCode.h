#pragma once
#include "BaseGameEngine.h"
#include "ZoneMap.h"
#include "GameMenu.h"
#include "Player.h"

enum GAME_STATES {
    MAIN_MENU,
    OVERWORLD,
    LEVEL_DESIGN,
    BUILDING,
    COMBAT
};

enum TEXTURE_NAMES
{
    GRASS,
    TREE,
    WATER,
    MOUNTAIN,
    NUM_TEXTURES,
    BUTTON_BACKGROUND,
    PLAYER
};

enum CLASS_IDS {
    ZONE_PORTAL,
    ZONE_MAP
};

enum MENUS {
    BUILD_MENU
};

class RpgGameEngine : public BaseGameEngine
{
public:
    //attributes
    std::unordered_map<int, MapTile> mapTiles;
    int gameState;
    std::unordered_map<int, GameMenu*> menus;
    ZoneMap currentZone;
    int tileHeight;
    int tileWidth;
    bool placingTile;
    MapTile* tileBeingPlaced;
    int mainCanvasStartX;
    bool leftButtonClicked;
    int xOffset;
    int yOffset;
    int x = 0;
    Player player;
    bool playerMovingUp, playerMovingDown, playerMovingRight, playerMovingLeft;
    int playerScreenX, playerScreenY;

    //contructor
    RpgGameEngine();
    RpgGameEngine(std::string title, int width, int height);

    //deconstructor
    ~RpgGameEngine();

    //methods
    void setUpGame();
    void loadAssets() override;
    void handleInput() override;
    void gameLogic() override;
    void gameRendering() override;
    void getTileIndexFromScreenCoords(int x, int y, int tileIndices[2]);
    void coordsFromTileIndex(int x, int y, int returnCoords[2]);
    std::string getSaveString();
    bool coordsAreOnDisplayedMapTile(int x, int y);
    bool isTilePassable(int x, int y);

private:
    //attributes

    //methods
    void drawMenu();
    void createTiles();
};
