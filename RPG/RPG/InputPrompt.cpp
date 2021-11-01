#include "InputPrompt.h"
#include "MenuButton.h"
#include "TextBox.h"
#include "MenuText.h"
#include "Prompt.h"

//constructors
InputPrompt::InputPrompt() : Prompt() {
    init();
}

InputPrompt::InputPrompt(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Prompt(gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

InputPrompt::InputPrompt(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Prompt(elementId, gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init();
    id = elementId;
}

InputPrompt::InputPrompt(GameScene* gameScene, std::string promptText, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Prompt(gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init(promptText);
}

InputPrompt::InputPrompt(int elementId, GameScene* gameScene, std::string promptText, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : Prompt(elementId, gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
    init(promptText);
    id = elementId;
}

InputPrompt::~InputPrompt()
{
    free();
}

bool InputPrompt::handleInput(InputMessage* message)
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
                    //scene->removePrompt(this);
                    //callback(enteredText);
                    toBeDeleted = true;
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

void InputPrompt::draw()
{
    if (active)
    {
        UiElement::draw();
    }
}

void InputPrompt::free()
{
    id = -1;
    callback = NULL;
}

InputPrompt* InputPrompt::addCallBack(std::function<void(std::string text)> newCallback)
{
    callback = newCallback;
    return this;
}

void InputPrompt::setInputText(std::string newInputText)
{
    getElementbyId(TXT_INPUT)->text = newInputText;
}

//private methods
void InputPrompt::init(std::string promptText) {
    init();
    prompt = promptText;
    MenuText* txtPrompt = new MenuText(scene, prompt, COLOR_WHITE, (xpos + (width - scene->engine->getTextTextureWidth(prompt)) / 2), ypos + height * 0.1);
    addElement(TXT_PROMPT,txtPrompt);
}

void InputPrompt::init() {
    id = 9999999;
    enteredText = "";
    prompt = "";
    callback = NULL;
    closeOnClickMiss = false;

    TextBox* txtInput = new TextBox(TXT_INPUT, scene, xpos + width * 0.1, ypos + height * 0.3, width * 0.7, scene->engine->screenHeight * 0.05);
    addElement(TXT_INPUT, txtInput);

    MenuButton* btnOk = new MenuButton(scene, DEFAULT_BUTTON_TEXTURE_ID, xpos + width * 0.2, ypos + height * 0.7);
    btnOk->setText("Ok")->addOnClick([this]() {
        enteredText = getElementbyId(TXT_INPUT)->text;
        this->callback(this->enteredText);
        this->toBeDeleted = true;
        });
    subElements.push_back(btnOk);

    MenuButton* btnCancel = new MenuButton(scene, DEFAULT_BUTTON_TEXTURE_ID, xpos + width * 0.6, ypos + height * 0.7);
    btnCancel->setText("Cancel")->addOnClick([this]() {
        this->toBeDeleted = true;
        });
    subElements.push_back(btnCancel);
}