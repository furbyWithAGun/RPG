#pragma once
#include "InputMessage.h"
#include "Sprite.h"
#include <functional>

enum LAYOUTS {
    FLOW_LAYOUT,
    SINGLE_LINE
};

enum ALIGNMENTS
{
    VERTICAL,
    HORIZONTAL
};

const int ALL_ELEMENTS = -1;


class UiElement : public Sprite
{
public:
    //attributes
    int id;
    std::vector<UiElement*> subElements;
    std::string text;
    bool dynamicPosition, dynamicSize;
    int layout, alignment;
    int numElementsToDisplay;
    int displayIndex;
    bool gettingText;
    bool displaySubElements;

    //constructors
    UiElement();
    UiElement(GameScene* newScene, int xpos, int ypos);
    UiElement(GameScene* gameScene, int spriteTextureKey);
    UiElement(GameScene* gameScene, SDL_Color elementColour, int xpos, int ypos);
    UiElement(GameScene* gameScene, int spriteTextureKey, int xpos, int ypos);
    UiElement(GameScene* gameScene, int spriteTextureKey, int xpos, int ypos, int elementWidth, int elementHeight);
    UiElement(GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight);
    UiElement(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    UiElement(int elementId, GameScene* newScene, int xpos, int ypos);
    UiElement(int elementId, GameScene* gameScene, int spriteTextureKey);
    UiElement(int elementId, GameScene* gameScene, SDL_Color elementColour, int xpos, int ypos);
    UiElement(int elementId, GameScene* gameScene, int spriteTextureKey, int xpos, int ypos);
    UiElement(int elementId, GameScene* gameScene, int spriteTextureKey, int xpos, int ypos, int elementWidth, int elementHeight);
    UiElement(int elementId, GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight);
    UiElement(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);

    //methods
    virtual void draw() override;
    virtual void draw(int x, int y) override;
    virtual bool handleInput(InputMessage* message);
    virtual std::string getText() { return text; };
    virtual std::string getText(int subElementId);
    virtual UiElement* setText(std::string newText);
    virtual UiElement* setText(std::string newText, SDL_Color colour = COLOR_BLACK);
    virtual void setText(int subElementId, std::string newText);
    virtual void addElement(UiElement* element);
    virtual void addElement(int elementId, UiElement* element);
    virtual UiElement* getElementbyId(int elementId);
    virtual void deactivate();
    virtual bool isGettingText();
    virtual void update();
    virtual void onClick();
    UiElement* addOnClick(std::function<void()> newCallback);
    UiElement* addBtnOneCallback(std::function<void()> newCallback);

protected:

    //attributes
    std::function<void()> callback;
    std::function<void()> btnOneCallback;

private:
    //attributes

    //methods
    void init();
    void init(int newId);
};

