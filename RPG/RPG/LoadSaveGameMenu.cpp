#include "LoadSaveGameMenu.h"
#include "RpgOverWorldScene.h"

enum LOAD_GAME_MENU_IDS {
    LOAD_GAME_LABEL,
    SAVES_SCROLL_BOX,
    GAME_LOAD_BUTTON,
    LOAD_GAME_CANCEL_BUTTON,
    LOAD_GAME_DELETE_BUTTON
};

LoadSaveGameMenu::LoadSaveGameMenu() : GameMenu()
{
    init();
}

LoadSaveGameMenu::LoadSaveGameMenu(GameScene* gameScene, RpgOverWorldScene* overWorldScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos) : GameMenu(gameScene, newId, newWidth, newHeight, newXPos, newYPos) {
    init();
    scene = gameScene;
    buildElements(overWorldScene);
}

void LoadSaveGameMenu::buildElements(RpgOverWorldScene* overWorldScene)
{
    //label
    addElement(LOAD_GAME_LABEL, new MenuText(LOAD_GAME_LABEL, scene, "Load Game", { 255, 255, 255 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.015));

    //Zones scrollbox
    ScrollBox* scroller;
    scroller = new ScrollBox(SAVES_SCROLL_BOX, scene, { 100, 100, 100 }, xpos + (width - width * 0.8) / 2, ypos + height * 0.15, width * 0.5, height * 0.6);
    scroller->numElementsToDisplay = 4;

    std::string path = "/path/to/directory";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        MenuText* saveName = new MenuText(scene, entry.path().string(), 0, 0);
        saveName->setBackground({ 100, 100, 100 });
        scroller->addElement(saveName);
    }

    addElement(SAVES_SCROLL_BOX, scroller);

    //load button
    MenuButton* loadButton = new MenuButton(GAME_LOAD_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + (width - width * 0.8) / 2, ypos + height * 0.8);
    loadButton->setText("Load")->addOnClick([this, overWorldScene]() {
        ScrollBox* scroller = (ScrollBox*)getElementbyId(SAVES_SCROLL_BOX);
        overWorldScene->setSaveGameName(scroller->selectedElement->getText());
        scene->engine->setNextScene(OVERWORLD);
        scene->endScene();
        close();
        });
    addElement(GAME_LOAD_BUTTON, loadButton);

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

void LoadSaveGameMenu::init()
{
    scene = nullptr;
    savesDisplay = nullptr;
}
