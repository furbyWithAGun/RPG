#pragma once
#include "UiElement.h"
#include "GameScene.h"
#include <functional>

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
    bool handleInput(InputMessage* message);
    virtual void onClick();
    MenuButton* addOnClick(std::function<void()> newCallback);
    void draw();
    MenuButton* setText(std::string newText, SDL_Color colour = COLOR_BLACK);

private:
    //attributes
    std::function<void()> callback;

    //methods
    void init();
    void init(GameScene * gameScene);
};

