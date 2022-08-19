#pragma once
#include "Texture.h"
#include "ControllerInterface.h"
#include <unordered_map>
#include "GameMenu.h"
#include <chrono>

class BaseGameEngine;
class Prompt;

class GameScene
{
    friend class BaseGameEngine;
    friend class HoverToolTip;
public:
    //attributes
    BaseGameEngine* engine;
    int timeToWaitDiscount;
    int lastTickDuration;
    bool sceneRunning;
    bool gettingTextInput;
    std::vector<Prompt*> openPrompts;
    std::unordered_map<int, GameMenu*> menus;
    
    //constructor
    GameScene();
    GameScene(BaseGameEngine * gameEngine);

    //methods
    virtual void handleInput();
    virtual void sceneLogic();
    virtual void renderScene() {};
    void renderTexture(Texture* texture, int x, int y);
    void renderTexture(Texture* texture, int x, int y, int width, int height);
    void renderTexture(int textureKey, int x, int y);
    void renderTexture(int textureKey, int x, int y, int width, int height);
    void renderRectangle(int x, int y, int width, int height, int r, int g, int b);
    void renderRectangle(int x, int y, int width, int height, SDL_Color color);
    void renderRectangle(int x, int y, int width, int height, int r, int g, int b, int a);
    bool getNextCommand(InputMessage* message);
    void addCommand(InputMessage* message);
    void addCommand(InputMessage message);
    void openMenu(int menuId);
    void closeMenu(int menuId);
    void closeAllMenus();
    bool mouseOnAMenu();
    Prompt* addPrompt(Prompt* newPrompt);
    void endScene();
    void removePrompt(Prompt* promptToDelete);
    void clearInputMessages();

protected:
    //attributes
    std::unordered_map<int, std::string> texturesToLoad;
    ControllerInterface* controllerInterface;
    //std::vector<InputMessage*> commandQueue;
    SDL_SpinLock commandQueueLock;

    //methods
    virtual void declareSceneAssets() {};
    virtual void setUpScene() {};
    bool sendMessageToMenus(InputMessage* message);
    void drawMenus();
    void drawPrompts();
    void clearCommandQueue();    

private:
    //attributes
    std::vector<InputMessage*> commandQueue;

    //methods
    void init();
    void handleTextInput();
};