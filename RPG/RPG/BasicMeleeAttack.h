#pragma once
#include "Attack.h"
#include "Animation.h"


class GameScene;
class Unit;

class BasicMeleeAttack : public Attack
{
public:
    //attribues
    int animationKey;

    //constructors
    BasicMeleeAttack();
    BasicMeleeAttack(int newType, Unit* newOwningUnit);

    //methods
    bool startAttack() override;
    void processHit(Unit* targetUnit);
    void processAttack();

private:
    //methods
    void init();
    int damageDealt();
};

