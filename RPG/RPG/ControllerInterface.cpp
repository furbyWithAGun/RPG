#include "ControllerInterface.h"
#include "BaseGameEngine.h"

//constructors
ControllerInterface::ControllerInterface() {
    latestXpos = latestYpos = 0;
    selectOn = shiftOn = capsLockOn = false;
}

//public methods
bool ControllerInterface::getNextMessage(InputMessage* message) {
    if (messageQueue.size() > 0)
    {
        *message = *messageQueue[0];
        delete messageQueue[0];
        messageQueue.erase(messageQueue.begin());
        return true;
    }
    else {
        message = NULL;
        return false;
    }
}

void ControllerInterface::addMessage(InputMessage* newMessage) {
    InputMessage* message = new InputMessage();
    *message = *newMessage;
    messageQueue.push_back(message);
    delete newMessage;
}

void ControllerInterface::addMessage(InputMessage newMessage) {
    InputMessage* message = new InputMessage();
    *message = newMessage;
    messageQueue.push_back(message);
}

bool ControllerInterface::getNextTextInput(InputMessage* message) {
    if (textInputQueue.size() > 0)
    {
        *message = *textInputQueue[0];
        delete textInputQueue[0];
        textInputQueue.erase(textInputQueue.begin());
        return true;
    }
    else {
        message = NULL;
        return false;
    }
}

void ControllerInterface::addTextInput(InputMessage* newMessage) {
    InputMessage* message = new InputMessage();
    *message = *newMessage;
    textInputQueue.push_back(message);
}

void ControllerInterface::addTextInput(InputMessage newMessage) {
    InputMessage* message = new InputMessage();
    *message = newMessage;
    textInputQueue.push_back(message);
}

void ControllerInterface::populateTextInputQueue()
{
    SDL_Event e;
    int xpos, ypos;
    while (SDL_PollEvent(&e) != 0) {
        SDL_GetMouseState(&xpos, &ypos);
        latestXpos = xpos;
        latestYpos = ypos;
        switch (e.type)
        {
        case SDL_QUIT:
            addTextInput(InputMessage(END_SCENE, xpos, ypos));
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button)
            {
            case SDL_BUTTON_LEFT:
                selectOn = true;
                addMessage(InputMessage(SELECT_ON, xpos, ypos));
                break;
            case SDL_BUTTON_RIGHT:
                addMessage(InputMessage(K_ESC, xpos, ypos));
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            selectOn = false;
            addTextInput(InputMessage(SELECT_OFF, xpos, ypos));
            break;
        case SDL_MOUSEWHEEL:
            if (e.wheel.y > 0) {
                addTextInput(InputMessage(SCROLL_UP, xpos, ypos));
            }
            else if (e.wheel.y < 0)
            {
                addTextInput(InputMessage(SCROLL_DOWN, xpos, ypos));
            }
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_CAPSLOCK:
                capsLockOn = !capsLockOn;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                shiftOn = true;
                break;
            case SDLK_BACKSPACE:
                addTextInput(InputMessage(K_BACKSPACE, xpos, ypos, e.text.text));
                break;
            case SDLK_ESCAPE:
                addTextInput(InputMessage(K_ESC, xpos, ypos, e.text.text));
                break;
            case SDLK_RETURN:
                addTextInput(InputMessage(K_ENTER, xpos, ypos, e.text.text));
                break;
            case SDLK_RETURN2:
                addTextInput(InputMessage(K_ENTER, xpos, ypos, e.text.text));
                break;
            case SDLK_KP_ENTER:
                addTextInput(InputMessage(K_ENTER, xpos, ypos, e.text.text));
                break;
            case SDLK_SPACE:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, " "));
                break;
            case SDLK_0:
            case SDLK_KP_0:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "0"));
                break;
            case SDLK_1:
            case SDLK_KP_1:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "1"));
                break;
            case SDLK_2:
            case SDLK_KP_2:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "2"));
                break;
            case SDLK_3:
            case SDLK_KP_3:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "3"));
                break;
            case SDLK_4:
            case SDLK_KP_4:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "4"));
                break;
            case SDLK_5:
            case SDLK_KP_5:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "5"));
                break;
            case SDLK_6:
            case SDLK_KP_6:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "6"));
                break;
            case SDLK_7:
            case SDLK_KP_7:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "7"));
                break;
            case SDLK_8:
            case SDLK_KP_8:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "8"));
                break;
            case SDLK_9:
            case SDLK_KP_9:
                addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "9"));
                break;
            case SDLK_q:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "Q"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "q"));
                }
                break;
            case SDLK_w:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "W"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "w"));
                }
                break;
            case SDLK_e:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "E"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "e"));
                }
                break;
            case SDLK_r:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "R"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "r"));
                }
                break;
            case SDLK_t:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "T"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "t"));
                }
                break;
            case SDLK_y:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "Y"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "y"));
                }
                break;
            case SDLK_u:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "U"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "u"));
                }
                break;
            case SDLK_i:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "I"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "i"));
                }
                break;
            case SDLK_o:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "O"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "o"));
                }
                break;
            case SDLK_p:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "P"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "p"));
                }
                break;
            case SDLK_a:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "A"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "a"));
                }
                break;
            case SDLK_s:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "S"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "s"));
                }
                break;
            case SDLK_d:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "D"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "d"));
                }
                break;
            case SDLK_f:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "F"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "f"));
                }
                break;
            case SDLK_g:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "G"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "g"));
                }
                break;
            case SDLK_h:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "H"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "h"));
                }
                break;
            case SDLK_j:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "J"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "j"));
                }
                break;
            case SDLK_k:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "K"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "k"));
                }
                break;
            case SDLK_l:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "L"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "l"));
                }
                break;
            case SDLK_z:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "Z"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "z"));
                }
                break;
            case SDLK_x:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "X"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "x"));
                }
                break;
            case SDLK_c:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "C"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "c"));
                }
                break;
            case SDLK_v:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "V"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "v"));
                }
                break;
            case SDLK_b:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "B"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "b"));
                }
                break;
            case SDLK_n:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "N"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "n"));
                }
                break;
            case SDLK_m:
                if (shiftOn || capsLockOn)
                {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "M"));
                }
                else {
                    addTextInput(InputMessage(TEXT_INPUT, xpos, ypos, "m"));
                }
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                shiftOn = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}