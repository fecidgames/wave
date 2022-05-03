#include "Slider.h"

Gui::Slider::Slider(int32_t x, int32_t y, int32_t length, int32_t blockWidth, int32_t blockHeight, int32_t id) : x(x), y(y), length(length), blockWidth(blockWidth), blockHeight(blockHeight), id(id) {
	blockX = x;
	mxr = 0;
}

void Gui::Slider::render(sf::RenderWindow& window) {
	sf::RectangleShape block(sf::Vector2f(!hovering ? blockWidth : blockWidth + 6, !hovering ? blockHeight : blockHeight + 6));
	block.setPosition(!hovering ? blockX : blockX - 3, !hovering ? y - blockHeight / 2 : y - blockHeight / 2 - 3);
	block.setFillColor(sf::Color::White);
	
	sf::RectangleShape sliderLine(sf::Vector2f(length, 1));
	sliderLine.setPosition(x, y);

	window.draw(block);
	window.draw(sliderLine);
}

void Gui::Slider::hover() {
	hovering = true;
}

void Gui::Slider::unHover() {
	hovering = false;
}

void Gui::Slider::drag() {
	dragging = true;
}

void Gui::Slider::release() {
	dragging = false;
}

bool Gui::Slider::isDragging() {
	return dragging;
}

int32_t Gui::Slider::getMXR() {
	return mxr;
}

void Gui::Slider::setMXR(int32_t mxr) {
	this->mxr = mxr;
}

int32_t Gui::Slider::getId() {
	return id;
}

bool Gui::Slider::getId(int32_t id) {
	return id == this->id;
}

int32_t Gui::Slider::getX() {
	return x;
}

int32_t Gui::Slider::getY() {
	return y;
}

int32_t Gui::Slider::getLength() {
	return length;
}

int32_t Gui::Slider::getBlockWidth() {
	return blockWidth;
}

int32_t Gui::Slider::getBlockHeight() {
	return blockHeight;
}

int32_t Gui::Slider::getBlockX() {
	return blockX;
}

void Gui::Slider::setBlockX(int32_t blockX) {
	if(blockX > (x + length - blockWidth))
		this->blockX = x + length - blockWidth;
	else if(blockX < x) 
		this->blockX = x;
	else
		this->blockX = blockX;
}