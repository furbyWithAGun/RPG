#include "UnitState.h"
#include "Unit.h"

//constructors
UnitState::UnitState() {
    init();
}

UnitState::UnitState(int newId, Unit* controlledUnit) {
    init();
    id = newId;
    unit = controlledUnit;
}

//private methods
void UnitState::init() {
    id = -1;
    unit = NULL;
}

int UnitState::update() {
    unit->updateCoords();
    updateAnimation();
    unit->updateMovement();
    return id;
}