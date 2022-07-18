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

void LoadSaveGameMenu::open()
{
    scene->closeAllMenus();
    GameMenu::open();
    delete elements[SAVES_SCROLL_BOX];
    elements.erase(SAVES_SCROLL_BOX);
    buildScrollBox();
}

void LoadSaveGameMenu::buildElements(RpgOverWorldScene* overWorldScene)
{
    //label
    addElement(LOAD_GAME_LABEL, new MenuText(LOAD_GAME_LABEL, scene, "Load Game", { 255, 255, 255 }, xpos + width * 0.465, ypos + height * 0.2));
    MenuText* label = (MenuText * )getElementbyId(LOAD_GAME_LABEL);

    buildScrollBox();

    //load button
    MenuButton* loadButton = new MenuButton(GAME_LOAD_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + width * 0.65, ypos + height * 0.3);
    loadButton->setText("Load")->addOnClick([this, overWorldScene]() {
        ScrollBox* scroller = (ScrollBox*)getElementbyId(SAVES_SCROLL_BOX);
        overWorldScene->setSaveGameName(SAVES_FILE_PATH + scroller->selectedElement->getText());
        scene->engine->setNextScene(OVERWORLD);
        close();
        scene->endScene();
        });
    addElement(GAME_LOAD_BUTTON, loadButton);

    //Cancel button
    MenuButton* cancelButton = new MenuButton(LOAD_GAME_CANCEL_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + width * 0.65, ypos + height * 0.4);
    cancelButton->setText("Cancel")->addOnClick([this]() {
        close();
        });
    addElement(LOAD_GAME_CANCEL_BUTTON, cancelButton);

    //Delete button
    MenuButton* deleteButton = new MenuButton(LOAD_GAME_DELETE_BUTTON, this->scene, BUTTON_BACKGROUND, xpos + width * 0.65, ypos + height * 0.5);
    deleteButton->setText("Delete")->addOnClick([this]() {
        ScrollBox* oldScroller = (ScrollBox*)getElementbyId(SAVES_SCROLL_BOX);
        std::remove((SAVES_FILE_PATH +  oldScroller->selectedElement->getText()).c_str());
        delete elements[SAVES_SCROLL_BOX];
        elements.erase(SAVES_SCROLL_BOX);
        buildScrollBox();
        });
    addElement(LOAD_GAME_DELETE_BUTTON, deleteButton);
}

void LoadSaveGameMenu::init()
{
    scene = nullptr;
    savesDisplay = nullptr;
}

void LoadSaveGameMenu::buildScrollBox()
{
    //Zones scrollbox
    ScrollBox* scroller;
    scroller = new ScrollBox(SAVES_SCROLL_BOX, scene, { 100, 100, 100 }, xpos + width * 0.5 - (width * 0.2)/2, ypos + height * 0.50 - (height * 0.4)/2, width * 0.2, height * 0.4);
    scroller->numElementsToDisplay = 4;

    std::string path = SAVES_FILE_PATH;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        MenuText* saveName = new MenuText(scene, entry.path().stem().string(), 0, 0);
        saveName->setBackground({ 100, 100, 100 });
        scroller->addElement(saveName);
    }

    addElement(SAVES_SCROLL_BOX, scroller);
}
