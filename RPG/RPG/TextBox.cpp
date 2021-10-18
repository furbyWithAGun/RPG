#include "TextBox.h"
  
const SDL_Color DEFAULT_TEXT_BOX_TEXT_COLOUR = { 0, 0, 0 };
const int DEFAULT_NUM_CHARS_TO_DISPLAY = 10;

TextBox::TextBox() : UiElement()
{
    init();
}

TextBox::TextBox(GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

TextBox::TextBox(int elementId, GameScene* gameScene, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(elementId, gameScene, xpos, ypos, elementWidth, elementHeight)
{
    init();
}

void TextBox::init()
{
    textColour = DEFAULT_TEXT_BOX_TEXT_COLOUR;
    numCharsToDisplay = DEFAULT_NUM_CHARS_TO_DISPLAY;
    gettingText = false;
    backgroundColour = { 255, 255, 255 };
}

void TextBox::draw() {
    if (active)
    {
        UiElement::draw();
        if (text.size() > numCharsToDisplay)
        {
            scene->engine->renderText(text.substr(text.size() - numCharsToDisplay, numCharsToDisplay), xpos, ypos, textColour);
        }
        else {
            scene->engine->renderText(text, xpos, ypos, textColour);
        }
    }
}

bool TextBox::handleInput(InputMessage* message) {
    bool messageConsumed = false;
    if (active)
    {
        switch (message->id)
        {
        case SELECT_ON:
            if (pointCollision(message->x, message->y))
            {
                gettingText = true;
                scene->gettingTextInput = true;
                messageConsumed = true;
            }
            else {
                gettingText = false;
                //scene->gettingTextInput = false;
            }
            break;
        case K_BACKSPACE:
            if (gettingText)
            {
                if (text.size() > 0) {

                    text.pop_back();
                }
                messageConsumed = true;
            }
            break;
        case K_ESC:
        case K_ENTER:
            gettingText = false;
            scene->gettingTextInput = false;
            messageConsumed = true;
            break;
        case TEXT_INPUT:
            if (gettingText)
            {
                text += message->text;
                messageConsumed = true;
            }
            break;
        default:
            break;
        }
    }
    return messageConsumed;
}

void TextBox::deactivate()
{
    UiElement::deactivate();
    gettingText = false;
}
