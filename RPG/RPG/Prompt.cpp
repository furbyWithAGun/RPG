#include "Prompt.h"

Prompt::Prompt() : UiElement() {
	init();
}

Prompt::Prompt(GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
	init();
}

Prompt::Prompt(int elementId, GameScene* gameScene, SDL_Color spriteBackgroundColour, int xpos, int ypos, int elementWidth, int elementHeight) : UiElement(elementId, gameScene, spriteBackgroundColour, xpos, ypos, elementWidth, elementHeight)
{
	init();
}

Prompt::~Prompt()
{
	free();
}

void Prompt::draw()
{
	if (active)
	{
		UiElement::draw();
	}
}

void Prompt::free()
{
	callback = NULL;
}

Prompt* Prompt::addCallBack(std::function<void()> newCallback)
{
	callback = newCallback;
	return this;
}

void Prompt::init()
{
	callback = NULL;
}
