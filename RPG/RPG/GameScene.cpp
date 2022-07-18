#include "GameScene.h"
#include "BaseGameEngine.h"
#include "Prompt.h"

//constructors
GameScene::GameScene() {
    init();
}

GameScene::GameScene(BaseGameEngine * newEngine) {
    init();
    engine = newEngine;
}

void GameScene::init() {
    engine = NULL;
    sceneRunning = true;
    gettingTextInput = false;
    controllerInterface = NULL;
}


//public methods

void GameScene::handleInput()
{
    InputMessage* message = new InputMessage();
    std::vector<InputMessage*> messagesToSendBack;
    if (openPrompts.size() > 0) {
        if (gettingTextInput)
        {
            handleTextInput();
        }
        controllerInterface->populateMessageQueue();
        while (controllerInterface->getNextMessage(message)) {
            bool promptsConsumeMessage = false;
            for (auto prompt : openPrompts) {
                if (prompt->handleInput(message)) {
                    promptsConsumeMessage = true;
                    break;
                }
            }
            if (!promptsConsumeMessage)
            {
                messagesToSendBack.push_back(new InputMessage(message->id, message->x, message->y, message->misc));
            }
        }
        for (auto prompt : openPrompts) {
            if (prompt->toBeDeleted)
            {
                removePrompt(prompt);
            }
        }
        for (auto msg : messagesToSendBack)
        {
            controllerInterface->addMessage(msg);
            //delete msg;
        }
        messagesToSendBack.clear();
    } else{
        if (gettingTextInput)
        {
            handleTextInput();
        }
        else {
            controllerInterface->populateMessageQueue();
        }
    }
    
    if (gettingTextInput)
    {
        handleTextInput();
    }

    gettingTextInput = false;

    for (auto menu : menus)
    {
        if (menu.second->isGettingText() && menu.second->isActive) {
            gettingTextInput = true;
        }
    }
    if (!gettingTextInput) {
        for (auto prompt : openPrompts) {
            if (prompt->gettingTextInput())
            {
                gettingTextInput = true;
            }
        }
    }

    while (controllerInterface->getNextMessage(message)) {
        if (!sendMessageToMenus(message)) {
            messagesToSendBack.push_back(new InputMessage(message->id, message->x, message->y, message->misc));
        }
    }
    for (auto msg : messagesToSendBack)
    {
        controllerInterface->addMessage(msg);
        //delete msg;
    }
    messagesToSendBack.clear();
    if (message != nullptr)
    {
        delete message;
    }
}

void GameScene::sceneLogic()
{
    for (auto menu : menus)
    {
        if (menu.second->isActive)
        {
            menu.second->update();
        }
    }
}

void GameScene::renderTexture(Texture* texture, int x, int y)
{
    engine->renderTexture(texture, x, y);
}

void GameScene::renderTexture(Texture*  texture, int x, int y, int width, int height)
{
    engine->renderTexture(texture, x, y, width, height);
}

void GameScene::renderTexture(int textureKey, int x, int y)
{
    engine->renderTexture(textureKey, x, y);
}

void GameScene::renderTexture(int textureKey, int x, int y, int width, int height)
{
    engine->renderTexture(textureKey, x, y, width, height);
}

void GameScene::renderRectangle(int x, int y, int width, int height, int r, int g, int b) {
    engine->renderRectangle(x, y, width, height, r, g, b);
}

void GameScene::renderRectangle(int x, int y, int width, int height, SDL_Color color) {
    engine->renderRectangle(x, y, width, height, color);
}

void GameScene::renderRectangle(int x, int y, int width, int height, int r, int g, int b, int a) {
    engine->renderRectangle(x, y, width, height, r, g, b, a);
}

void GameScene::endScene() {
    sceneRunning = false;
    for (auto prompt : openPrompts) {
        delete prompt;
    }
    openPrompts.clear();
    SDL_AtomicUnlock(&engine->sceneRunningLock);
}

void GameScene::openMenu(int menuId) {
    menus[menuId]->open();
    controllerInterface->selectOn = false;
}

void GameScene::closeMenu(int menuId) {
    menus[menuId]->close();
}

void GameScene::closeAllMenus() {
    for (auto menu : menus) {
        menu.second->close();
    }
    gettingTextInput = false;
}

bool GameScene::mouseOnAMenu()
{   
    for (auto menu : menus) {
        if (menu.second->pointCollide(controllerInterface->latestXpos, controllerInterface->latestYpos) && menu.second->isActive)
        {
            return true;
        }
    }
    return false;
}

bool GameScene::sendMessageToMenus(InputMessage* message)
{
    bool messageConsumed = false;
    for (auto menu : menus){
        if (!messageConsumed)
        {
            if (menu.second->isActive)
            {
                messageConsumed = menu.second->handleInput(message);
                if (messageConsumed)
                {
                    return true;
                }
            }
        }
    }
    return messageConsumed;
}

void GameScene::drawMenus()
{
    for (auto menu : menus)
    {
        if (menu.second->isActive)
        {
            menu.second->draw();
        }
    }
}

void GameScene::drawPrompts()
{
    for (auto prompt : openPrompts) {
        if (prompt->active)
        {
            prompt->draw();
        }
    }
}

void GameScene::clearCommandQueue()
{
    for (auto command : commandQueue) {
        delete command;
        commandQueue.clear();
    }
}

Prompt* GameScene::addPrompt(Prompt* newPrompt)
{
    openPrompts.push_back(newPrompt);
    return newPrompt;
}

void GameScene::removePrompt(Prompt* promptToDelete)
{
    for (int i = 0; i < openPrompts.size(); i++)
    {
        if (openPrompts[i] == promptToDelete) {
            delete openPrompts[i];
            openPrompts.erase(openPrompts.begin() + i);
        }
    }
}

void GameScene::clearInputMessages()
{
    for (auto msg : controllerInterface->messageQueue)
    {
        delete msg;
    }
    controllerInterface->messageQueue.clear();
}

bool GameScene::getNextCommand(InputMessage* message) {
    if (commandQueue.size() > 0)
    {
        *message = *commandQueue[0];
        delete commandQueue[0];
        commandQueue.erase(commandQueue.begin());
        return true;
    }
    else {
        message = NULL;
        return false;
    }
}

void GameScene::addCommand(InputMessage* newMessage) {
    InputMessage* message = new InputMessage();
    *message = *newMessage;
    commandQueue.push_back(message);
}

void GameScene::addCommand(InputMessage newMessage) {
    InputMessage* message = new InputMessage();
    *message = newMessage;
    commandQueue.push_back(message);
}

void GameScene::handleTextInput()
{

    bool messageConsumed = false;
    if (controllerInterface != NULL && gettingTextInput)
    {
        controllerInterface->populateTextInputQueue();
        InputMessage* message = new InputMessage();
        while (controllerInterface->getNextTextInput(message))
        {
            switch (message->id)
            {
            case END_SCENE:
                endScene();
                break;
            case K_ESC:
            case K_BACKSPACE:
            case K_ENTER:
            case TEXT_INPUT:
            case SELECT_ON:
            case SELECT_OFF:
            case SCROLL_UP:
            case SCROLL_DOWN:
                for (auto prompt : openPrompts)
                {
                    if (prompt->handleInput(message)) {
                        messageConsumed = true;
                    }
                }
                if (!messageConsumed)
                {
                    sendMessageToMenus(message);
                }
                break;
            default:
                break;
            }
        }
        delete message;
    }
}
