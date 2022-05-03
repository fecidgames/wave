#pragma once

#include "STATE.h"

namespace Gui {

class Arrow {
public:
	Arrow(int32_t x, int32_t y, int32_t width, int32_t height, bool inverted, int32_t id);

	void render(sf::RenderWindow& window);

	int32_t getId();
	bool getId(int32_t id);

	int32_t getX();
	int32_t getY();
	int32_t getWidth();
	int32_t getHeight();

	bool isInverted();

private:
	int32_t x, y, width, height, id;
	bool inverted;
};

}

