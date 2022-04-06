#pragma once

#include <list>
#include <vector>
#include <iostream>

#include "STATE.h"
#include "EntityHandler.h"
#include "HUD.h"

class EntityHandler;

namespace Gui {
	class Button {
	public:
		bool down = false;
		bool hover = false;

		Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id);

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

	class Checkbox {
	public:
		bool checked = false;

		Checkbox(int32_t x, int32_t y, int32_t size, bool checked, int32_t id);

		void render(sf::RenderWindow& window);
		void updateTexture();

		int32_t getId() {
			return id;
		}

		bool getId(int32_t id) {
			return id == this->id;
		}

		int32_t getX() {
			return x;
		}

		int32_t getY() {
			return y;
		}

		int32_t getSize() {
			return size;
		}


	private:
		int32_t x, y, size, id;
		sf::Texture texture;
	};

	class Slider {
	public:
		bool hover = false;
		bool dragging = false;

		int32_t mxr;

		Slider(int32_t x, int32_t y, int32_t length, int32_t blockWidth, int32_t blockHeight, int32_t id);

		void render(sf::RenderWindow& window);

		int32_t getId() {
			return id;
		}

		bool getId(int32_t id) {
			return id == this->id;
		}

		int32_t getX() {
			return x;
		}

		int32_t getY() {
			return y;
		}

		int32_t getLength() {
			return length;
		}

		int32_t getBlockWidth() {
			return blockWidth;
		}

		int32_t getBlockHeight() {
			return blockHeight;
		}

		int32_t getBlockX() {
			return blockX;
		}

		void setBlockX(int32_t blockX) {
			if(blockX > (x + length - blockWidth))
				this->blockX = x + length - blockWidth;
			else if(blockX < x) 
				this->blockX = x;
			else
				this->blockX = blockX;
		}

	private:
		int32_t x, y, length, blockWidth, blockHeight, id, blockX = 0;
	};
}

class MenuRenderer {

public:
	MenuRenderer(EntityHandler& e, HUD& hud);
	~MenuRenderer();

	void render(sf::RenderWindow& window);

	GameState gameState;

	std::vector<Gui::Button*> getButtons() {
		return buttons;
	}

	std::vector<Gui::Slider*> getSliders() {
		return sliders;
	}

	std::vector<Gui::Checkbox*> getCheckboxes() {
		return checkboxes;
	}

	void setup(STATE gameState);

	HUD& getHud() {
		return hud;
	}

private:
	std::vector<Gui::Button*> buttons;
	std::vector<Gui::Slider*> sliders;
	std::vector<Gui::Checkbox*> checkboxes;

	std::vector<sf::RectangleShape> rects;
	std::list<sf::Text> texts;

	HUD& hud;

	sf::Font menuFont;

	EntityHandler& e;

	uint32_t time = 0;

	bool isOdd(int n) {
		return n % 2 == 0;
	}

	void setupButtons(STATE gameState);
	void setupDrawables(STATE gameState);
	void setupEntities(STATE gameState);

	void playerPos(PlayerEntity* p);
};

