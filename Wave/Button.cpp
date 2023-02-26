#include "Button.h"

Gui::Button::Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id, int32_t layer) : layer(layer), x(x), y(y), width(width), height(height), text(text), id(id) {

}

void Gui::Button::render(sf::RenderWindow& window) {
	sf::RectangleShape btnShape(sf::Vector2f(!hovering ? width : width + 6, !hovering ? height : height + 6));
	btnShape.setPosition(!hovering ? x : x - 3, !hovering ? y : y - 3);
	btnShape.setOutlineThickness(1.0f);
	btnShape.setFillColor(!down ? sf::Color::Black : sf::Color::White);
	btnShape.setOutlineColor(sf::Color::White);

	sf::Font f;
	f.loadFromFile("fonts/mainFont.ttf");

	sf::Text btnText(text, f, 35);
	while(btnText.getGlobalBounds().width > btnShape.getGlobalBounds().width)
		btnText.setCharacterSize((uint32_t) (btnText.getCharacterSize() - 2.5));

	btnText.setPosition((int) (x + (width / 2) - btnText.getGlobalBounds().width / 2), (int) (y + (height / 2) - btnText.getGlobalBounds().height / 2 ) - 3);
	
	window.draw(btnShape);
	window.draw(btnText);
}

void Gui::Button::notify() {
	std::cout << "Pressed B:" << id << ".\n";
}

void Gui::Button::press() {
	down = true;
}

void Gui::Button::release() {
	down = false;
}

void Gui::Button::hover() {
	hovering = true;
}

void Gui::Button::unHover() {
	hovering = false;
}

int32_t Gui::Button::getId() {
	return id;
}

bool Gui::Button::getId(int32_t id) {
	return id == this->id;
}

bool Gui::Button::getId(std::initializer_list<int> ids) {
	for (auto id : ids)
		if (id == this->id)
			return true;

	return false;
}

float_t Gui::Button::getX() {
	return x;
}

float_t Gui::Button::getY() {
	return y;
}

float_t Gui::Button::getWidth() {
	return width;
}

float_t Gui::Button::getHeight() {
	return height;
}

std::string Gui::Button::getText() {
	return text;
}