#include "LoadZoneMenu.h"
#include "RpgWorldBuilderScene.h"

enum LOAD_ZONE_MENU_IDS {
    LOAD_ZONE_LABEL,
    ZONES_SCROLL_BOX,
    ZONE_LOAD_BUTTON,
    LOAD_ZONE_CANCEL_BUTTON,
    LOAD_ZONE_DELETE_BUTTON
};

LoadZoneMenu::LoadZoneMenu() : GameMenu() {
    init();
}

LoadZoneMenu::LoadZoneMenu(RpgWorldBuilderScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos) {
    init();
    scene = gameScene;
    buildElements();
}

void LoadZoneMenu::open()
{   
    scene->closeAllMenus();
    GameMenu::open();
    //ScrollBox* scroller = (ScrollBox*) getElementbyId(ZONES_SCROLL_BOX);
    //scroller->selectedElement = NULL;
    delete elements[ZONES_SCROLL_BOX];
    elements.erase(ZONES_SCROLL_BOX);
    ScrollBox* scroller;
    scroller = new ScrollBox(ZONES_SCROLL_BOX, scene, { 100, 100, 100 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.15, width * 0.5, height * 0.6);
    scroller->numElementsToDisplay = 4;

    for (auto zone : scene->getZones())
    {
        MenuText* zoneName = new MenuText(scene, zone.second->zoneName, 0, 0);
        zoneName->setBackground({ 100, 100, 100 });
        scroller->addElement(zoneName, zone.second->id);
    }
    addElement(ZONES_SCROLL_BOX, scroller);
}

void LoadZoneMenu::buildElements()
{
    //label
    addElement(LOAD_ZONE_LABEL, new MenuText(LOAD_ZONE_LABEL, scene, "Load Zone", { 255, 255, 255 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.015));

    //Zones scrollbox
    ScrollBox* scroller;
    scroller = new ScrollBox(ZONES_SCROLL_BOX, scene, { 100, 100, 100 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.15, width * 0.5 , height * 0.6);
    scroller->numElementsToDisplay = 4;

    for (auto zone : scene->getZones())
    {
        MenuText* zoneName = new MenuText(scene, zone.second->zoneName, 0, 0);
        zoneName->setBackground({ 100, 100, 100 });
        scroller->addElement(zoneName, zone.second->id);
    }

    addElement(ZONES_SCROLL_BOX, scroller);

    //load button
    MenuButton* loadButton = new MenuButton(ZONE_LOAD_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + (width - width * 0.8) / 2, ypos + height * 0.8);
    loadButton->setText("Load")->addOnClick([this]() {
        ScrollBox* scroller = (ScrollBox*) getElementbyId(ZONES_SCROLL_BOX);
        scene->setCurrentZone(scroller->getSelectedElementValue());
        close();
        });
    addElement(ZONE_LOAD_BUTTON, loadButton);

    //Cancel button
    MenuButton* cancelButton = new MenuButton(ZONE_LOAD_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + width * 0.5, ypos + height * 0.8);
    cancelButton->setText("Cancel")->addOnClick([this]() {
        close();
        });
    addElement(LOAD_ZONE_CANCEL_BUTTON, cancelButton);

    //Delete button
    MenuButton* deleteButton = new MenuButton(LOAD_ZONE_DELETE_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + width * 0.7, ypos + height * 0.4);
    deleteButton->setText("Delete")->addOnClick([this]() {
        ScrollBox* oldScroller = (ScrollBox*)getElementbyId(ZONES_SCROLL_BOX);
        scene->deleteZone(oldScroller->getSelectedElementValue());
        scene->saveZones("zones.txt");
        delete elements[ZONES_SCROLL_BOX];
        elements.erase(ZONES_SCROLL_BOX);
        ScrollBox* scroller;
        scroller = new ScrollBox(ZONES_SCROLL_BOX, scene, { 100, 100, 100 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.15, width * 0.5, height * 0.6);
        scroller->numElementsToDisplay = 4;

        for (auto zone : scene->getZones())
        {
            MenuText* zoneName = new MenuText(scene, zone.second->zoneName, 0, 0);
            zoneName->setBackground({ 100, 100, 100 });
            scroller->addElement(zoneName, zone.second->id);
        }
        addElement(ZONES_SCROLL_BOX, scroller);
        });
    addElement(LOAD_ZONE_DELETE_BUTTON, deleteButton);
}

void LoadZoneMenu::init()
{
    scene = NULL;
    zonesDisplay = NULL;
}
