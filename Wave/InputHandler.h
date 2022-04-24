#pragma once

#include "MenuRenderer.h"
#include "EntityHandler.h"

class EntityHandler;
class Wave;

class InputHandler {

public:
	InputHandler(Wave& wave, MenuRenderer& menuRenderer, EntityHandler& entityHandler);

	void update(sf::Event* e);

	bool mouseOver(double mx, double my, double x, double y, double width, double height);
	bool mouseOver(double mx, double my, Gui::Button* button);
	bool mouseOver(double mx, double my, Gui::Slider* button);
	bool mouseOver(double mx, double my, Gui::Checkbox* button);
	bool mouseOver(double mx, double my, Gui::Arrow* button);
	bool mouseOverBlock(double mx, double my, Gui::Slider* slider);

	void tick();

private:
	MenuRenderer* menuRenderer;
	EntityHandler* entityHandler;

	Wave& wave;

	GameState& gameState;

	bool keyDown[4] = {};
};

