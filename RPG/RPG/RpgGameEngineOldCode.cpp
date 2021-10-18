//#include "RpgGameEngineOldCode.h"
//#include "RpgGameEngine.h"
//#include <cmath>
//#include "RpgGameButtons.cpp"
//#include "RpgGameMenus.cpp"
//
////global vars
//const int TILE_HEIGHT = 50;
//const int TILE_WIDTH = 50;
//const int DESIRED_TILES_DOWN = 10;
//const int DESIRED_TILES_ACROSS = 19;
//
//const int DEFAULT_FONT_SIZE = 28;
//
//
////methods
//RpgGameEngine::RpgGameEngine() : BaseGameEngine("", 0, 0) {
//    gameState = 0;
//    tileHeight = TILE_HEIGHT;
//    tileWidth = TILE_WIDTH;
//    placingTile = false;
//    tileBeingPlaced = NULL;
//    leftButtonClicked = false;
//    xOffset = yOffset = 0;
//    mainCanvasStartX = 0;
//}
//
//RpgGameEngine::RpgGameEngine(std::string title, int width, int height) : BaseGameEngine(title, width, height) {
//    gameState = 0;
//    tileHeight = TILE_HEIGHT;
//    tileWidth = TILE_WIDTH;
//    placingTile = false;
//    tileBeingPlaced = NULL;
//    mainCanvasStartX = width * LEFT_MENU_SIZE + 1;
//    leftButtonClicked = false;
//    xOffset = yOffset = 0;
//    playerMovingUp = playerMovingDown = playerMovingRight = playerMovingLeft = false;
//}
//
//RpgGameEngine::~RpgGameEngine() {
//    mapTiles.clear();
//    gameState = 0;
//    menus.clear();
//    if (&currentZone != NULL)
//    {
//        //delete &currentZone;
//    }
//    tileHeight = 0;
//    tileWidth = 0;
//    tileBeingPlaced = NULL;
//    mainCanvasStartX = 0;
//    leftButtonClicked = false;
//    xOffset = 0;
//    yOffset = 0;
//    playerMovingUp = playerMovingDown = playerMovingRight = playerMovingLeft = false;
//}
//
//void RpgGameEngine::loadAssets() {
//    //load textures
//    std::unordered_map<int, std::string> texturesToCreate = {
//        {BUTTON_BACKGROUND, "images/buttonBackground.png"},
//        {GRASS, "images/grass.png"},
//        {TREE, "images/tree.png"},
//        {WATER, "images/water.png"},
//        {MOUNTAIN, "images/mountain.png"},
//        {PLAYER, "images/player.png"}
//    };
//
//    createMultipleTextures(texturesToCreate);
//
//    //load fonts
//    mainFont = TTF_OpenFont("fonts/OpenSans-Regular.ttf", DEFAULT_FONT_SIZE);
//}
//
//void RpgGameEngine::createTiles() {
//    //create the different tiles
//    mapTiles[GRASS] = MapTile(true, GRASS);
//    mapTiles[TREE] = MapTile(false, TREE);
//    mapTiles[WATER] = MapTile(false, WATER);
//    mapTiles[MOUNTAIN] = MapTile(false, MOUNTAIN);
//
//
//    //resize tiles depending on screen size
//    int tilesImpliedWidth = screenWidth / DESIRED_TILES_ACROSS;
//    int tilesImpliedHeight = screenHeight / DESIRED_TILES_DOWN;
//    if (tilesImpliedHeight >= tilesImpliedWidth) {
//        tileHeight = tilesImpliedHeight;
//        tileWidth = tilesImpliedHeight;
//    }
//    else {
//        tileHeight = tilesImpliedWidth;
//        tileWidth = tilesImpliedWidth;
//    }
//
//    for (auto i = mapTiles.begin(); i != mapTiles.end(); i++) {
//        textures[i->second.textureKey].resize(tileHeight, tileWidth);
//    }
//}
//
//void RpgGameEngine::setUpGame() {
//
//    gameState = LEVEL_DESIGN;
//
//    createTiles();
//
//    SaveFile firstZoneFile = SaveFile("zoneOne.txt");
//    firstZoneFile.loadFile();
//    currentZone = ZoneMap(firstZoneFile.objects[0].rawString);
//
//    ZoneBuilderMenu* zoneBuildMenu = new ZoneBuilderMenu(this, BUILD_MENU, screenWidth * LEFT_MENU_SIZE, screenHeight, 0, 0);
//    zoneBuildMenu->isActive = true;
//
//    menus[BUILD_MENU] = zoneBuildMenu;
//
//    //resize player texture to match tile size
//    textures[PLAYER].resize(tileHeight, tileWidth);
//    //printf("%i, %i", textures[PLAYER].height);
//    player = Player(&textures[PLAYER], this);
//    int screenCoords[2];
//    coordsFromTileIndex(DESIRED_TILES_ACROSS / 2, DESIRED_TILES_DOWN / 2, screenCoords);
//    playerScreenX = screenCoords[0];
//    playerScreenY = screenCoords[1];
//    player.setStartLocation(DESIRED_TILES_ACROSS / 2, DESIRED_TILES_DOWN / 2);
//}
//
//std::string RpgGameEngine::getSaveString() {
//    std::string returnString = "";
//    returnString += currentZone.toSaveString();
//    return returnString;
//}
//
//void RpgGameEngine::handleInput() {
//    SDL_Event e;
//    int x, y;
//    int k[2];
//
//    SDL_GetMouseState(&x, &y);
//    if (gameState == LEVEL_DESIGN)
//    {
//        if (x < screenWidth * 0.01) {
//            xOffset += 2;
//        }
//        if (x > screenWidth * 0.99) {
//            xOffset -= 2;
//        }
//        if (y < screenHeight * 0.01) {
//            yOffset += 2;
//        }
//        if (y > screenHeight * 0.99) {
//            yOffset -= 2;
//        }
//    }
//
//    //Handle events on queue
//    while (SDL_PollEvent(&e) != 0)
//    {
//        for (auto menu : menus)
//        {
//            if (menu.second->isActive)
//            {
//                menu.second->handleEvent(&e);
//            }
//        }
//        switch (e.type)
//        {
//        case SDL_QUIT:
//            gameRunning = false;
//            break;
//        case SDL_MOUSEBUTTONDOWN:
//            switch (e.button.button)
//            {
//            case SDL_BUTTON_LEFT:
//                leftButtonClicked = true;
//                if (placingTile)
//                {
//                    if (coordsAreOnDisplayedMapTile(x, y))
//                    {
//                        getTileIndexFromScreenCoords(x, y, k);
//                        currentZone.tileMap[k[1]][k[0]] = tileBeingPlaced->textureKey;
//                    }
//                }
//                break;
//            default:
//                break;
//            }
//
//            break;
//        case SDL_MOUSEBUTTONUP:
//            switch (e.button.button)
//            {
//            case SDL_BUTTON_LEFT:
//                leftButtonClicked = false;
//                break;
//            default:
//                break;
//            }
//            break;
//        case SDL_MOUSEMOTION:
//            SDL_GetMouseState(&x, &y);
//            if (placingTile)
//            {
//                if (coordsAreOnDisplayedMapTile(x, y) && leftButtonClicked)
//                {
//                    getTileIndexFromScreenCoords(x, y, k);
//                    currentZone.tileMap[k[1]][k[0]] = tileBeingPlaced->textureKey;
//                }
//            }
//            break;
//        case SDL_KEYDOWN:
//            switch (e.key.keysym.sym) {
//            case SDLK_w:
//                playerMovingUp = true;
//                break;
//            case SDLK_s:
//                playerMovingDown = true;
//                break;
//            case SDLK_a:
//                playerMovingLeft = true;
//                break;
//            case SDLK_d:
//                playerMovingRight = true;
//                break;
//            }
//            break;
//        case SDL_KEYUP:
//            switch (e.key.keysym.sym) {
//            case SDLK_w:
//                playerMovingUp = false;
//                break;
//            case SDLK_s:
//                playerMovingDown = false;
//                break;
//            case SDLK_a:
//                playerMovingLeft = false;
//                break;
//            case SDLK_d:
//                playerMovingRight = false;
//                break;
//            }
//            break;
//        default:
//            break;
//        }
//    }
//}
//
//void RpgGameEngine::gameLogic() {
//    x++;
//    //printf("%i\n", x);
//    double rate = SDL_GetTicks() / 1000;
//    printf("%f\n", (double)x / rate);
//
//    if (playerMovingUp && !playerMovingDown && isTilePassable(player.tileLocation[0], player.tileLocation[1] - 1)) {
//        player.startMovement(MOVE_UP);
//    }
//    else if (playerMovingDown && !playerMovingUp && isTilePassable(player.tileLocation[0], player.tileLocation[1] + 1)) {
//        player.startMovement(MOVE_DOWN);
//    }
//    else if (playerMovingRight && !playerMovingLeft && isTilePassable(player.tileLocation[0] + 1, player.tileLocation[1])) {
//        player.startMovement(MOVE_RIGHT);
//    }
//    else if (playerMovingLeft && !playerMovingRight && isTilePassable(player.tileLocation[0] - 1, player.tileLocation[1])) {
//        player.startMovement(MOVE_LEFT);
//    }
//    player.updatePlayer();
//}
//
//void RpgGameEngine::gameRendering() {
//    //clear screen
//    SDL_SetRenderDrawColor(getMainRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
//    SDL_RenderClear(getMainRenderer());
//
//    //fill screen with water
//    for (size_t i = 0; i * tileHeight <= screenHeight + tileHeight; i++)
//    {
//        for (size_t j = 0; j * tileWidth <= screenWidth + tileWidth; j++) {
//            renderTexture(textures[WATER], ((tileWidth * j) + screenWidth * LEFT_MENU_SIZE) + (xOffset % tileWidth) - tileWidth, tileHeight * i + (yOffset % tileHeight) - tileHeight);
//        }
//    }
//
//    //draw zone
//    for (int i = 0; i < currentZone.tileMap.size(); i++) {
//        for (int j = 0; j < currentZone.tileMap[i].size(); j++) {
//            renderTexture(textures[mapTiles[currentZone.tileMap[i][j]].textureKey], (tileWidth * j) + screenWidth * LEFT_MENU_SIZE + xOffset, tileHeight * i + yOffset);
//        }
//    }
//
//    //draw tile being placed
//    if (placingTile)
//    {
//        int x, y;
//        int k[2], l[2];
//        SDL_GetMouseState(&x, &y);
//        getTileIndexFromScreenCoords(x, y, k);
//        coordsFromTileIndex(k[0], k[1], l);
//        if (coordsAreOnDisplayedMapTile(x, y)) {
//            renderTexture(textures[tileBeingPlaced->textureKey], l[0], l[1]);
//        }
//    }
//
//    //draw menus
//    for (auto menu : menus)
//    {
//        if (menu.second->isActive)
//        {
//            menu.second->draw();
//        }
//    }
//
//    //draw player
//    player.draw();
//
//    //Update screen
//    SDL_RenderPresent(getMainRenderer());
//}
//
//void RpgGameEngine::getTileIndexFromScreenCoords(int x, int y, int tileIndices[2]) {
//    tileIndices[0] = floor(((x - xOffset - screenWidth * LEFT_MENU_SIZE)) / tileWidth);
//    tileIndices[1] = floor((y - yOffset) / tileHeight);
//}
//
//void RpgGameEngine::coordsFromTileIndex(int x, int y, int returnCoords[2]) {
//    returnCoords[0] = x * tileWidth + LEFT_MENU_SIZE * screenWidth + xOffset;
//    returnCoords[1] = y * tileHeight + yOffset;
//}
//
//bool RpgGameEngine::coordsAreOnDisplayedMapTile(int x, int y) {
//    int k[2];
//    getTileIndexFromScreenCoords(x, y, k);
//    return ((mainCanvasStartX <= x) && (k[0] >= 0) && (k[0] < currentZone.tileMap[0].size()) && (k[1] >= 0) && (k[1] < currentZone.tileMap.size()));
//}
//
//bool RpgGameEngine::isTilePassable(int x, int y) {
//    if (x < 0 || y < 0 || y >= currentZone.tileMap.size() || x >= currentZone.tileMap[y].size())
//    {
//        return false;
//    }
//    return mapTiles[currentZone.tileMap[y][x]].passable;
//}