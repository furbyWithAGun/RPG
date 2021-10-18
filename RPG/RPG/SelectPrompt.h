#pragma once
#include "Prompt.h"
#include "MenuText.h"
#include <functional>

class SelectPrompt : public Prompt
{
public:
    //attributes
    struct SelectOption {
        std::string text;
        int returnValue;
        MenuText* displayText;
    };
    bool closeOnClickMiss;

    //constructors
    SelectPrompt();
    SelectPrompt(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    SelectPrompt(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight);
    //destructors
    ~SelectPrompt() override;

    //methods
    SelectPrompt* addSelectOption(std::string newDisplayTest, int newReturnValue);
    int getSelectedOptionValue();
    bool handleInput(InputMessage* message) override;
    void draw() override;
    void free();


private:
    //attributes
    std::vector<SelectOption*> selectOptions;
    SelectOption* selectedOption;

    //methods
    void init();
};

