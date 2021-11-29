#include "TownBuildMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"

static const int WIDTH_ADJUSTOR = 38;
static const int HEIGHT_ADJUSTOR = 20;

const int DEFAULT_DESIRED_TILES_DOWN_BUILDING = 30;
const int DEFAULT_DESIRED_TILES_ACROSS_BUILDING = 40;

enum INVENTORY_MENU_IDS {
    BUILDINGS_SCROLL_BOX,
    TOWN_BUILD_CANCEL_BUTTON
};

TownBuildMenu::TownBuildMenu() : GameMenu()
{
    init();
}

TownBuildMenu::TownBuildMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

void TownBuildMenu::open()
{
    GameMenu::open();
    scene->displayHud = false;
    scene->desiredTilesAcross = DEFAULT_DESIRED_TILES_ACROSS_BUILDING;
    scene->desiredTilesDown = DEFAULT_DESIRED_TILES_DOWN_BUILDING;
    scene->resizeTiles();
    scene->player->updateCamera();
    scene->player->cameraFollowPlayer = false;
}

void TownBuildMenu::draw()
{
    GameMenu::draw();
}

void TownBuildMenu::update()
{
    GameMenu::update();
}

bool TownBuildMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void TownBuildMenu::buildElements()
{
    mainPanel = new PagedPanel(scene, COLOR_BLACK, xpos, ypos, width, height);
    addElement(mainPanel);
    buildPageOne();
}

void TownBuildMenu::init()
{
    scene = nullptr;
}

void TownBuildMenu::buildPageOne()
{
    mainPanel->addElementToPage(0, new MenuText(scene, "Buildings", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.01));
    ScrollBox* scroller;
    scroller = new ScrollBox(BUILDINGS_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.05, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    scroller->numElementsToDisplay = 2;

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
            if (scene->canAffordBuilding(&buildingTemplates[i], (RpgTown*)scene->currentZone))
            {
                scene->buildingBeingPlaced = buildingTemplates[i];
                scene->placingBuilding = true;
            }
            });
        scroller->addElement(button);
    }

    mainPanel->addElementToPage(0, BUILDINGS_SCROLL_BOX, scroller);

    MenuButton* cancelButton = new MenuButton(TOWN_BUILD_CANCEL_BUTTON, scene, BUTTON_BACKGROUND);
    cancelButton->setText("Cancel")->addOnClick([this]() {
        close();
        scene->placingBuilding = false;
        scene->openMenu(RPG_OVERWORLD_MENU);
        scene->displayHud = true;
        scene->player->cameraFollowPlayer = true;
        scene->desiredTilesAcross = DEFAULT_DESIRED_TILES_ACROSS;
        scene->desiredTilesDown = DEFAULT_DESIRED_TILES_DOWN;
        scene->resizeTiles();
        });
    cancelButton->xpos = engine->screenWidth * 0.01;
    cancelButton->ypos = engine->screenHeight * 0.8;
    mainPanel->addElementToPage(0, TOWN_BUILD_CANCEL_BUTTON, cancelButton);
}
