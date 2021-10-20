#pragma once
#include "Attack.h"
#include "Animation.h"


class GameScene;
class RpgUnit;

class BasicMeleeAttack : public Attack
{
public:
    //attribues
    int animationKey;

    //constructors
    BasicMeleeAttack();
    BasicMeleeAttack(int newType, RpgUnit* newOwningUnit);

    //methods
    bool startAttack() override;
    void processHit(RpgUnit* targetUnit);
    void processAttack();

private:
    //methods
    void init();
    int damageDealt();
};

