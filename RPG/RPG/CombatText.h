#pragma once
#include <string>
#include <SDL.h>

class CombatText
{
public:
    //attributes
    std::string text;
    int tileX, tileY, duration, tickCount, xSpeed, ySpeed, delay;
    SDL_Color colour;

    //constructors
    CombatText();
    CombatText(std::string newText, int newTileX, int newTileY);
    CombatText(std::string newText, int newTileX, int newTileY, int newDuration);
    CombatText(std::string newText, SDL_Color textColour, int newTileX, int newTileY);
    CombatText(std::string newText, SDL_Color textColour, int newTileX, int newTileY, int newDuration);
    CombatText(int delay, std::string newText, int newTileX, int newTileY);
    CombatText(int delay, std::string newText, int newTileX, int newTileY, int newDuration);
    CombatText(int delay, std::string newText, SDL_Color textColour, int newTileX, int newTileY);
    CombatText(int delay, std::string newText, SDL_Color textColour, int newTileX, int newTileY, int newDuration);

private:
    //methods
    void init();
    void init(std::string newText, int newTileX, int newTileY);
    void init(std::string newText, int newTileX, int newTileY, int newDuration);
};

