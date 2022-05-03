#include "Arrow.h"

Gui::Arrow::Arrow(int32_t x, int32_t y, int32_t width, int32_t height, bool inverted, int32_t id) : x(x), y(y), width(width), height(height), id(id), inverted(inverted) {

}

void Gui::Arrow::render(sf::RenderWindow& window) {
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(x, y));
	triangle.setPoint(1, sf::Vector2f(x, y + height));

	if(!inverted)
		triangle.setPoint(2, sf::Vector2f(x + width, y + height / 2));
	if(inverted)
		triangle.setPoint(2, sf::Vector2f(x - width, y + height / 2));

	window.draw(triangle);
}

int32_t Gui::Arrow::getId() {
	return id;
}

bool Gui::Arrow::getId(int32_t id) {
	return id == this->id;
}

int32_t Gui::Arrow::getX() {
	return x;
}

int32_t Gui::Arrow::getY() {
	return y;
}

int32_t Gui::Arrow::getWidth() {
	return width;
}

int32_t Gui::Arrow::getHeight() {
	return height;
}

bool Gui::Arrow::isInverted() {
	return inverted;
}