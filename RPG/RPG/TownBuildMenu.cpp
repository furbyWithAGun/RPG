#include "TownBuildMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"

static const int WIDTH_ADJUSTOR = 38;
static const int HEIGHT_ADJUSTOR = 20;

const int DEFAULT_DESIRED_TILES_DOWN_BUILDING = 30;
const int DEFAULT_DESIRED_TILES_ACROSS_BUILDING = 40;

enum BUILDING_MENU_IDS {
    BUILDINGS_SCROLL_BOX,
    TOWN_BUILD_CANCEL_BUTTON,
    BUILDING_MENU_GOLD_DISPLAY,
    BUILDING_MENU_WOOD_DISPLAY,
    BUILDING_MENU_POP_DISPLAY,
    PROVINCE_BUILDINGS_SCROLL_BOX,
    PROVINCE_TOWN_BUILD_CANCEL_BUTTON,
    PROVINCE_BUILDING_MENU_GOLD_DISPLAY,
    PROVINCE_BUILDING_MENU_WOOD_DISPLAY,
    PROVINCE_BUILDING_MENU_POP_DISPLAY
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
    scene->closeAllMenus();
    GameMenu::open();
    scene->displayHud = false;
    scene->desiredTilesAcross = DEFAULT_DESIRED_TILES_ACROSS_BUILDING;
    scene->desiredTilesDown = DEFAULT_DESIRED_TILES_DOWN_BUILDING;
    scene->resizeTiles();
    scene->player->updateCamera();
    scene->player->cameraFollowPlayer = false;
    townBuildingFor = ((RpgZone*)scene->currentZone)->getNearestTown(scene->player->tileDestination);
}

void TownBuildMenu::draw()
{
    if (townBuildingFor != nullptr && ((RpgZone*)scene->currentZone)->zoneType == ZONE_RPG_TOWN)
    {
        ((MenuText*)getElementbyId(BUILDING_MENU_GOLD_DISPLAY))->setText("Gold: " + std::to_string(scene->player->gold + ((RpgTown*)scene->currentZone)->getTownGold()));
        ((MenuText*)getElementbyId(BUILDING_MENU_WOOD_DISPLAY))->setText("Wood: " + std::to_string(qtyInContainer(ITEM_WOOD, scene->player->inventory) + qtyInContainer(ITEM_WOOD, ((RpgTown*)scene->currentZone)->getTownInventory())));
        ((MenuText*)getElementbyId(BUILDING_MENU_POP_DISPLAY))->setText("Free Population: " + std::to_string(((RpgTown*)scene->currentZone)->getFreePop()))->setdimensions(scene->engine->screenWidth * 0.08, scene->engine->screenHeight * 0.03);
    }
    else if (townBuildingFor != nullptr && ((RpgZone*)scene->currentZone)->zoneType == ZONE_RPG_PROVINCE) {
        ((MenuText*)getElementbyId(PROVINCE_BUILDING_MENU_GOLD_DISPLAY))->setText("Gold: " + std::to_string(scene->player->gold));
        ((MenuText*)getElementbyId(PROVINCE_BUILDING_MENU_WOOD_DISPLAY))->setText("Wood: " + std::to_string(qtyInContainer(ITEM_WOOD, scene->player->inventory)));
        ((MenuText*)getElementbyId(PROVINCE_BUILDING_MENU_POP_DISPLAY))->setText("Free Population: N/A")->setdimensions(scene->engine->screenWidth * 0.08, scene->engine->screenHeight * 0.03);
    }
    GameMenu::draw();
}

void TownBuildMenu::update()
{
    GameMenu::update();
    if (((RpgZone*)scene->currentZone)->zoneType == ZONE_RPG_TOWN) {
        mainPanel->active = true;
        provincePanel->active = false;
    }
    else if (((RpgZone*)scene->currentZone)->zoneType == ZONE_RPG_PROVINCE) {
        mainPanel->active = false;
        provincePanel->active = true;
    }
}

bool TownBuildMenu::handleInput(InputMessage* message)
{
    if (!GameMenu::handleInput(message)) {
        if (message->id == BUTTON_1_OFF)
        {
            cancelBuild();
            return true;
        }
    }
    return false;
}

void TownBuildMenu::buildElements()
{
    mainPanel = new PagedPanel(scene, COLOR_BLACK, xpos, ypos, width, height);
    provincePanel = new PagedPanel(scene, COLOR_BLACK, xpos, ypos, width, height);
    addElement(mainPanel);
    addElement(provincePanel);
    buildPageOne();
    buildProvincePageOne();
}

void TownBuildMenu::init()
{
    scene = nullptr;
}

void TownBuildMenu::buildPageOne()
{
    mainPanel->addElementToPage(0, new MenuText(BUILDING_MENU_GOLD_DISPLAY, scene, "Gold: " + std::to_string(scene->player->gold), { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.01));
    mainPanel->addElementToPage(0, new MenuText(BUILDING_MENU_WOOD_DISPLAY, scene, "Wood: " + std::to_string(qtyInContainer(ITEM_WOOD, scene->player->inventory)), { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.05));
    MenuText* popText = new MenuText(BUILDING_MENU_POP_DISPLAY, scene, "Free Population: " + std::to_string(0), { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.09, scene->engine->screenWidth * 0.08, scene->engine->screenHeight * 0.03);
    popText->setAutoUpdateDimensions(false);
    mainPanel->addElementToPage(0, popText);
    mainPanel->addElementToPage(0, new MenuText(scene, "Buildings", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.15));
    ScrollBox* scroller;
    scroller = new ScrollBox(BUILDINGS_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.19, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
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
        button->addOnClick([this, i, scroller]() {
            if (scene->townCanAffordBuilding(&buildingTemplates[i], (RpgTown*)scene->currentZone))
            {
                scene->buildingBeingPlaced = buildingTemplates[i];
                scene->placingBuilding = true;
            }
            else {
                scroller->selectedElement = nullptr;
            }
            });
        HoverToolTip* toolTip = createBuildBuildingToolTip(&buildingTemplates[i], scene);
        registerToolTip(button, toolTip);
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

void TownBuildMenu::buildProvincePageOne()
{
    provincePanel->addElementToPage(0, new MenuText(PROVINCE_BUILDING_MENU_GOLD_DISPLAY, scene, "Gold: " + std::to_string(scene->player->gold), { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.01));
    provincePanel->addElementToPage(0, new MenuText(PROVINCE_BUILDING_MENU_WOOD_DISPLAY, scene, "Wood: " + std::to_string(qtyInContainer(ITEM_WOOD, scene->player->inventory)), { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.05));
    MenuText* popText = new MenuText(PROVINCE_BUILDING_MENU_POP_DISPLAY, scene, "Free Population: " + std::to_string(0), { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.09, scene->engine->screenWidth * 0.08, scene->engine->screenHeight * 0.03);
    popText->setAutoUpdateDimensions(false);
    provincePanel->addElementToPage(0, popText);
    provincePanel->addElementToPage(0, new MenuText(scene, "Buildings", { 255, 255, 255 }, scene->mainCanvasStartX / 6, engine->screenHeight * 0.15));
    ScrollBox* scroller;
    scroller = new ScrollBox(PROVINCE_BUILDINGS_SCROLL_BOX, scene, { 100, 100, 100 }, engine->screenWidth * 0.01, engine->screenHeight * 0.19, scene->mainCanvasStartX * 0.85, engine->screenHeight * 0.2);
    scroller->numElementsToDisplay = 2;

    for (int i = 0; i < NUM_BUILDING_TYPES; i++)
    {
        MenuButton* button;
        //buildingTemplates.push_back(*createNewBuildingNoId(i, LEFT));
        if (buildingTemplates[i].canBeBuiltOnOverworld())
        {
            button = new MenuButton(scene, buildingTemplates[i].iconTextureId);
            button->xpos = 0;
            button->ypos = 0;
            button->width = engine->screenWidth / WIDTH_ADJUSTOR;
            button->height = engine->screenHeight / HEIGHT_ADJUSTOR;
            button->addOnClick([this, i, scroller]() {
                if (scene->playerCanAffordBuilding(&buildingTemplates[i]))
                {
                    scene->buildingBeingPlaced = buildingTemplates[i];
                    scene->placingBuilding = true;
                }
                else {
                    scroller->selectedElement = nullptr;
                }
                });
            HoverToolTip* toolTip = createBuildBuildingToolTip(&buildingTemplates[i], scene);
            registerToolTip(button, toolTip);
            scroller->addElement(button);
        }
    }

    provincePanel->addElementToPage(0, PROVINCE_BUILDINGS_SCROLL_BOX, scroller);

    MenuButton* cancelButton = new MenuButton(PROVINCE_TOWN_BUILD_CANCEL_BUTTON, scene, BUTTON_BACKGROUND);
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
    provincePanel->addElementToPage(0, PROVINCE_TOWN_BUILD_CANCEL_BUTTON, cancelButton);
}

void TownBuildMenu::cancelBuild()
{
    scene->placingBuilding = false;
    ((ScrollBox*)getElementbyId(BUILDINGS_SCROLL_BOX))->selectedElement = nullptr;
}
