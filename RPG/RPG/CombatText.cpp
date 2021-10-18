#include "CombatText.h"

const int DEFAULT_COMBAT_TEXT_DURATION = 30;
const int DEFAULT_COMBAT_TEXT_X_SPEED = 1;
const int DEFAULT_COMBAT_TEXT_Y_SPEED = 1;

CombatText::CombatText() {
    init();
}

CombatText::CombatText(std::string newText, int newTileX, int newTileY) {
    init(newText, newTileX, newTileY);
}

CombatText::CombatText(std::string newText, int newTileX, int newTileY, int newDuration) {
    init(newText, newTileX, newTileY, newDuration);
}

CombatText::CombatText(std::string newText, SDL_Color textColour, int newTileX, int newTileY) {
    init(newText, newTileX, newTileY);
    colour = textColour;
}

CombatText::CombatText(std::string newText, SDL_Color textColour, int newTileX, int newTileY, int newDuration) {
    init(newText, newTileX, newTileY, newDuration);
    colour = textColour;
}

CombatText::CombatText(int delay, std::string newText, int newTileX, int newTileY) {
    init(newText, newTileX, newTileY);
    (*this).delay = delay;
}

CombatText::CombatText(int delay, std::string newText, int newTileX, int newTileY, int newDuration) {
    init(newText, newTileX, newTileY, newDuration);
    (*this).delay = delay;
}

CombatText::CombatText(int delay, std::string newText, SDL_Color textColour, int newTileX, int newTileY) {
    init(newText, newTileX, newTileY);
    colour = textColour;
    (*this).delay = delay;
}

CombatText::CombatText(int delay, std::string newText, SDL_Color textColour, int newTileX, int newTileY, int newDuration) {
    init(newText, newTileX, newTileY, newDuration);
    colour = textColour;
    (*this).delay = delay;
}

//private Methods
void CombatText::init() {
    text = "";
    tileX = tileY = tickCount = 0;
    duration = DEFAULT_COMBAT_TEXT_DURATION;
    xSpeed = DEFAULT_COMBAT_TEXT_X_SPEED;
    ySpeed = DEFAULT_COMBAT_TEXT_Y_SPEED;
    colour = { 0, 0, 0 };
    delay = 0;
}

void CombatText::init(std::string newText, int newTileX, int newTileY)
{
    init();
    text = newText;
    tileX = newTileX;
    tileY = newTileY;
}

void CombatText::init(std::string newText, int newTileX, int newTileY, int newDuration)
{
    init(newText, newTileX, newTileY);
    duration = newDuration;
}
