#include "RpgKeysMouseController.h"
#include "BaseGameEngine.h"
#include "RpgGameConstants.h"

//constructors
RpgKeysMouseController::RpgKeysMouseController() : ControllerInterface() {

}

//methods
void RpgKeysMouseController::populateMessageQueue() {
    SDL_Event e;
    int x, y;
    SDL_GetMouseState(&x, &y);

    addMessage(InputMessage(POINTER_STATE, x, y));
    while (SDL_PollEvent(&e) != 0) {
        SDL_GetMouseState(&x, &y);
        latestXpos = x;
        latestYpos = y;
        switch (e.type)
        {
        case SDL_QUIT:
            addMessage(InputMessage(END_SCENE, x, y));
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (e.button.button)
            {
            case SDL_BUTTON_LEFT:
                selectOn = true;
                addMessage(InputMessage(SELECT_ON, x, y));
                break;
            case SDL_BUTTON_RIGHT:
                addMessage(InputMessage(BUTTON_1_ON, x, y));
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (e.button.button)
            {
            case SDL_BUTTON_LEFT:
                selectOn = false;
                addMessage(InputMessage(SELECT_OFF, x, y));
                break;
            case SDL_BUTTON_RIGHT:
                addMessage(InputMessage(BUTTON_1_OFF, x, y));
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            addMessage(InputMessage(POINTER_MOVEMENT, x, y));
            break;
        case SDL_MOUSEWHEEL:
            if (e.wheel.y > 0) {
                addMessage(InputMessage(SCROLL_UP, x, y));
            }
            else if (e.wheel.y < 0)
            {
                addMessage(InputMessage(SCROLL_DOWN, x, y));
            }
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_w:
                addMessage(InputMessage(BUTTON_2_ON, x, y));
                break;
            case SDLK_s:
                addMessage(InputMessage(BUTTON_3_ON, x, y));
                break;
            case SDLK_a:
                addMessage(InputMessage(BUTTON_4_ON, x, y));
                break;
            case SDLK_d:
                addMessage(InputMessage(BUTTON_5_ON, x, y));
                break;
            case SDLK_e:
                addMessage(InputMessage(BUTTON_6_ON, x, y));
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                shiftOn = true;
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym) {
            case SDLK_w:
                addMessage(InputMessage(BUTTON_2_OFF, x, y));
                break;
            case SDLK_s:
                addMessage(InputMessage(BUTTON_3_OFF, x, y));
                break;
            case SDLK_a:
                addMessage(InputMessage(BUTTON_4_OFF, x, y));
                break;
            case SDLK_d:
                addMessage(InputMessage(BUTTON_5_OFF, x, y));
                break;
            case SDLK_e:
                addMessage(InputMessage(BUTTON_6_OFF, x, y));
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                shiftOn = false;
            }
            break;
        default:
            break;
        }
    }
}
