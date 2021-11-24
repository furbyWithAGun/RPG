#pragma once
#include "GameMenu.h"
#include "Item.h"
#include "MenuButton.h"
#include "ScrollBox.h"
#include "MenuText.h"

class RpgOverWorldScene;

class TransferItemsMenu : public GameMenu
{
public:
    //attributes

    //constructors
    TransferItemsMenu();
    TransferItemsMenu(RpgOverWorldScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    TransferItemsMenu(RpgOverWorldScene* gameScene, int newId);
    void open() override;
    void open(std::vector<Item*>* newContainer);
    void open(std::vector<Item*>* newContainer, std::string containerName);
    void draw() override;
    void rebuildElements() override;

    //methods
    bool handleInput(InputMessage* message);
    void transferItemToContainer(Item* itemToTransfer);

private:
    //attributes
    std::string nameOfContainer;
    std::vector<Item*>* container;
    RpgOverWorldScene* scene;

    //methods
    void buildElements();
    void init();

};

