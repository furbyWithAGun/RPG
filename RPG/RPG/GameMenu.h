#pragma once
#include <vector>
#include <unordered_map>

class MenuButton;
class MenuText;
class BaseGameEngine;
class InputMessage;
class UiElement;
class GameScene;
class GameEngine;
class HoverToolTip;
class GameMenu
{
public:
    //attributes
    std::vector<MenuButton*> buttons;
    std::unordered_map<int, UiElement*> elements;
    std::vector<MenuText*> texts;
    bool isActive;
    GameScene* scene;
    bool pointCollide(int x, int y);

    
    //constructors
    GameMenu();
    GameMenu(GameScene* gameScene, int newId, int newWidth, int newHeight, int newXPos, int newYPos);
    GameMenu(GameScene* gameScene, int newId);

    //destructor
    ~GameMenu();

    //methods
    void setRGBA(int newR, int newG, int newB, int newA);
    int addElement(UiElement* element);
    int addElement(int elementId, UiElement* element);
    UiElement* getElementbyId(int elementId);
    int getNextElementId();
    virtual void open();
    virtual void close();
    virtual void draw();
    virtual void drawToolTips();
    void registerToolTip(UiElement* parentElement, HoverToolTip* toolTip);
    virtual void update();
    virtual void rebuildElements() {};
    virtual bool handleInput(InputMessage* message);
    bool isGettingText();

protected:
    //attributes
    BaseGameEngine* engine;
    std::vector<HoverToolTip*> toolTips;
    int width;
    int height;
    int xpos;
    int ypos;
    int id, r, g, b, a;

private:
    //attributes
    int nextElementId;

    //methods
    void init();
    void deactivate();
};

