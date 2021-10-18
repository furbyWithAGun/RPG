#include "InputMessage.h"

//constructors
InputMessage::InputMessage() {
    init();
}

InputMessage::InputMessage(int messageId) {
    init(messageId);
}

InputMessage::InputMessage(int messageId, int xVal, int yVal) {
    init(messageId, xVal, yVal);
}

InputMessage::InputMessage(int messageId, int xVal, int yVal, int miscVal) {
    init(messageId, xVal, yVal);
    misc = miscVal;
}

InputMessage::InputMessage(int messageId, int xVal, int yVal, std::string messageText) {
    init(messageId, xVal, yVal);
    text = messageText;
}

//private methods
void InputMessage::init() {
    id = x = y = misc = -1;
    text = "";
}

void InputMessage::init(int messageId) {
    init();
    id = messageId;
}

void InputMessage::init(int messageId, int xVal, int yVal)
{
    init(messageId);
    x = xVal;
    y = yVal;
}
