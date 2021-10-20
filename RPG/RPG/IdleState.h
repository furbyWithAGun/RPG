#pragma once
#include "UnitState.h"

class RpgUnit;

class IdleState : public UnitState
{
public:
    //attributes
    RpgUnit* unit;

    //constructors
    IdleState();
    IdleState(int id, RpgUnit* controlledUnit);

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

