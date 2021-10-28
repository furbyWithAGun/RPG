#include "TownCommand.h"
#include "Unit.h"

TownCommand::TownCommand() : DooDad()
{

}

TownCommand::TownCommand(TileGridScene* gameScene, int textureKey, int tileX, int tileY) : DooDad(gameScene, textureKey, tileX, tileY)
{
	init();
}

TownCommand::TownCommand(TileGridScene* gameScene, int tileX, int tileY) : DooDad(gameScene, tileX, tileY)
{
    init();
}

TownCommand::TownCommand(TileGridScene* gameScene) : DooDad(gameScene)
{
    init();
}

TownCommand::TownCommand(SaveObject saveObject, TileGridScene* gameScene) : DooDad(saveObject, gameScene)
{
	init();
}

void TownCommand::actionOn(Unit* unit, int actionType)
{
	SelectPrompt* townCommandPromp;
    townCommandPromp = new SelectPrompt(unit->scene, COLOR_BLACK, unit->scene->engine->screenWidth * 0.5, unit->scene->engine->screenHeight * 0.5, unit->scene->engine->screenWidth * 0.1, unit->scene->engine->screenHeight * 0.1);
    townCommandPromp->addSelectOption("Build Menu", 1);
    townCommandPromp->addCallBack([this, townCommandPromp, unit]() {
        switch (townCommandPromp->getSelectedOptionValue())
        {
        case 1:
            unit->scene->openMenu(TOWN_BUILD_MENU);
            unit->scene->closeMenu(RPG_OVERWORLD_MENU);
            break;
        default:
            break;
        }
        unit->scene->removePrompt(townCommandPromp);
        });
    townCommandPromp->active = true;
    townCommandPromp->closeOnClickMiss = true;
    unit->scene->addPrompt(townCommandPromp);
}

void TownCommand::init()
{
	type = DOODAD_TOWN_COMMAND;
    textureKey = TEXTURE_TOWN_COMMAND;
    passable = false;
}
