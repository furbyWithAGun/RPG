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

protected:
    //attributes
    int id;
    Unit* unit;

    //methods
    virtual void updateAnimation() {};

private:
    //methods
    void init();
};

