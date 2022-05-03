#pragma once

#include "STATE.h"

namespace Gui {

class Button {

public:
	Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id);

	void render(sf::RenderWindow& window);

	void press();
	void release();

	void hover();
	void unHover();

	int32_t getId();
	bool getId(int32_t id);

	float_t getX();
	float_t getY();
	float_t getWidth();
	float_t getHeight();

	std::string getText();

private:
	float_t x, y;
	float_t width, height;

	std::string text;

	int32_t id;

	bool down = false;
	bool hovering = false;
};

}

