#include "SaveMapBuilderButton.h"

//constructors
SaveMapBuilderButton::SaveMapBuilderButton() : MenuButton() {
    scene = NULL;
}

SaveMapBuilderButton::SaveMapBuilderButton(RpgWorldBuilderScene* gameScene, int buttonTextureKey) : MenuButton(gameScene, buttonTextureKey) {
    scene = gameScene;
}

SaveMapBuilderButton::SaveMapBuilderButton(int elementId, RpgWorldBuilderScene* gameScene, int buttonTextureKey) : MenuButton(elementId, gameScene, buttonTextureKey) {
    scene = gameScene;
}

void SaveMapBuilderButton::onClick() {
    scene->openMenu(SAVE_ZONE_MENU);
}