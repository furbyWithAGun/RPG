#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"

class RpgOverWorldScene;

struct EquipmentDisplaySlot;
//struct EquipmentDisplaySlot {
//    int x, y, width, height;
//    UiElement icon;
//};

class InventoryMenu : public GameMenu
{
public:
    //attributes
    std::unordered_map<int, EquipmentDisplaySlot> displaySlots;

    //constructors
    InventoryMenu();
    InventoryMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    InventoryMenu(RpgOverWorldScene* gameScene, int newId);
    void open() override;
    void draw() override;
    void rebuildElements() override;

    //methods
    bool handleInput(InputMessage* message);

private:
    //attributes
    RpgOverWorldScene* scene;

    //methods
    void buildElements();
    void defineEquipmentSlots();
    void init();
};

