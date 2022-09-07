#pragma once
#include "RpgGameConstants.h"

class RpgUnit;
class DooDad;

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
    virtual bool startAttack(int x, int y);
    virtual void processHit(RpgUnit* targetUnit) {};
    virtual void processHit(DooDad* targetUnit) {};
    virtual void update();
    virtual void processAttack() {};

private:
    //attributes

    //methods
    void init();
};

