#pragma once
#include "GameMenu.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"

class RpgUnit;
class RpgOverWorldScene;

struct EquipmentDisplaySlot;

class OtherUnitInventoryMenu : public GameMenu
{
public:
    //attributes
    std::unordered_map<int, EquipmentDisplaySlot> displaySlots;

    //constructors
    OtherUnitInventoryMenu();
    OtherUnitInventoryMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    OtherUnitInventoryMenu(RpgOverWorldScene* gameScene, int newId);
    void open() override;
    void open(RpgUnit* newUnit);
    void draw() override;
    void rebuildElements() override;
    void setUnit(RpgUnit* newUnit);
    RpgUnit* getSelectedUnit();

    //methods
    bool handleInput(InputMessage* message);

private:
    //attributes
    RpgOverWorldScene* scene;
    RpgUnit* selectedUnit;

    //methods
    void buildElements();
    void defineEquipmentSlots();
    void init();
};

