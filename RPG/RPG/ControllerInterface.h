#pragma once
#include "InputMessage.h"
#include <vector>

enum BASIC_INPUT_MESSAGES {
    END_SCENE,
    K_ESC,
    K_BACKSPACE,
    K_ENTER,
    SELECT_ON,
    SELECT_OFF,
    TEXT_INPUT,
    POINTER_STATE,
    SCROLL_UP,
    SCROLL_DOWN,
    BUTTON_1_ON,
    BUTTON_1_OFF,
    NUM_BASIC_MESSAGES
};

class ControllerInterface
{
public:
    //attributes
    std::vector<InputMessage*> messageQueue;
    std::vector<InputMessage*> textInputQueue;
    int latestXpos, latestYpos;
    bool selectOn;
    bool shiftOn;
    bool ctrlOn;
    bool capsLockOn;

    //constructors
    ControllerInterface();

    //methods
    virtual void populateMessageQueue() {};
    void populateTextInputQueue();
    bool getNextMessage(InputMessage* message);
    void addMessage(InputMessage* message);
    void addMessage(InputMessage message);
    bool getNextTextInput(InputMessage* message);
    void addTextInput(InputMessage* message);
    void addTextInput(InputMessage message);
};

