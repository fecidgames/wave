#pragma once

#include <list>
#include <vector>
#include <iostream>

#include "STATE.h"
#include "EntityHandler.h"

class EntityHandler;

namespace Gui {
	class Button {
	public:
		bool down = false;
		bool hover = false;

		Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id);
		~Button();

		void render(sf::RenderWindow& window);

		int32_t getId() {
			return id;
		}

		bool getId(int32_t id) {
			return id == this->id;
		}

		float_t getX() {
			return x;
		}

		float_t getY() {
			return y;
		}

		float_t getWidth() {
			return width;
		}

		float_t getHeight() {
			return height;
		}

		std::string getText() {
			return text;
		}

	private:
		float_t x, y;
		float_t width, height;
		std::string text;
		int32_t id;
	};
}

class MenuRenderer {

public:
	MenuRenderer(EntityHandler& e);
	~MenuRenderer();

	void render(sf::RenderWindow& window);

	GameState gameState;

	std::list<Gui::Button*> getButtons() {
		return buttons;
	}

	void setup(STATE gameState);

private:
	std::list<Gui::Button*> buttons;
	std::vector<sf::RectangleShape> rects;
	std::list<sf::Text> texts;

	sf::Font menuFont;

	EntityHandler& e;

	void setupButtons(STATE gameState);
	void setupDrawables(STATE gameState);
	void setupEntities(STATE gameState);
};

