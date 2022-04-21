#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <functional>

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
		Checkbox(int32_t x, int32_t y, double scale, bool checked, int32_t id);

		void render(sf::RenderWindow& window);

		void click() {
			checked = !checked;
		}

		bool isChecked() {
			return checked;
		}

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

		int32_t getWidth() {
			return width;
		}

		int32_t getHeight() {
			return height;
		}

		double getScale() {
			return scale;
		}


	private:
		bool checked = true;
		int32_t x, y, width = 0, height = 0, id;
		double scale;
		sf::Texture textureChecked;
		sf::Texture textureNotChecked;
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

	class Arrow {
	public:
		Arrow(int32_t x, int32_t y, int32_t width, int32_t height, bool inverted, int32_t id);

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

		int32_t getWidth() {
			return width;
		}

		int32_t getHeight() {
			return height;
		}

		bool isInverted() {
			return inverted;
		}

	private:
		int32_t x, y, width, height, id;
		bool inverted;
	};
}

class MenuRenderer {

public:
	MenuRenderer(EntityHandler& e, HUD& hud, GameState& state);
	~MenuRenderer();

	void render(sf::RenderWindow& window);

	GameState& gameState;

	std::vector<Gui::Button*> getButtons() {
		return buttons;
	}

	std::vector<Gui::Slider*> getSliders() {
		return sliders;
	}

	std::vector<Gui::Checkbox*> getCheckboxes() {
		return checkboxes;
	}

	std::vector<Gui::Arrow*> getArrows() {
		return arrows;
	}

	void setup(STATE gameState);
	void resetDrawables();
	void exitConfirmation();
	void gameEnd();
	void pauseGame();

	HUD& getHud() {
		return hud;
	}

	bool isExitUnconfirmed() {
		return exitConfirmationPopup;
	}

	std::string getGameMode() {
		return gameMode;
	}

	bool isGamePaused() {
		return gamePaused;
	}

	void setGameMode(std::string gameMode) {
		this->gameMode = gameMode;

		gameState.setGameMode((gameMode == "Infinite") ? MODE::MODE_INFINITE : MODE::MODE_DUAL);

		descriptionr1 = (gameMode == "Infinite") ? "Play until you die. Enemies" : (gameMode == "Dual") ? "Battle against each other." : "An error occurred!";
		descriptionr2 = (gameMode == "Infinite") ? "will get harder over time." : (gameMode == "Dual") ? "Last one to die wins." : "";
	}

private:
	std::vector<Gui::Button*> buttons;
	std::vector<Gui::Slider*> sliders;
	std::vector<Gui::Checkbox*> checkboxes;
	std::vector<Gui::Arrow*> arrows;

	std::vector<sf::RectangleShape> rects;
	std::list<sf::Text> texts;

	std::string gameMode = "Infinite";
	std::string descriptionr1 = "Play until you die. Enemies";
	std::string descriptionr2 = "will get harder over time.";
	std::string personalBest = "00:00";

	HUD& hud;

	sf::Font menuFont;

	EntityHandler& e;

	uint32_t time = 0;

	bool exitConfirmationPopup = false;
	bool gamePaused = false;

	bool isOdd(int n) {
		return n % 2 == 0;
	}

	void setupButtons(STATE gameState);
	void setupDrawables(STATE gameState);
	void setupEntities(STATE gameState);

	void clearLists();

	void playerPos(PlayerEntity* p);
};

