#pragma once
#include "ControllerInterface.h"

class RpgKeysMouseController : public ControllerInterface
{
public:
    //constructor
    RpgKeysMouseController();

    //methods
    void populateMessageQueue() override;

};

