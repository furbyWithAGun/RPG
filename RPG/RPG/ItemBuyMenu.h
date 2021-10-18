#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"

class RpgOverWorldScene;
class ItemShop;
class Item;

class ItemBuyMenu : public GameMenu
{
public:
    //constructors
    ItemBuyMenu();
    ItemBuyMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    void open() override;
    void draw() override;
    void update() override;

    //methods
    bool handleInput(InputMessage* message);
    void setItemShop(ItemShop* newItemShop);


private:
    //attributes
    RpgOverWorldScene* scene;
    ItemShop* itemShop;

    //methods
    void buildElements();
    void init();
};

