#include "EquippedMenu.h"
#include "RpgOverWorldScene.h"

enum EQUIPPED_MENU_IDS {
    SLOTS_SCROLL_BOX,
    EQUIPPED_CLOSE_BUTTON,
    UNEQUIP_GEAR_BUTTON
};

const int INV_EQUIP_ID_START = 10000;

std::unordered_map<int, std::string> equipSlotDisplayText = {
    {HEAD_SLOT, "Head"},
    {NECK_SLOT, "Neck"},
    {SHOULDERS_SLOT, "Shoulders"},
    {BODY_SLOT, "Body"},
    {ARMS_SLOT, "Arms"},
    {HANDS_SLOT, "Hands"},
    {LEFT_HAND, "Left Hand"},
    {RIGHT_HAND, "Right Hand"},
    {LEFT_RING_SLOT, "Left Ring"},
    {RIGHT_RING_SLOT, "Right Ring"},
    {BELT_SLOT, "Belt"},
    {LEGS_SLOT, "Legs"},
    {FEET_SLOT, "Feet"} };

EquippedMenu::EquippedMenu() : GameMenu()
{
    init();
}

EquippedMenu::EquippedMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

void EquippedMenu::buildElements()
{
    ScrollBox* slots;
    slots = new ScrollBox(SLOTS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.1, width * 0.6, height * 0.7);
    slots->numElementsToDisplay = 5;

    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        if (scene->player->equippedItems[i] != nullptr)
        {
            slots->addElement(new MenuText(this->scene, equipSlotDisplayText[i] + ": " + scene->player->equippedItems[i]->name, COLOR_WHITE, xpos + width * 0.1, ypos + height * i * 0.1), i);
        }
        else {
            slots->addElement(new MenuText(INV_EQUIP_ID_START + i, this->scene, equipSlotDisplayText[i] + ": Nothing", COLOR_DARK_GREY, xpos + width * 0.1, ypos + height * i * 0.1), i);
        }
    }
    addElement(SLOTS_SCROLL_BOX, slots);

    MenuButton* closeBtn = new MenuButton(EQUIPPED_CLOSE_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.1, ypos + height * 0.85);
    closeBtn->setText("Close")->addOnClick([this]() {
        this->close();
        });
    addElement(EQUIPPED_CLOSE_BUTTON, closeBtn);

    MenuButton* unequipBtn = new MenuButton(UNEQUIP_GEAR_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.45);
    unequipBtn->setText("Unequip")->addOnClick([this, slots]() {
        scene->player->inventory.push_back(scene->player->equippedItems[slots->getSelectedElementValue()]);
        scene->player->equippedItems[slots->getSelectedElementValue()] = nullptr;
        update();
        scene->menus[INVENTORY_MENU]->update();
        });
    addElement(UNEQUIP_GEAR_BUTTON, unequipBtn);
}

void EquippedMenu::init()
{
    scene = nullptr;
}

void EquippedMenu::open()
{
    GameMenu::open();
}

void EquippedMenu::draw()
{
    GameMenu::draw();
}

void EquippedMenu::update()
{
    ScrollBox* slots = (ScrollBox*) getElementbyId(SLOTS_SCROLL_BOX);
    slots->clear();
    for (int i = BARE_HANDS + 1; i != NUM_EQUIPMENT_SLOTS; i++)
    {
        if (scene->player->equippedItems[i] != nullptr)
        {
            slots->addElement(new MenuText(this->scene, equipSlotDisplayText[i] + ": " + scene->player->equippedItems[i]->name, COLOR_WHITE, xpos + width * 0.1, ypos + height * i * 0.1), i);
        }
        else {
            slots->addElement(new MenuText(INV_EQUIP_ID_START + i, this->scene, equipSlotDisplayText[i] + ": Nothing", COLOR_DARK_GREY, xpos + width * 0.1, ypos + height * i * 0.1), i);
        }
    }
    slots->selectedElement = nullptr;
}

bool EquippedMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}
