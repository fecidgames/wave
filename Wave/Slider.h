#pragma once

#include "STATE.h"

namespace Gui {

class Slider {
public:
	Slider(int32_t x, int32_t y, int32_t length, int32_t blockWidth, int32_t blockHeight, int32_t id);

	void render(sf::RenderWindow& window);

	void hover();
	void unHover();

	void drag();
	void release();

	bool isDragging();

	int32_t getMXR();
	void setMXR(int32_t mxr);

	int32_t getId();
	bool getId(int32_t id);

	int32_t getX();
	int32_t getY();

	int32_t getLength();
	int32_t getBlockWidth();
	int32_t getBlockHeight();
	int32_t getBlockX();
	void setBlockX(int32_t blockX);

private:
	int32_t x, y, length, blockWidth, blockHeight, id, blockX = 0;
	int32_t mxr;

	bool hovering = false;
	bool dragging = false;
};

}

