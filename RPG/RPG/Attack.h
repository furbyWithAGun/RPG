#pragma once
#include "RpgGameConstants.h"

class RpgUnit;

class Attack
{
public:
    //attributes
    int type, range, damage, cooldownTimeLeft, cooldown, attackDelay, attackTime;
    RpgUnit* owningUnit;

    //constructors
    Attack();
    Attack(int newType, RpgUnit* newOwningUnit);

    //methods
    virtual bool startAttack();
    virtual void processHit(RpgUnit* targetUnit) {};
    virtual void update();
    virtual void processAttack() {};

private:
    //attributes

    //methods
    void init();
};

