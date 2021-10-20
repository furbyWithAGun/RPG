#pragma once
#include "UnitState.h"
#include "RpgUnit.h"
class AttackingState : public UnitState
{
public:
    //attributes
    RpgUnit* unit;

    //constructors
    AttackingState();
    AttackingState(int id, RpgUnit* controlledUnit);

    //methods
    virtual int update();
    virtual int handleInput(InputMessage* message);

protected:
    //attributes

private:
    //methods
};

