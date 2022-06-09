#include "MenuText.h"
#include "BaseGameEngine.h"

MenuText::MenuText()
{
    init();
}

MenuText::MenuText(GameScene* newScene, std::string newText, int xpos, int ypos) : UiElement(newScene, xpos, ypos) {
    init(newText);
}

MenuText::MenuText(GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos): UiElement(newScene, textColour, xpos, ypos)
{
    init(newText);
    colour = textColour;
}

MenuText::MenuText(GameScene* newScene, std::string newText, int xpos, int ypos, int newWidth, int newHeight) : UiElement(newScene, SDL_Color {0, 0, 0},xpos, ypos, newWidth, newHeight)
{
    init(newText);
}

MenuText::MenuText(GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos, int newWidth, int newHeight) : UiElement(newScene, textColour, xpos, ypos, newWidth, newHeight)
{
    init(newText);
    colour = textColour;
}

MenuText::MenuText(int elementId, GameScene* newScene, std::string newText, int xpos, int ypos) : UiElement(elementId, newScene, xpos, ypos) {
    init(newText);
}

MenuText::MenuText(int elementId, GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos) : UiElement(elementId, newScene, textColour, xpos, ypos)
{
    init(newText);
    colour = textColour;
}

MenuText::MenuText(int elementId, GameScene* newScene, std::string newText, int xpos, int ypos, int newWidth, int newHeight) : UiElement(elementId, newScene, SDL_Color{ 0, 0, 0 }, xpos, ypos, newWidth, newHeight)
{
    init(newText);
}

MenuText::MenuText(int elementId, GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos, int newWidth, int newHeight) : UiElement(elementId, newScene, textColour, xpos, ypos, newWidth, newHeight)
{
    init(newText);
    colour = textColour;
}

void MenuText::init() {
    drawBackground = false;
    colour = { 0, 0, 0 };
}

void MenuText::init(std::string newText) {
    init();
    setText(newText);
    //text = newText;
}

void MenuText::setPos(int newX, int newY)
{
    xpos = newX;
    ypos = newY;
}

void MenuText::setBackground(SDL_Color newColour)
{
    backgroundColour = newColour;
    drawBackground = true;
}

void MenuText::disableBackground()
{
    drawBackground = false;
}

MenuText* MenuText::setText(std::string newText)
{
    //int textureKey = scene->engine->createTextTexture(newText, colour);
    //text = newText;
    //height = scene->engine->getTextureHeight(textureKey);
    //width = scene->engine->getTextureWidth(textureKey);
    UiElement::setText(newText);
    return this;
}

void MenuText::draw()
{
    if (active)
    {
        UiElement::draw();
        if (width != -1 && height != -1)
        {
            scene->engine->renderText(text, xpos, ypos, width, height, colour);
        }
        else {
            scene->engine->renderText(text, xpos, ypos, colour);
        }
    }
}

void MenuText::draw(int x, int y)
{
    if (active)
    {
        UiElement::draw(x, y);
        if (width != -1 && height != -1)
        {
            scene->engine->renderText(text, x, y, width, height, colour);
        }
        else {
            scene->engine->renderText(text, x, y, colour);
        }
    }
}
