#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"
#include "PagedPanel.h"

class RpgOverWorldScene;
class Building;

class TownBuildMenu : public GameMenu
{
public:
    //attributes
    PagedPanel* mainPanel;
    std::vector<Building> buildingTemplates;

    //constructors
    TownBuildMenu();
    TownBuildMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    void open() override;
    void draw() override;
    void update() override;

    //methods
    bool handleInput(InputMessage* message);

private:
    //attributes
    RpgOverWorldScene* scene;

    //methods
    void buildElements();
    void init();
    void buildPageOne();
};
