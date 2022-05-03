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

	bool mouseOver(sf::Event::MouseMoveEvent mb, Gui::Button* button);
	bool mouseOver(sf::Event::MouseButtonEvent mb, Gui::Button* button);
	bool mouseOver(sf::Event::MouseButtonEvent mb, Gui::Slider* slider);
	bool mouseOver(sf::Event::MouseButtonEvent mb, Gui::Checkbox* checkbox);
	bool mouseOver(sf::Event::MouseButtonEvent mb, Gui::Arrow* arrow);
	bool mouseOverBlock(sf::Event::MouseButtonEvent mb, Gui::Slider* slider);

	void tick();

	bool type(sf::Event* e, sf::Event::EventType type);

private:
	MenuRenderer* menuRenderer;
	EntityHandler* entityHandler;

	Wave& wave;

	GameState& gameState;

	bool keyDown[4] = {};
};

