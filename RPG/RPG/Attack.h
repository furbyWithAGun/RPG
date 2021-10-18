#pragma once
#include "RpgGameConstants.h"

class Unit;

class Attack
{
public:
    //attributes
    int type, range, damage, cooldownTimeLeft, cooldown, attackDelay, attackTime;
    Unit* owningUnit;

    //constructors
    Attack();
    Attack(int newType, Unit* newOwningUnit);

    //methods
    virtual bool startAttack();
    virtual void processHit(Unit* targetUnit) {};
    virtual void update();
    virtual void processAttack() {};

private:
    //attributes

    //methods
    void init();
};

