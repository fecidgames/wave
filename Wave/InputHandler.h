#pragma once

#include "MenuRenderer.h"

class InputHandler {

public:
	InputHandler(MenuRenderer& menuRenderer);

	void update(sf::Event* e);

	bool mouseOver(float_t mx, float_t my, float_t x, float_t y, float_t width, float_t height);
	bool mouseOver(float_t mx, float_t my, Gui::Button* button);

private:
	MenuRenderer* menuRenderer;
	GameState& gameState;

};

