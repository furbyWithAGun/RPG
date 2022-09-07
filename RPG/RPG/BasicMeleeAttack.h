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
    bool startAttack(int x, int y) override;
    void processHit(RpgUnit* targetUnit) override;
    void processHit(DooDad* targetDooDad) override;
    void processAttack() override;

private:
    //methods
    void init();
    int damageDealt();
};

