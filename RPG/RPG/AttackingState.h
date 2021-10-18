#pragma once
#include "UnitState.h"
class AttackingState : public UnitState
{
public:
    //attributes

    //constructors
    AttackingState();
    AttackingState(int id, Unit* controlledUnit);

    //methods
    virtual int update();
    virtual int handleInput(InputMessage* message);

protected:
    //attributes

private:
    //methods
};

