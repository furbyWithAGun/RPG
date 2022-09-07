#pragma once
#include "Attack.h"
class GameScene;
class RpgUnit;

class BasicRangedAttack : public Attack
{
public:
    //attribues
    int animationKey;

    //constructors
    BasicRangedAttack();
    BasicRangedAttack(int newType, RpgUnit* newOwningUnit);

    //methods
    bool startAttack(int x, int y) override;
    void processHit(RpgUnit* targetUnit) override;
    void processHit(DooDad* targetDooDad) override;
    void processAttack() override;

private:
    //attributes
    int xTarget, yTarget;
    //methods
    void init();
    int damageDealt();
};


