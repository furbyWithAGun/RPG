#pragma once
#include "UnitState.h"
class MovingState : public UnitState
{
public:
    //attributes

    //constructors
    MovingState();
    MovingState(int id, Unit* controlledUnit);

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

