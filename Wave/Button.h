#pragma once

#include "STATE.h"
#include <iostream>
#include <initializer_list>

namespace Gui {

class Button {

public:
	Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id);

	void render(sf::RenderWindow& window);

	void press();
	void release();

	void hover();
	void unHover();

	void notify();

	int32_t getId();
	bool getId(int32_t id);
	bool getId(std::initializer_list<int> ids);

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

