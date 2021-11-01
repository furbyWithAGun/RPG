#pragma once
#include "Prompt.h"

enum INPUT_PROMPT_ELEMENT_IDS {
    TXT_INPUT,
    TXT_PROMPT
};


class InputPrompt : public Prompt
{
public:
    //attributes
    bool closeOnClickMiss;
    std::string enteredText;
    std::string prompt;

    //constructors
    InputPrompt();
    InputPrompt(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    InputPrompt(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    InputPrompt(GameScene* gameScene, std::string promptText,SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    InputPrompt(int elementId, GameScene* gameScene, std::string promptText, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    //destructors
    ~InputPrompt() override;

    //methods
    bool handleInput(InputMessage* message) override;
    void draw() override;
    void free();
    InputPrompt* addCallBack(std::function<void(std::string text)> newCallback);
    void setInputText(std::string newInputText);


private:
    //attributes
    std::function<void(std::string text)> callback;

    //methods
    void init();
    void init(std::string promptText);
};

