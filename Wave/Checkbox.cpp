#include "Checkbox.h"

Gui::Checkbox::Checkbox(int32_t x, int32_t y, double scale, bool checked, int32_t id) : x(x), y(y), scale(scale), checked(checked), id(id) {
	if(!textureNotChecked.loadFromFile("textures/checkbox_empty.png"))
			throw std::exception("checkbox_empty.png");

	if(!textureChecked.loadFromFile("textures/checkbox_checked.png"))
			throw std::exception("checkbox_checked.png not found!");
}

void Gui::Checkbox::render(sf::RenderWindow& window) {
	sf::Sprite spr(checked ? textureChecked : textureNotChecked);
	spr.setScale(scale, scale);
	spr.setPosition(x, y - spr.getGlobalBounds().height / 2 + 5);

	width  = spr.getGlobalBounds().width;
	height = spr.getGlobalBounds().height;

	window.draw(spr);
}

void Gui::Checkbox::click() {
	checked = !checked;
}

bool Gui::Checkbox::isChecked() {
	return checked;
}

int32_t Gui::Checkbox::getId() {
	return id;
}

bool Gui::Checkbox::getId(int32_t id) {
	return id == this->id;
}

int32_t Gui::Checkbox::getX() {
	return x;
}

int32_t Gui::Checkbox::getY() {
	return y;
}

int32_t Gui::Checkbox::getWidth() {
	return width;
}

int32_t Gui::Checkbox::getHeight() {
	return height;
}

double Gui::Checkbox::getScale() {
	return scale;
}