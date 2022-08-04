#include "TransferItemsMenu.h"
#include "RpgOverWorldScene.h"
#include "Player.h"
#include "inputPrompt.h"

enum TRANSFER_ITEMS_MENU_IDS {
    ITEMS_SCROLL_BOX,
    TRANSFER_ITEMS_CLOSE_BUTTON,
    TRANSFER_ITEMS_TRANSFER_BUTTON,
};

TransferItemsMenu::TransferItemsMenu() : GameMenu()
{
    init();
}

TransferItemsMenu::TransferItemsMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos)
{
    init();
    scene = gameScene;
    buildElements();
}

TransferItemsMenu::TransferItemsMenu(RpgOverWorldScene* gameScene, int newId) : GameMenu(gameScene, newId)
{
    container = nullptr;
    init();
    scene = gameScene;
    width = engine->screenWidth * 0.25;
    height = engine->screenHeight * 0.7;
    xpos = scene->mainCanvasStartX + engine->screenWidth * 0.02;
    ypos = engine->screenHeight * 0.15;
    buildElements();
}

void TransferItemsMenu::open()
{
    GameMenu::open();
    scene->openMenu(INVENTORY_MENU);
    rebuildElements();
    ((ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX))->displayIndex = 0;
}

void TransferItemsMenu::open(std::vector<Item*>* newContainer)
{
    container = newContainer;
    open();
}

void TransferItemsMenu::open(std::vector<Item*>* newContainer, std::string containerName)
{
    nameOfContainer = containerName;
    open(newContainer);
}

void TransferItemsMenu::draw()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    int itemIndex = items->getSelectedElementValue();
    Item* item;

    MenuButton* btnXfer = (MenuButton*)getElementbyId(TRANSFER_ITEMS_TRANSFER_BUTTON);
    btnXfer->active = false;

    if (itemIndex != -1)
    {
        btnXfer->active = true;
    }


    GameMenu::draw();
    for (auto toolTip : toolTips)
    {
        if (toolTip->active) {
            toolTip->draw();
        }
    }
}

void TransferItemsMenu::rebuildElements()
{
    ScrollBox* items = (ScrollBox*)getElementbyId(ITEMS_SCROLL_BOX);
    items->clear();
    for (size_t i = 0; i < toolTips.size(); i++)
    {
        delete toolTips[i];
    }
    toolTips.clear();
    if (container != nullptr)
    {
        for (int i = 0; i < (*container).size(); i++)
        {
            MenuText* txtInvItem = new MenuText(scene, (*container)[i]->name, 0, 0);
            HoverToolTip* toolTip = createItemToolTip((*container)[i], scene);
            registerToolTip(txtInvItem, toolTip);

            if ((*container)[i]->stackSize > 1)
            {
                items->addElement(txtInvItem->setText((*container)[i]->name + " X " + std::to_string((*container)[i]->stackSize)), i);
            }
            else {
                items->addElement(txtInvItem->setText((*container)[i]->name), i);
            }
        }
    }
    
    items->selectedElement = nullptr;
    if (items->subElements.size() <= items->numElementsToDisplay)
    {
        items->displayIndex = 0;
    }

}

bool TransferItemsMenu::handleInput(InputMessage* message)
{
    return GameMenu::handleInput(message);
}

void TransferItemsMenu::transferItemToContainer(Item* itemToTransfer)
{
    addItemToContainer(itemToTransfer, *container);
}

void TransferItemsMenu::buildElements()
{
    ScrollBox* items;
    items = new ScrollBox(ITEMS_SCROLL_BOX, scene, COLOR_GREY, xpos + width * 0.1, ypos + height * 0.4, width * 0.55, height * 0.4);
    items->numElementsToDisplay = 5;
    addElement(ITEMS_SCROLL_BOX, items);

    MenuButton* closeBtn = new MenuButton(TRANSFER_ITEMS_CLOSE_BUTTON, scene, BUTTON_BACKGROUND, xpos + width * 0.1, ypos + height * 0.85);
    closeBtn->setText("Close")->addOnClick([this]() {
        this->close();
        });
    addElement(TRANSFER_ITEMS_CLOSE_BUTTON, closeBtn);

    MenuButton* xferBtn = new MenuButton(TRANSFER_ITEMS_TRANSFER_BUTTON ,scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.45);
    xferBtn->setText("Transfer")->addOnClick([this, items]() {
        int selection = items->getSelectedElementValue();
        if (selection != -1)
        {
            if ((*container)[selection]->stackSize > 1)
            {
                InputPrompt* qtyPrompt = new InputPrompt(scene, "Transfer How Many?", COLOR_BLACK, xpos + width, ypos, scene->engine->screenWidth * 0.2, scene->engine->screenHeight * 0.2);
                qtyPrompt->setInputText(std::to_string((*container)[selection]->stackSize));
                qtyPrompt->addCallBack([selection, this](std::string enteredText) {
                    int numToXfer;
                    if (stringIsAnInt(enteredText))
                    {
                        numToXfer = std::stoi(enteredText);
                    }
                    else {
                        numToXfer = 0;
                    }

                    if (numToXfer >= (*container)[selection]->stackSize)
                    {
                        addItemToContainer((*container)[selection], scene->player->inventory);
                        removeItemFromContainer(selection, *container);
                        //rebuildElements();
                        scene->menus[INVENTORY_MENU]->rebuildMenuElements(); rebuildMenuElements();
                    }
                    else if (numToXfer > 0) {
                        Item* itemToXfer = createNewItem((*container)[selection]->specificType); // relies on fact each item type atm has a unique textureId
                        itemToXfer->stackSize = numToXfer;
                        //scene->addItemsToMap(scene->player->zone, scene->player->tileLocation->x, scene->player->tileLocation->y, { itemToDrop });
                        addItemToContainer(itemToXfer, scene->player->inventory);
                        (*container)[selection]->stackSize -= numToXfer;
                        //rebuildElements();
                        scene->menus[INVENTORY_MENU]->rebuildMenuElements(); 
                        rebuildMenuElements();
                    }
                    });
                scene->addPrompt(qtyPrompt);
            }
            else {
                addItemToContainer((*container)[selection], scene->player->inventory);
                removeItemFromContainer(selection, *container);
                //rebuildElements();
                scene->menus[INVENTORY_MENU]->rebuildMenuElements(); 
                rebuildMenuElements();
            }
        }
        });

    addElement(TRANSFER_ITEMS_TRANSFER_BUTTON, xferBtn);
}

void TransferItemsMenu::init()
{
    nameOfContainer = "";
    container = nullptr;
    scene = nullptr;
}
