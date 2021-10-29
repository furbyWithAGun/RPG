#include "UiElement.h"

const SDL_Color DEFAULT_UI_ELEMENT_COLOUR = { 0, 0, 0 };

UiElement::UiElement() : Sprite()
{
    init();
}

UiElement::UiElement(GameScene* newScene, int xpos, int ypos) : Sprite(newScene, xpos, ypos)
{
    init();
}

UiElement::UiElement(GameScene* gameScene, int spriteTextureKey) : Sprite(spriteTextureKey, gameScene)
{
    init();
}

UiElement::UiElement(GameScene* gameScene, int spriteTextureKey, int xpos, int ypos) : Sprite(spriteTextureKey, gameScene, xpos, ypos)
{
    init();
}

UiElement::UiElement(GameScene* gameScene, SDL_Color elementColour, int xpos, int ypos) : Sprite(elementColour, gameScene, xpos, ypos)
{
    init();
}

UiElement::UiElement(GameScene* gameScene, int spriteTextureKey, int xpos, int ypos, int elementWidth, int elementHeight) : Sprite(spriteTextureKey, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

UiElement::UiElement(GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight) : Sprite(DEFAULT_UI_ELEMENT_COLOUR, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

UiElement::UiElement(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Sprite(spriteBackgroundColour, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

UiElement::UiElement(int elementId, GameScene* newScene, int xpos, int ypos) : Sprite(newScene, xpos, ypos)
{
    init(elementId);
}

UiElement::UiElement(int elementId, GameScene* gameScene, int spriteTextureKey) : Sprite(spriteTextureKey, gameScene)
{
    init(elementId);
}

UiElement::UiElement(int elementId, GameScene* gameScene, int spriteTextureKey, int xpos, int ypos) : Sprite(spriteTextureKey, gameScene, xpos, ypos)
{
    init(elementId);
}

UiElement::UiElement(int elementId, GameScene* gameScene, SDL_Color elementColour, int xpos, int ypos) : Sprite(elementColour, gameScene, xpos, ypos)
{
    init(elementId);
}

UiElement::UiElement(int elementId, GameScene* gameScene, int spriteTextureKey, int xpos, int ypos, int elementWidth, int elementHeight) : Sprite(spriteTextureKey, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init(elementId);
}

UiElement::UiElement(int elementId, GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight) : Sprite(DEFAULT_UI_ELEMENT_COLOUR, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init(elementId);
}

UiElement::UiElement(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Sprite(spriteBackgroundColour, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init(elementId);
}

void UiElement::init() {
    gettingText = false;
    id = -1;
    text = "";
    dynamicPosition = dynamicSize = true;
    layout = FLOW_LAYOUT;
    alignment = VERTICAL;
    displaySubElements = true;
}

void UiElement::init(int newId) {
    init();
    id = newId;
}

void UiElement::draw() {
	if (active)
	{
		Sprite::draw();
        if (displaySubElements)
        {
            for (auto element : subElements)
            {
                if (element->active) {
                    element->draw();
                }
            }

        }
    }
}

bool UiElement::handleInput(InputMessage* message)
{
    switch (message->id)
    {
    case SELECT_ON:
    case SELECT_OFF:
        return pointCollision(message->x, message->y);
        break;
    default:
        return false;
    }
}


void UiElement::addElement(UiElement* newElement) {
    subElements.push_back(newElement);
}

void UiElement::addElement(int elementId, UiElement* newElement) {
    newElement->id = elementId;
    subElements.push_back(newElement);
}

UiElement* UiElement::getElementbyId(int elementId) {
    if (id == elementId)
    {
        return this;
    }

    for (auto element : subElements) {
        if (element->id == elementId)
        {
            return element;
        }

        if (element->getElementbyId(elementId) != NULL)
        {
            return element->getElementbyId(elementId);
        }
    }
    return nullptr;
}

void UiElement::deactivate()
{
    active = false;
}

bool UiElement::isGettingText()
{
    if (gettingText)
    {
        return true;
    }
    for (auto element : subElements)
    {
        if (element->isGettingText())
        {
            return true;
        }
    }
    return false;
}

std::string UiElement::getText(int subElementId) {
    UiElement* element = getElementbyId(subElementId);
    if (element != NULL)
    {
        return element->getText();
    }
    return "";
}

UiElement* UiElement::setText(std::string newText) {
    text = newText;
    return this;
}

void UiElement::setText(int subElementId, std::string newText) {
    UiElement* element = getElementbyId(subElementId);
    if (element != NULL)
    {
        element->setText(newText);
    }
}