#pragma once
#include <string>
#include <vector>

class InputMessage {
public:
    //attributes
    int id, x, y, misc;
    std::string text;
    std::vector<int> params;

    //constructors
    InputMessage();
    InputMessage(int messageId);
    InputMessage(int messageId, int xVal, int yVal);
    InputMessage(int messageId, int xVal, int yVal, std::string messageText);
    InputMessage(int messageId, int xVal, int yVal, int miscVal);
    InputMessage(int messageId, int xVal, int yVal, int miscVal, std::vector<int> paramsVal);

    //methods

private:
    void init();
    void init(int messageId);
    void init(int messageId, int xVal, int yVal);
};
