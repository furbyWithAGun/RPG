#pragma once
#include <string>

class InputMessage {
public:
    //attributes
    int id, x, y, misc;
    std::string text;

    //constructors
    InputMessage();
    InputMessage(int messageId);
    InputMessage(int messageId, int xVal, int yVal);
    InputMessage(int messageId, int xVal, int yVal, std::string messageText);
    InputMessage(int messageId, int xVal, int yVal, int miscVal);

    //methods

private:
    void init();
    void init(int messageId);
    void init(int messageId, int xVal, int yVal);
};
