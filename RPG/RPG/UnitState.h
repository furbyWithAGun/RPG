#pragma once
#include "InputMessage.h"

class Unit;

class UnitState
{
public:
    //attributes

    //constructors
    UnitState();
    UnitState(int id, Unit* controlledUnit);

    //methods
    virtual int update();
    virtual int handleInput(InputMessage* message) { return id; };
    virtual void updateAnimation() {};

protected:
    //attributes
    int id;
    Unit* unit;

    //methods

private:
    //methods
    void init();
};

