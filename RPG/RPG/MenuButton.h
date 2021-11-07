#pragma once
#include "UiElement.h"
#include "GameScene.h"

//class BaseGameEngine;

class MenuButton: public UiElement
{
public:
    //attributes
    GameScene* scene;
    int textTextureKey;
    int textXoffset, textYoffset, textWidth, textHeight;

    //constructors
    MenuButton();
    MenuButton(GameScene* gamescene, int spriteTextureKey);
    MenuButton(int elementID, GameScene* gamescene, int spriteTextureKey);
    MenuButton(GameScene* gamescene, int spriteTextureKey, int xpos, int ypos);
    MenuButton(GameScene* gamescene, int xpos, int ypos);
    MenuButton(int elementID, GameScene* gamescene, int spriteTextureKey, int xpos, int ypos);

    //destructor
    //~MenuButton();

    //methods
    void draw();
    MenuButton* setText(std::string newText, SDL_Color colour = COLOR_BLACK) override;

private:

    //methods
    void init();
    void init(GameScene * gameScene);
};

