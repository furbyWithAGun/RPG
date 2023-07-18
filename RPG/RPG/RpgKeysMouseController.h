#pragma once
#include "ControllerInterface.h"
#include <unordered_map>


const int DEFAULT_MS_DOUBLE_PRESS_DELAY = 500;

class RpgKeysMouseController : public ControllerInterface
{
public:
    //constructor
    RpgKeysMouseController();

    //methods
    void populateMessageQueue() override;



private:
    //attributes
    std::unordered_map<int, int> buttonLastPressStamp;

};

