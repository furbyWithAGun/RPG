#pragma once
#include "UiElement.h"
#include "MenuButton.h"

class PagedPanel : public UiElement
{
public:
    //attributes
    MenuButton nextButton;
    MenuButton prevButton;
    int currentPage;
    std::vector<std::vector<UiElement*>> pages;

    //constructors
    PagedPanel();
    PagedPanel(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    PagedPanel(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);

    //methods
    void addElement(UiElement* newElement) override;
    void addElementToPage(int pageNum, UiElement* newElement);
    void addElementToPage(int pageNum, int newElementId, UiElement* newElement);
    UiElement* getElementbyId(int elementId);
    bool handleInput(InputMessage* message) override;
    void draw() override;
    bool isGettingText() override;

private:
    void init();
};

