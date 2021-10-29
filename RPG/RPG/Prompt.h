#pragma once
#include "UiElement.h"
#include <functional>

class Prompt : public UiElement
{
public:
    //attributes
    bool toBeDeleted;

    //constructors
    Prompt();
    Prompt(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    Prompt(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);

    //destructor
    virtual ~Prompt();
    
    //methods
    virtual void draw() override;
    void free();
    Prompt* addCallBack(std::function<void()> newCallback);
    bool gettingTextInput();

protected:
    //attributes
    std::function<void()> callback;

private:
    //methods
    void init();
};