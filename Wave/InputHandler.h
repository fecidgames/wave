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

	bool mo(sf::Event::MouseButtonEvent mb, int32_t x, int32_t y, int32_t width, int32_t height);
	bool mo(sf::Event::MouseMoveEvent mb, int32_t x, int32_t y, int32_t width, int32_t height);

	void handleButtonPresses(sf::Event* e);
	void handleSliderPresses(sf::Event* e);
	void handleArrowPresses(sf::Event* e);
	void handleCheckboxPresses(sf::Event* e);

	Wave& wave;

	GameState& gameState;

	bool keyDown[4] = {};
};

