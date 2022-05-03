#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <functional>

#include "EntityHandler.h"
#include "HUD.h"

#include "Arrow.h"
#include "Button.h"
#include "Checkbox.h"
#include "Slider.h"

class EntityHandler;
class Wave;

class MenuRenderer {

public:
	MenuRenderer(Wave& wave, EntityHandler& e, HUD& hud, GameState& state);
	~MenuRenderer();

	void render(sf::RenderWindow& window, bool onTop);

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
	void pauseGame(bool paused);

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

	void setWinningPlayer(std::string winner) {
		winningPlayer = winner;
	}

	void sendTime(int32_t ms, bool dual) {
		pTime = hud.formatTime(ms);

		//Check and set best time here accordingly
		if(dual) {
			//dualBest check & set
		} else {
			//personalBest check & set
		}
	}

	void renderDebugMenuOverlay(sf::RenderWindow& window);

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
	std::string personalBest = "00:00"; //Only infinite
	std::string dualBest = "00:00"; //Only dual
	std::string winningPlayer = "Player 1";
	std::string pTime = "00:00";

	HUD& hud;

	sf::Font menuFont;

	EntityHandler& e;

	Wave& wave;

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

