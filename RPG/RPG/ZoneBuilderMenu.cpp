#include "ZoneBuilderMenu.h"
//constants
static const int WIDTH_ADJUSTOR = 38;
static const int HEIGHT_ADJUSTOR = 20;


enum SAVE_BUILDER_MENU_IDS {
    LOAD_BUTTON,
    TILE_SCROLL_BOX,
    NEW_ZONE_BUTTON,
    PORTAL_SCROLL_BOX,
    BACKGROUND_TILE_SCROLL_BOX,
    MOB_SPAWN_SCROLL_BOX,
    MOB_SPAWN_BUTTON_TRUE,
    MOB_SPAWN_BUTTON_FALSE,
    TXT_DIFFICULTY,
    TXT_ZONE_TYPE,
    BUILDINGS_SCROLL_BOX,
    DOODADS_SCROLL_BOX,
    UNITS_SCROLL_BOX,
    QUIT_BUTTON
};

//constructors
ZoneBuilderMenu::ZoneBuilderMenu() : GameMenu() {
    scene = NULL;
}

ZoneBuilderMenu::ZoneBuilderMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos) {
    scene = gameScene;
    buildElements();
    updateMobSpawnButton();
    updateDifficultyText();
    updateZoneTypeText();
}

void ZoneBuilderMenu::close()
{
}

//public methods
bool ZoneBuilderMenu::handleInput(InputMessage* message) {
    ScrollBox* scroller;
    switch (message->id)
    {
    case BUTTON_1_ON:
        scene->placingTile = false;
        scene->placingPortal = false;
        scene->placingBuilding = false;
        scene->placingDooDad = false;
        scene->placingUnit = false;
        scroller = (ScrollBox*)getElementbyId(TILE_SCROLL_BOX);
        scroller->selectedElement = NULL;
        scroller = (ScrollBox*)getElementbyId(PORTAL_SCROLL_BOX);
        scroller->selectedElement = NULL;
        scroller = (ScrollBox*)getElementbyId(BUILDINGS_SCROLL_BOX);
        scroller->selectedElement = NULL;
        scroller = (ScrollBox*)getElementbyId(DOODADS_SCROLL_BOX);
        scroller->selectedElement = NULL;
        scroller = (ScrollBox*)getElementbyId(UNITS_SCROLL_BOX);
        scroller->selectedElement = NULL;
        break;
    default:
        break;
    }

    return GameMenu::handleInput(message);
}

void ZoneBuilderMenu::updateMobSpawnButton()
{
    if (&scene->sceneToEdit != nullptr)
    {
        if (scene->sceneToEdit.mobSpawn)
        {
            ((ScrollBox*)getElementbyId(MOB_SPAWN_SCROLL_BOX))->selectedElement = getElementbyId(MOB_SPAWN_BUTTON_TRUE);
        }
        else {
            ((ScrollBox*)getElementbyId(MOB_SPAWN_SCROLL_BOX))->selectedElement = getElementbyId(MOB_SPAWN_BUTTON_FALSE);
        }
    } 
}

void ZoneBuilderMenu::updateDifficultyText()
{
    if (&scene->sceneToEdit != nullptr)
    {
        ((TextBox*)getElementbyId(TXT_DIFFICULTY))->setText(std::to_string((scene->sceneToEdit).difficulty));
    }
}

void ZoneBuilderMenu::setZoneDifficulty()
{
    scene->sceneToEdit.difficulty = std::stoi(getElementbyId(TXT_DIFFICULTY)->getText());
}

void ZoneBuilderMenu::updateZoneTypeText()
{
    if (&scene->sceneToEdit != nullptr)
    {
        ((TextBox*)getElementbyId(TXT_ZONE_TYPE))->setText(std::to_string(scene->sceneToEdit.zoneType));
    }
}

void ZoneBuilderMenu::setZoneType()
{
    scene->sceneToEdit.zoneType = std::stoi(getElementbyId(TXT_ZONE_TYPE)->getText());
}


//private methods
void ZoneBuilderMenu::buildElements() {

    mainPanel = new PagedPanel(scene, COLOR_BLACK, xpos, ypos, width, height);
    addElement(mainPanel);
    buildPageOne();
    buildPageTwo();
    buildPageThree();
}

void ZoneBuilderMenu::buildPageOne()
{
    mainPanel->addElementToPage(0, new MenuText(scene, "Tiles", { 255, 255, 255 }, scene->mainCanvasStartX / 4, engine->screenHeight * 0.01));
    mainPanel->addElementToPage(0, new MenuText(scene, "Portals", { 255, 255, 255 }, scene->mainCanvasStartX / 4, engine->screenHeight * 0.4));
    ScrollBox* scroller;
    scroller = new ScrollBox(TILE_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.05, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    scroller->numElementsToDisplay = 3;

    for (auto i = scene->mapTiles.begin(); i != scene->mapTiles.end(); i++)
    {
        MapBuilderTileButton* button;
        button = new MapBuilderTileButton(scene, &i->second);
        button->xpos = 0;
        button->ypos = 0;
        scroller->addElement(button);
    }


    mainPanel->addElementToPage(0, TILE_SCROLL_BOX, scroller);

    ScrollBox* portalScroller;
    portalScroller = new ScrollBox(TILE_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.45, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    portalScroller->numElementsToDisplay = 2;

    int x = 0;
    for (int i = 0; i < scene->zonePortalImages.size(); i++)
    {
        MapBuilderPortalButton* button;
        button = new MapBuilderPortalButton(scene, scene->zonePortalImages[i]);
        button->xpos = button->width / 2 + button->width * (x % 2) + button->width * (x % 2);
        button->ypos = (button->height * floor(x / 2) + button->height * floor(x / 2)) + engine->screenHeight * 0.45;
        portalScroller->addElement(button);
        x++;
    }

    mainPanel->addElementToPage(0, PORTAL_SCROLL_BOX, portalScroller);

    SaveMapBuilderButton* button = new SaveMapBuilderButton(scene, BUTTON_BACKGROUND);
    button->xpos = width * 0.2;
    button->ypos = height * 0.69;
    button->setText("Save Map");
    mainPanel->addElementToPage(0, button);

    MenuButton* loadButton = new MenuButton(LOAD_BUTTON, this->scene, BUTTON_BACKGROUND, width * 0.2, height * 0.76);
    loadButton->setText("Load Map")->addOnClick([this] {
        scene->openMenu(LOAD_ZONE_MENU);
        });
    mainPanel->addElementToPage(0, LOAD_BUTTON, loadButton);

    MenuButton* newZoneButton = new MenuButton(NEW_ZONE_BUTTON, this->scene, BUTTON_BACKGROUND, width * 0.2, height * 0.83);
    newZoneButton->setText("New Map")->addOnClick([this] {
        //scene->createNewZone();
        scene->openMenu(WORLD_BUILDING_NEW_ZONE_MENU);
        });
    mainPanel->addElementToPage(0, NEW_ZONE_BUTTON, newZoneButton);

    MenuButton* quitButton = new MenuButton(QUIT_BUTTON, this->scene, BUTTON_BACKGROUND, width * 0.2, height * 0.9);
    quitButton->setText("Quit")->addOnClick([this] {
        scene->engine->setNextScene(MAIN_MENU_SCENE);
        scene->endScene();
        });
    mainPanel->addElementToPage(0, QUIT_BUTTON, quitButton);

}

void ZoneBuilderMenu::buildPageTwo()
{
    mainPanel->addElementToPage(1, new MenuText(scene, "Background", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.01));
    ScrollBox* scroller;
    scroller = new ScrollBox(BACKGROUND_TILE_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.05, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    scroller->numElementsToDisplay = 2;

    for (auto i = scene->mapTiles.begin(); i != scene->mapTiles.end(); i++)
    {
        MenuButton* button;
        button = new MenuButton(scene, i->second.textureKey);
        button->xpos = 0;
        button->ypos = 0;
        button->width = engine->screenWidth / WIDTH_ADJUSTOR;
        button->height = engine->screenHeight / HEIGHT_ADJUSTOR;
        button->addOnClick([this, i]() {
            scene->sceneToEdit.backGroundTile = i->second.textureKey;
            });
        scroller->addElement(button);
    }

    mainPanel->addElementToPage(1, BACKGROUND_TILE_SCROLL_BOX, scroller);

    mainPanel->addElementToPage(1, new MenuText(scene, "Mobs Spawn", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.4));
    ScrollBox* mobSpawnScroller;
    mobSpawnScroller = new ScrollBox(MOB_SPAWN_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.45, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    mobSpawnScroller->numElementsToDisplay = 2;
    
    MenuButton* trueButton;
    trueButton = new MenuButton(scene, 0, 0);
    trueButton->id = MOB_SPAWN_BUTTON_TRUE;
    trueButton->setText("True")->addOnClick([this]() {
        scene->sceneToEdit.mobSpawn = true;
        });
    mobSpawnScroller->addElement(trueButton);

    MenuButton* falseButton;
    falseButton = new MenuButton(scene, 0, 0);
    falseButton->id = MOB_SPAWN_BUTTON_FALSE;
    falseButton->setText("False")->addOnClick([this]() {
        scene->sceneToEdit.mobSpawn = false;
        });
    mobSpawnScroller->addElement(falseButton);

    mainPanel->addElementToPage(1, MOB_SPAWN_SCROLL_BOX, mobSpawnScroller);

    mainPanel->addElementToPage(1, new MenuText(scene, "Difficulty", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.7));
    TextBox* txtDifficulty = new TextBox(TXT_DIFFICULTY, scene, scene->mainCanvasStartX / 6, engine->screenHeight * 0.75, scene->mainCanvasStartX / 2, engine->screenHeight * 0.04);
    mainPanel->addElementToPage(1, txtDifficulty);

    mainPanel->addElementToPage(1, new MenuText(scene, "Zone Type", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.8));
    TextBox* txtZoneType = new TextBox(TXT_ZONE_TYPE, scene, scene->mainCanvasStartX / 6, engine->screenHeight * 0.85, scene->mainCanvasStartX / 2, engine->screenHeight * 0.04);
    mainPanel->addElementToPage(1, txtZoneType);
}

void ZoneBuilderMenu::buildPageThree()
{
    // buildings scroller
    mainPanel->addElementToPage(2, new MenuText(scene, "Buildings", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.01));
    ScrollBox* buildingScroller;
    buildingScroller = new ScrollBox(BUILDINGS_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.05, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    buildingScroller->numElementsToDisplay = 2;

    for (int i = 0; i < NUM_BUILDING_TYPES; i++)
    {
        MenuButton* button;
        buildingTemplates.push_back(*createNewBuildingNoId(i, LEFT));
        button = new MenuButton(scene, buildingTemplates[i].iconTextureId);
        button->xpos = 0;
        button->ypos = 0;
        button->width = engine->screenWidth / WIDTH_ADJUSTOR;
        button->height = engine->screenHeight / HEIGHT_ADJUSTOR;
        button->addOnClick([this, i]() {
            scene->buildingBeingPlaced = buildingTemplates[i];
            scene->placingBuilding = true;
            scene->placingDooDad = false;
            scene->placingTile = false;
            scene->placingPortal = false;
            scene->placingUnit = false;
            });
        buildingScroller->addElement(button);
    }

    mainPanel->addElementToPage(2, BUILDINGS_SCROLL_BOX, buildingScroller);

    //doodads scroller
    mainPanel->addElementToPage(2, new MenuText(scene, "DooDads", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.4));
    ScrollBox* dooDadScroller;
    dooDadScroller = new ScrollBox(DOODADS_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.45, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    dooDadScroller->numElementsToDisplay = 2;

    for (int i = 0; i < NUM_DOODAD_TYPES; i++)
    {
        if (i != DOODAD_UNIT_SPAWNER)
        {
            MenuButton* button;
            DooDadTemplates.push_back(*createNewDooDad(i, scene, scene->sceneToEdit.id));
            button = new MenuButton(scene, DooDadTemplates[i].textureKey);
            button->xpos = 0;
            button->ypos = 0;
            button->width = engine->screenWidth / WIDTH_ADJUSTOR;
            button->height = engine->screenHeight / HEIGHT_ADJUSTOR;
            button->addOnClick([this, i]() {
                scene->dooDadgBeingPlaced = DooDadTemplates[i];
                scene->placingUnit = false;
                scene->placingDooDad = true;
                scene->placingBuilding = false;
                scene->placingTile = false;
                scene->placingPortal = false;
                });
            dooDadScroller->addElement(button);
        }
    }

    mainPanel->addElementToPage(2, DOODADS_SCROLL_BOX, dooDadScroller);

    //units sroller
    mainPanel->addElementToPage(2, new MenuText(scene, "units", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.65));
    ScrollBox* unitScroller;
    unitScroller = new ScrollBox(UNITS_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.7, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    unitScroller->numElementsToDisplay = 2;

    for (int i = 0; i < NUM_UNIT_TYPES; i++)
    {
        unitTemplates.push_back(*createNewUnitBlankId(&this->scene->sceneToEdit, this->scene, i));
        MenuButton* button;
        if (i != PLAYER)
        {
            button = new MenuButton(scene, unitTemplates[i].animations[IDLE_DOWN].spriteSheetKey);
            button->xpos = 0;
            button->ypos = 0;
            button->width = engine->screenWidth / WIDTH_ADJUSTOR;
            button->height = engine->screenHeight / HEIGHT_ADJUSTOR;
            button->addOnClick([this, i]() {
                scene->unitBeingPlaced = unitTemplates[i];
                scene->placingUnit = true;
                scene->placingBuilding = false;
                scene->placingDooDad = false;
                scene->placingTile = false;
                scene->placingPortal = false;
                });
            unitScroller->addElement(button);
        }
    }

    mainPanel->addElementToPage(2, UNITS_SCROLL_BOX, unitScroller);
}
