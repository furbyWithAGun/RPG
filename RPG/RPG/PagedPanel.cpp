#include "PagedPanel.h"

const double BUTTON_HEIGHT = 0.04;
const double BUTTON_WIDTH = 0.045;

PagedPanel::PagedPanel() : UiElement()
{
    init();
}

PagedPanel::PagedPanel(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

PagedPanel::PagedPanel(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(elementId, gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

void PagedPanel::init()
{    
    prevButton = MenuButton(scene, xpos + (width - scene->engine->screenWidth * BUTTON_WIDTH * 2) / 2, ypos + height - scene->engine->screenHeight * BUTTON_HEIGHT);
    prevButton.setdimensions(scene->engine->screenWidth * BUTTON_WIDTH, scene->engine->screenHeight * BUTTON_HEIGHT);
    prevButton.setText("Prev", COLOR_WHITE);
    
    nextButton= MenuButton(scene, scene->engine->screenWidth * BUTTON_WIDTH + xpos + (width - scene->engine->screenWidth * BUTTON_WIDTH * 2) / 2, ypos + height - scene->engine->screenHeight * BUTTON_HEIGHT);
    nextButton.setdimensions(scene->engine->screenWidth * BUTTON_WIDTH, scene->engine->screenHeight * BUTTON_HEIGHT);
    nextButton.setText("Next", COLOR_WHITE);
}

void PagedPanel::addElement(UiElement* newElement)
{
    subElements.push_back(newElement);
}

void PagedPanel::addElementToPage(int pageNum, UiElement* newElement)
{
    while (pageNum >= pages.size())
    {
        pages.push_back(std::vector<UiElement*>());
    }
    pages[pageNum].push_back(newElement);
}

void PagedPanel::addElementToPage(int pageNum, int newElementId, UiElement* newElement)
{
    newElement->id = newElementId;
    while (pageNum >= pages.size())
    {
        pages.push_back(std::vector<UiElement*>());
    }
    pages[pageNum].push_back(newElement);
}

UiElement* PagedPanel::getElementbyId(int elementId)
{
    if (id == elementId)
    {
        return this;
    }

    for (size_t i = 0; i < pages.size(); i++)
    {
        for (size_t j = 0; j < pages[i].size(); j++) {
            if (pages[i][j]->id == elementId)
            {
                return pages[i][j];
            }

            if (pages[i][j]->getElementbyId(elementId) != nullptr)
            {
                return pages[i][j]->getElementbyId(elementId);
            }
        }
    }
    return nullptr;
}

bool PagedPanel::handleInput(InputMessage* message)
{
    bool messageConsumed = false;
    if (message->id == SELECT_ON)
    {
        int x = 2453456;
    }
    if (active)
    {
        for (UiElement* element : pages[currentPage]) {
            messageConsumed = element->handleInput(message);
            if (messageConsumed)
            {
                break;
            }
        }

        switch (message->id)
        {
        case SELECT_ON:
            if (currentPage + 1 < pages.size() && nextButton.pointCollision(message->x, message->y))
            {
                currentPage += 1;
            }
            else if (currentPage > 0 && prevButton.pointCollision(message->x, message->y)) {
                currentPage -= 1;
            }
            break;
        case SCROLL_UP:
            if (currentPage > 0 && pointCollision(message->x, message->y))
            {
                //currentPage -= 1;
            }
            break;
        case SCROLL_DOWN:
            if (currentPage + 1 < pages.size() && pointCollision(message->x, message->y)) {
                //currentPage += 1;
            }
            break;
        default:
            break;
        }
    }
    return pointCollision(message->x, message->y);
}


void PagedPanel::draw()
{
    if (active)
    {
        UiElement::draw();
        for (auto element : pages[currentPage])
        {
            element->draw();
        }
        if (currentPage + 1 < pages.size())
        {
            nextButton.draw();
        }
        if (currentPage > 0)
        {
            prevButton.draw();
        }
    }
}

bool PagedPanel::isGettingText()
{
    if (UiElement::isGettingText())
    {
        return true;
    }
    for (auto element: pages[currentPage]) {
        if (element->isGettingText())
        {
            return true;
        }
    }
    return false;
}

void PagedPanel::deactivate()
{
    UiElement::deactivate();
    for (std::vector<UiElement*> page : pages) {
        for (UiElement* element : page) {
            element->deactivate();
        }
    }
}

void PagedPanel::activate()
{
    UiElement::activate();
    for (std::vector<UiElement*> page : pages) {
        for (UiElement* element : page) {
            element->activate();
        }
    }
}
