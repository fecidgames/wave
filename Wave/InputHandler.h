#pragma once

#include "MenuRenderer.h"
#include "EntityHandler.h"

class InputHandler {

public:
	InputHandler(MenuRenderer& menuRenderer, EntityHandler& entityHandler);

	void update(sf::Event* e);

	bool mouseOver(double mx, double my, double x, double y, double width, double height);
	bool mouseOver(double mx, double my, Gui::Button* button);

	void tick();

private:
	MenuRenderer* menuRenderer;
	EntityHandler* entityHandler;

	GameState& gameState;

	bool keyDown[4] = {};
};

