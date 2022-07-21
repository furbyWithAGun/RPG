#include "BaseGameEngine.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdlib.h>

//constants
const int KEY_R_VALUE = 255;
const int KEY_G_VALUE = 0;
const int KEY_B_VALUE = 255;
const int DEFAULT_FONT_SIZE = 28;
const double DEFAULT_TICKS_PER_SECOND = 150;
//const double DEFAULT_TICK_DELAY = 1000 / DEFAULT_TICKS_PER_SECOND;
const std::string DEFAULT_BUTTON_TEXTURE_PATH = "images/buttonBackground.png";
const double DEFAULT_SIGMOID_OMEGA = 1;
const double DEFAULT_SIGMOID_ALPHA = 1.1;

BaseGameEngine::BaseGameEngine(std::string title, int width, int height) {
    textures.clear();
    screenHeight = 0;
    screenWidth = 0;
    windowTitle = title;
    windowWidth = width;
    windowHeight = height;
    mainWindow = NULL;
    mainRenderer = NULL;
    mainFont = NULL;
    currentScene = NULL;
    nextScene = NULL;
    sceneRunning = false;
    gameRunning = false;
    sceneLock = 0;
    setTicksPerSecond(DEFAULT_TICKS_PER_SECOND);
    auto_texturekey = AUTO_TEXTURE_KEY_START;
}

BaseGameEngine::~BaseGameEngine() {
    free();
}

void BaseGameEngine::free() {
    
    if (mainWindow != NULL)
    {
        SDL_DestroyWindow(mainWindow);
    }

    if (mainRenderer != NULL)
    {
        SDL_DestroyRenderer(mainRenderer);
    }
    if (mainFont != NULL)
    {
        TTF_CloseFont(mainFont);
    }

    textures.clear();
    windowHeight = 0;
    windowWidth = 0;
    windowTitle = "";
    screenWidth = 0;
    screenHeight = 0;
    mainWindow= NULL;
    mainRenderer = NULL;
    mainFont = NULL;
    currentScene = NULL;
    nextScene = NULL;
    scenes.clear();
}

SDL_Window* BaseGameEngine::createWindow(const char* title, int height, int width) {
    SDL_Window* newWindow = NULL;

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    newWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    //newWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    //newWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP); //********************DO NOT USE THIS ONE******************************************
    
    if (newWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }

    
    return newWindow;
}

SDL_Renderer* BaseGameEngine::createRenderer(SDL_Window* window) {
    SDL_Renderer* newRenderer = NULL;

    //Create vsynced renderer for window
    newRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (newRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return NULL;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(newRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_GetRendererOutputSize(newRenderer, &screenWidth, &screenHeight);

    return newRenderer;
}

bool BaseGameEngine::init() {
    //init sigmoid function
    setSigmoidFunction(DEFAULT_SIGMOID_OMEGA, DEFAULT_SIGMOID_ALPHA);

    //init rand
    srand(time(NULL));

    //init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //create window
    mainWindow = createWindow(windowTitle.c_str(), windowHeight, windowWidth);
    if (mainWindow == NULL)
    {
        return false;
    }

    //create main window renderer
    mainRenderer = createRenderer(mainWindow);
    if (mainRenderer == NULL)
    {
        return false;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    //load assets (this method will be overriden in child class)
    loadAssets();

    //load fonts
    mainFont = TTF_OpenFont("fonts/OpenSans-Regular.ttf", DEFAULT_FONT_SIZE);

    //load default textures
    createImageTexture(DEFAULT_BUTTON_TEXTURE_ID, DEFAULT_BUTTON_TEXTURE_PATH);

    return true;
}

void BaseGameEngine::close() {
    free();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Window* BaseGameEngine::getMainWindow() {
    return mainWindow;
}

SDL_Renderer* BaseGameEngine::getMainRenderer() {
    return mainRenderer;
}

SDL_Texture* BaseGameEngine::loadTextureImageFromFile(std::string path) {
    SDL_Texture* newTexture = NULL;
    
    //load the image from the file
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }

    //set transparent color
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, KEY_R_VALUE, KEY_G_VALUE, KEY_B_VALUE));
    
    //convert to texture
    newTexture = SDL_CreateTextureFromSurface(mainRenderer, loadedSurface);
    if (newTexture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return NULL;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    //SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_ADD);
    SDL_SetTextureScaleMode(newTexture, SDL_ScaleModeNearest);
    
    return newTexture;
}

bool BaseGameEngine::loadTextureImage(Texture* texture) {

    texture->texture = loadTextureImageFromFile(texture->filePath);
    SDL_QueryTexture(texture->texture, NULL, NULL, &texture->width, &texture->height);
    return true;
}

SDL_Texture* BaseGameEngine::loadTextureFromText(std::string text, SDL_Color colour) {
    SDL_Texture* textTexture;
    SDL_Surface* textSurface = TTF_RenderText_Solid(mainFont, text.c_str(), colour);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    textTexture = SDL_CreateTextureFromSurface(mainRenderer, textSurface);
    if (textTexture == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(textSurface);
    return textTexture;
}

int BaseGameEngine::createImageTexture(std::string imagePath) {
    int textureKey = auto_texturekey;
    textures[textureKey] = Texture(imagePath);
    loadTextureImage(&textures[textureKey]);
    auto_texturekey++;
    return textureKey;
}

int BaseGameEngine::createImageTexture(int textureKey, std::string imagePath) {
    textures[textureKey] = Texture(imagePath);
    loadTextureImage(&textures[textureKey]);
    return textureKey;
}

int BaseGameEngine::createTextTexture(std::string text, SDL_Color colour) {
    if (!text.empty())
    {
        std::string key = text + std::to_string(colour.a) + std::to_string(colour.r) + std::to_string(colour.g) + std::to_string(colour.b);
        if (textTextures.find(key) == textTextures.end())
        {
            int textureKey = auto_texturekey;
            textures[textureKey] = Texture();
            textures[textureKey].texture = loadTextureFromText(text, colour);
            SDL_QueryTexture(textures[textureKey].texture, NULL, NULL, &textures[textureKey].width, &textures[textureKey].height);
            auto_texturekey++;
            textTextures[key] = textureKey;
            return textureKey;
        }
        else {
            return textTextures[key];
        }
    }
}

int BaseGameEngine::createTextTexture(int textureKey, std::string text, SDL_Color colour) {
    textures[textureKey] = Texture();
    textures[textureKey].texture = loadTextureFromText(text, colour);
    SDL_QueryTexture(textures[textureKey].texture, NULL, NULL, &textures[textureKey].width, &textures[textureKey].height);
    return textureKey;
}

bool BaseGameEngine::createMultipleTextures(std::unordered_map<int, std::string> texturesToCreate) {
    for (auto i = texturesToCreate.begin(); i != texturesToCreate.end(); ++i)
    {
        createImageTexture(i->first, i->second);
    }
    return true;
}

void BaseGameEngine::renderTexture(Texture* texture, int x, int y) {
    SDL_Rect renderQuad = { x, y, texture->width, texture->height };
    
    SDL_RenderCopy(mainRenderer, texture->texture, NULL, &renderQuad);
}

void BaseGameEngine::renderTexture(Texture* texture, int x, int y, int width, int height) {
    SDL_Rect renderQuad = { x, y, width, height };

    SDL_RenderCopy(mainRenderer, texture->texture, NULL, &renderQuad);
}

void BaseGameEngine::renderTexture(int textureKey, int x, int y) {
    renderTexture(&textures[textureKey], x, y);
}

void BaseGameEngine::renderTexture(int textureKey, int x, int y, int width, int height) {
    renderTexture(&textures[textureKey], x, y, width, height);
}

void BaseGameEngine::renderText(std::string textToRender, int x, int y, SDL_Color colour)
{
    if (!textToRender.empty())
    {
        std::string key = textToRender + std::to_string(colour.a) + std::to_string(colour.r) + std::to_string(colour.g) + std::to_string(colour.b);
        if (textTextures.find(key) == textTextures.end())
        {
            textTextures[key] = createTextTexture(textToRender, colour);
        }

        renderTexture(&textures[textTextures[key]], x, y);
    }
}

void BaseGameEngine::renderText(std::string textToRender, int x, int y, int width, int height, SDL_Color colour)
{
    if (!textToRender.empty())
    {
        std::string key = textToRender + std::to_string(colour.a) + std::to_string(colour.r) + std::to_string(colour.g) + std::to_string(colour.b);
        if (textTextures.find(key) == textTextures.end())
        {
            textTextures[key] = createTextTexture(textToRender, colour);
        }

        renderTexture(&textures[textTextures[key]], x, y, width, height);
    }
}


void BaseGameEngine::renderAnimation(Animation* animation, int x, int y) {
    SDL_Rect renderQuad = { x, y, animation->frameWidth, animation->frameHeight };
    SDL_Rect clipQuad = { 0, animation->currentFrame * animation->frameHeight, animation->frameWidth, animation->frameHeight };

    SDL_RenderCopy(mainRenderer, textures[animation->spriteSheetKey].texture, &clipQuad, &renderQuad);
}

void BaseGameEngine::renderAnimation(Animation* animation, int x, int y, int width, int height) {
    SDL_Rect renderQuad = { x, y, width, height };
    SDL_Rect clipQuad = { 0, animation->currentFrame * animation->frameHeight, animation->frameWidth, animation->frameHeight };

    SDL_RenderCopy(mainRenderer, textures[animation->spriteSheetKey].texture, &clipQuad, &renderQuad);
}

void BaseGameEngine::renderRectangle(int x, int y, int width, int height, int r, int g, int b)
{
    SDL_Rect fillRect = { x, y, width, height };
    SDL_SetRenderDrawColor(getMainRenderer(), r, g, b, 0xFF);
    SDL_RenderFillRect(getMainRenderer(), &fillRect);
}

void BaseGameEngine::renderRectangle(int x, int y, int width, int height, SDL_Color color)
{
    SDL_Rect fillRect = { x, y, width, height };
    SDL_SetRenderDrawColor(getMainRenderer(), color.r, color.g, color.b, 0xFF);
    SDL_RenderFillRect(getMainRenderer(), &fillRect);
}

void BaseGameEngine::renderRectangle(int x, int y, int width, int height, int r, int g, int b, int a)
{
    SDL_Rect fillRect = { x, y, width, height };
    SDL_SetRenderDrawColor(getMainRenderer(), r, g, b, a);
    SDL_RenderFillRect(getMainRenderer(), &fillRect);
}

int BaseGameEngine::getTextureWidth(int textureKey) {
    return textures[textureKey].width;
}

int BaseGameEngine::getTextureHeight(int textureKey) {
    return textures[textureKey].height;
}

int BaseGameEngine::getTextTextureWidth(std::string text) {
    std::string key = text + std::to_string(0) + std::to_string(0) + std::to_string(0) + std::to_string(0);
    if (textTextures.find(key) == textTextures.end())
    {
        textTextures[key] = createTextTexture(text, {0, 0, 0});
    }

    return getTextureWidth(textTextures[key]);
}

int BaseGameEngine::getTextTextureHeight(std::string text) {
    std::string key = text + std::to_string(0) + std::to_string(0) + std::to_string(0) + std::to_string(0);
    if (textTextures.find(key) == textTextures.end())
    {
        textTextures[key] = createTextTexture(text, { 0, 0, 0 });
    }

    return getTextureHeight(textTextures[key]);
}

double BaseGameEngine::getProbFromSigmoid(double skill, double difficulty)
{
    return sigmoid(skill / difficulty);
}

void BaseGameEngine::setSigmoidFunction(double omega, double alpha)
{
    sigmoidOmega = omega;
    sigmoidAlpha = alpha;
}

double BaseGameEngine::sigmoid(double x)
{
    return pow(x, sigmoidAlpha) / (pow(x, sigmoidAlpha) + pow(sigmoidOmega, sigmoidAlpha));
}

double BaseGameEngine::pickElementByProbability(std::vector<ChanceObject> items)
{
    double testNumber = randomDouble();
    double cumulativeProbability = 0.0;
    for (auto item : items) {
        cumulativeProbability += item.weight;
        if (testNumber <= cumulativeProbability) {
            return item.value;
        }
    }
}

void BaseGameEngine::setTicksPerSecond(int newTicksPerScond)
{
    ticksPerSecond = newTicksPerScond;
    tickDelay = 1000 / newTicksPerScond;
}

int BaseGameEngine::getScreenRefreshRate()
{
    SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
    SDL_GetDisplayMode(0, 0, &mode);
    return mode.refresh_rate;
}

void BaseGameEngine::addScene(int sceneId, GameScene* sceneToAdd)
{
    scenes[sceneId] = sceneToAdd;
}

void BaseGameEngine::setNextScene(int sceneId)
{
    nextScene = scenes[sceneId];
}

double BaseGameEngine::randomDouble() {
    return (double) rand() / RAND_MAX;
}

int BaseGameEngine::randomInt(int maxValue) {
    return rand() % (maxValue + 1);
}

int BaseGameEngine::randomInt(int minValue, int maxValue) {
    int returnInt = rand() % (maxValue - minValue + 1) + minValue;
    return returnInt;
}

//this method will be ovverridden in child class
void BaseGameEngine::loadAssets() {

}

//this method will be ovverridden in child class
void BaseGameEngine::handleInput() {
    
}

//this method will be ovverridden in child class
void BaseGameEngine::gameLogic() {

}

//this method will be ovverridden in child class
void BaseGameEngine::gameRendering() {

}

void BaseGameEngine::startMainGameLoop() {

    gameRunning = true;

    while (gameRunning)
    {
        gameRunning = currentScene->sceneRunning =  initNextScene();
        while (currentScene->sceneRunning)
        {
            //handle input
            SDL_AtomicLock(&sceneLock);
            currentScene->handleInput();
            currentScene->clearInputMessages();
            SDL_AtomicUnlock(&sceneLock);

            //clear screen
            SDL_SetRenderDrawColor(getMainRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(getMainRenderer());
            //call scene rendering
            SDL_AtomicLock(&sceneLock);
            currentScene->renderScene();
            currentScene->drawMenus();
            currentScene->drawPrompts();
            SDL_AtomicUnlock(&sceneLock);
            //Update screen
            SDL_RenderPresent(getMainRenderer());
        }
    }
}

//private methods
bool BaseGameEngine::initNextScene() {
    SDL_AtomicLock(&sceneRunningLock);
    if (nextScene != NULL)
    {
        currentScene = nextScene;
        nextScene = NULL;
        loadSceneTextures(currentScene);
        currentScene->setUpScene();
        currentScene->sceneRunning = true;
        SDL_CreateThread(logicThread, "logicThread", (void*)currentScene);
        return true;
    }
    else {
        SDL_AtomicUnlock(&sceneRunningLock);
        return false;
    }
}

bool BaseGameEngine::loadSceneTextures(GameScene * newScene) {
    currentScene->declareSceneAssets();
    clearTextures();
    createMultipleTextures(newScene->texturesToLoad);
    return true;
}

bool BaseGameEngine::clearTextures() {
    for (auto i = textures.begin(); i != textures.end(); ++i) {
        if (i->second.texture != NULL)
        {
            SDL_DestroyTexture(i->second.texture);
            i->second.texture = NULL;
        }
    }
    textures.clear();
    textTextures.clear();
    auto_texturekey = AUTO_TEXTURE_KEY_START;
    createImageTexture(DEFAULT_BUTTON_TEXTURE_ID, DEFAULT_BUTTON_TEXTURE_PATH);
    return true;
}

//functions
int logicThread(void* scene) {
    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
    srand(time(NULL));
    double lastLogicTickStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double initialLogicTickStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int timeToWait = 0;
    static_cast <GameScene*> (scene)->timeToWaitDiscount = 0;
    int tickCount = 0;
    while (static_cast <GameScene*> (scene)->sceneRunning)
    {
        tickCount++;
        //std::cout << (tickCount / ((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) - initialLogicTickStamp)) * 1000;
        //std::cout << "\n";
        timeToWait = static_cast <GameScene*> (scene)->engine->tickDelay - (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - lastLogicTickStamp) + static_cast <GameScene*> (scene)->timeToWaitDiscount;
        if (timeToWait >= 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
            static_cast <GameScene*> (scene)->timeToWaitDiscount = 0;
        }
        else {
            static_cast <GameScene*> (scene)->timeToWaitDiscount = timeToWait;
            std::cout << " \ntime to wait: ";
            std::cout << static_cast <GameScene*> (scene)->timeToWaitDiscount;
            std::cout << "\n";
        }
        //std::cout << "\nlast tick duration: ";
        //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - lastLogicTickStamp;
        //std::cout << "\n";
        lastLogicTickStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        SDL_AtomicLock(&static_cast <GameScene*> (scene)->engine->sceneLock);
        static_cast <GameScene*> (scene)->sceneLogic();
        static_cast <GameScene*> (scene)->setLastTickTimeStamp();
        SDL_AtomicUnlock(&static_cast <GameScene*> (scene)->engine->sceneLock);
    }
    return 0;
}


std::string getChanceObjectSaveString(ChanceObject chanceObject)
{
    std::string saveString;
    int uniqueObjectId = getUniqueId();

    saveString = BEGIN_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(CHANCE_OBJECT) + "\n";
    saveString += getAttributeString(getUniqueId(), CHANCE_OBJECT_WEIGHT, chanceObject.weight);
    saveString += getAttributeString(getUniqueId(), CHANCE_OBJECT_VALUE, chanceObject.value);
    saveString += END_OBJECT_IDENTIFIER + std::to_string(uniqueObjectId) + "-" + std::to_string(CHANCE_OBJECT) + "\n";
    return saveString;
}

ChanceObject getChanceObjectFromSaveObject(SaveObject saveObject)
{
    ChanceObject returnChanceObject = ChanceObject{ 0, 0 };
    for (int i = 0; i < saveObject.attributes.size(); i++)
    {
        switch (saveObject.attributes[i].attributeType) {
        case CHANCE_OBJECT_WEIGHT:
            returnChanceObject.weight = stoi(saveObject.attributes[i].valueString);
            break;
        case CHANCE_OBJECT_VALUE:
            returnChanceObject.value = stoi(saveObject.attributes[i].valueString);
            break;
        default:
            break;
        }
    }
    return returnChanceObject;
}

std::vector<ChanceObject> getChanceObjectVectorFromSaveObject(std::string saveString){
    std::vector<ChanceObject> returnVector;

    std::vector<SaveObject> savedObjects = getSaveObjectVectorFromSaveString2(saveString);

    for (size_t i = 0; i < savedObjects.size(); i++)
    {
        returnVector.push_back(getChanceObjectFromSaveObject(savedObjects[i].rawString));
    }


    return returnVector;
}

std::string getChancObjectVectorSaveString(std::vector<ChanceObject> vector) {
    std::string returnString;
    returnString += std::to_string(vector.size()) + "\n";
    for (int i = 0; i < vector.size(); i++)
    {
        returnString += getChanceObjectSaveString(vector[i]) + "\n";
    }
    return returnString;
}

bool stringIsAnInt(std::string string)
{
    for (char& c : string) {
        if(!std::isdigit(c)){
            return false;
        }
    }
    return true;
}
