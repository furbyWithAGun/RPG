#include "SelectPrompt.h"

//constructors
SelectPrompt::SelectPrompt() : Prompt(){
    init();
}

SelectPrompt::SelectPrompt(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Prompt(gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

SelectPrompt::SelectPrompt(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Prompt(elementId, gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init();
    id = elementId;
}

SelectPrompt::~SelectPrompt()
{
    free();
}

SelectPrompt* SelectPrompt::addSelectOption(std::string newDisplayTest, int newReturnValue)
{
    SelectOption* newOption = new SelectOption;
    newOption->text = newDisplayTest;
    newOption->returnValue = newReturnValue;
    newOption->displayText = new MenuText(scene, newDisplayTest, COLOR_WHITE, xpos, ypos);
    selectOptions.push_back(newOption);
    return this;
}

int SelectPrompt::getSelectedOptionValue()
{
    return selectedOption->returnValue;
}

bool SelectPrompt::handleInput(InputMessage* message)
{
    bool messageConsumed = false;
    if (active)
    {
        for (auto element : subElements) {
            if (!messageConsumed)
            {
                messageConsumed = element->handleInput(message);
            }
        }

        if (!messageConsumed)
        {
            switch (message->id)
            {
            case SELECT_ON:
                if (closeOnClickMiss && !pointCollision(message->x, message->y)) {
                    scene->removePrompt(this);
                }
                for (auto selectOption : selectOptions) {
                    if (selectOption->displayText->pointCollision(message->x, message->y))
                    {
                        selectedOption = selectOption;
                        callback();
                        return true;
                    }
                }
                break;
            default:
                break;
            }
        }
        if (!messageConsumed)
        {
            messageConsumed = Prompt::handleInput(message);
        }
    }
    return messageConsumed;
}

void SelectPrompt::draw()
{
    if (active)
    {
        UiElement::draw();
        for (int i = 0; i < selectOptions.size(); i++) {
            selectOptions[i]->displayText->xpos = xpos + (width - selectOptions[i]->displayText->width) / 2;
            selectOptions[i]->displayText->ypos = (ypos + (i + 1) * (((height - selectOptions.size() * selectOptions[i]->displayText->height)) / (selectOptions.size() + 1))) + (i) * selectOptions[i]->displayText->height;
            selectOptions[i]->displayText->draw();
        }
    }
}

void SelectPrompt::free()
{
    id = -1;
    for (auto selectOption: selectOptions) {
        if (selectOption != nullptr) {
            delete selectOption->displayText;
            delete selectOption;
        }
    }
    selectOptions.clear();
    selectedOption = nullptr;
    callback = NULL;
}

//private methods
void SelectPrompt::init() {
    id = 0;
    selectedOption = nullptr;
    callback = NULL;
    closeOnClickMiss = false;
}