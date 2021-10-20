#pragma once
#include "UnitState.h"

class RpgUnit;

class MovingState : public UnitState
{
public:
    //attributes
    RpgUnit* unit;

    //constructors
    MovingState();
    MovingState(int id, RpgUnit* controlledUnit);

    //methods
    virtual int update();
    virtual int handleInput(InputMessage* message);

protected:
    //attributes

    //methods
    void updateAnimation() override;

private:
    //methods
};

