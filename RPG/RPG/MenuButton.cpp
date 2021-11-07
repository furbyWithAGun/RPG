#include "MenuButton.h"

MenuButton::MenuButton() : UiElement() {
    init();
}

MenuButton::MenuButton(GameScene* gameScene, int spriteTextureKey) : UiElement(gameScene, spriteTextureKey){
    init(gameScene);
}

MenuButton::MenuButton(int elementId, GameScene* gameScene, int spriteTextureKey) : UiElement(elementId, gameScene, spriteTextureKey) {
    init(gameScene);
}

MenuButton::MenuButton(GameScene* gameScene, int spriteTextureKey, int xpos, int ypos) : UiElement(gameScene, spriteTextureKey, xpos, ypos) {
    init(gameScene);
}

MenuButton::MenuButton(GameScene* gameScene, int xpos, int ypos) : UiElement(gameScene, xpos, ypos) {
    init(gameScene);
}

MenuButton::MenuButton(int elementId, GameScene* gameScene, int spriteTextureKey, int xpos, int ypos) : UiElement(elementId, gameScene, spriteTextureKey, xpos, ypos) {
    init(gameScene);
}

void MenuButton::init() {
    scene = nullptr;
    text = "";
    textXoffset = textYoffset = textWidth = textHeight = 0;
    textTextureKey = -1;
    if (textureKey == -1)
    {
        textureKey = DEFAULT_BUTTON_TEXTURE_ID;
    }
}

void MenuButton::init(GameScene* gameScene) {
    init();
    scene = gameScene;
    if (textureKey == DEFAULT_BUTTON_TEXTURE_ID)
    {
        width = scene->engine->getTextureWidth(DEFAULT_BUTTON_TEXTURE_ID);
        height = scene->engine->getTextureHeight(DEFAULT_BUTTON_TEXTURE_ID);
    }
}

void MenuButton::draw() {
    if (active)
    {
        UiElement::draw();
        if (!textTextureKey != -1)
        {
            scene->renderTexture(textTextureKey, xpos + textXoffset, ypos + textYoffset, textWidth, textHeight);
        }
    }
}

MenuButton* MenuButton::setText(std::string newText, SDL_Color colour) {
    text = newText;
    textTextureKey = scene->engine->createTextTexture(newText, colour);
    textHeight = height * 0.75;
    textWidth = width * 0.75;
    textXoffset = width * 0.09;
    textYoffset = height * 0.11;
    return this;
}
