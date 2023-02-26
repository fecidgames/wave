#pragma once

#include "STATE.h"

namespace Gui {

class Checkbox {
public:
	Checkbox(int32_t x, int32_t y, double scale, bool checked, int32_t id);

	void render(sf::RenderWindow& window);

	void click();

	bool isChecked();

	int32_t getId();
	bool getId(int32_t id);

	int32_t getX();
	int32_t getY();
	int32_t getWidth();
	int32_t getHeight();
	double getScale();

	int32_t getLayer() { return layer; }


private:
	bool checked = true;
	int32_t x, y, width = 0, height = 0, id;
	double scale;
	sf::Texture textureChecked;
	sf::Texture textureNotChecked;

	int32_t layer = 1;

	sf::Sprite spr;
};

}

