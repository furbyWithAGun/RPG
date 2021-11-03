#pragma once
#include <string>
#include "GameScene.h"
#include "UiElement.h"

class MenuText : public UiElement
{
public:
    //attributes
    SDL_Color colour;

    //constructors
    MenuText();
    MenuText(GameScene* newScene, std::string newText, int xpos, int ypos);
    MenuText(GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos);
    MenuText(GameScene* newScene, std::string newText, int xpos, int ypos, int newWidth, int newHeight);
    MenuText(GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos, int newWidth, int newHeight);
    MenuText(int elementId, GameScene* newScene, std::string newText, int xpos, int ypos);
    MenuText(int elementId, GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos);
    MenuText(int elementId, GameScene* newScene, std::string newText, int xpos, int ypos, int newWidth, int newHeight);
    MenuText(int elementId, GameScene* newScene, std::string newText, SDL_Color textColour, int xpos, int ypos, int newWidth, int newHeight);

    //methods
    void draw() override;
    void draw(int x, int y) override;
    void setPos(int newX, int newY);
    void setBackground(SDL_Color newColour);
    void disableBackground();
    MenuText* setText(std::string newText);

private:
    //methods
    void init();
    void init(std::string newText);
};

