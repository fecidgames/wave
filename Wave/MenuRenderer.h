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

	void render(sf::RenderWindow& window, int32_t layer);

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

	void sendScore(int _score) {
		this->score = _score;
		gameScore = std::to_string(score) + " points.";

		//add score to total points for shop stuff
	}

	bool isPauseGuiHidden() {
		return !pauseGuiShown;
	}

	void setup(STATE gameState);
	void setupInGame(STATE gameState);

	void resetDrawables();
	void exitConfirmation();
	void gameEnd();
	void hidePauseGUI();
	void pauseGame();
	void pauseGame(bool paused);
	void setupDebugMenu(bool enabled);

	sf::Text createText(double x, double y, std::string text, int size);
	sf::Text createText(std::string text, int size);

	sf::Text createCenteredTextX(double y, std::string text, int size);
	sf::Text createCenteredTextX(double y, std::string text, int size, int half); //0 is left, 1 is right
	sf::Text createCenteredTextY(double x, std::string text, int size);
	sf::Text createCenteredTextY(double x, std::string text, int size, int half); //0 is top, 1 is bottom
	sf::Text createCenteredTextXY(std::string text, int size);
	sf::Text createCenteredTextXY(std::string text, int size, int side); // 0 is left center, 1 is right center, 2 is bottom center, 3 is top center

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
	std::string gameScore = "0 points";

	HUD& hud;

	sf::Font menuFont;

	EntityHandler& e;
	Wave& wave;

	uint32_t time = 0;
	uint32_t score = 0;
	uint32_t total_score = 0;

	bool exitConfirmationPopup = false;
	bool gamePaused = false;
	bool pauseGuiShown = false;

	bool isOdd(int n) {
		return n % 2 == 0;
	}

	Gui::Slider* volumeSlider;
	int32_t getVolumeX();

	void setupButtons(STATE gameState);
	void setupDrawables(STATE gameState);
	void setupEntities(STATE gameState);

	void clearLists();

	void playerPos(PlayerEntity* p);
};

