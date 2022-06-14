#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Window {
	static uint32_t WIDTH = 1080;
	static uint32_t HEIGHT = 720;
}

enum class ID {
	Player,
	Trail,
	MenuParticle,

	BasicEnemy,
	FastEnemy,
	SmartEnemy,

	MeteorShower,
	MeteorShowerParticle
};

enum class MODE {
	MODE_INFINITE,
	MODE_DUAL,
	MODE_BATTLE
};

enum class STATE {
	STATE_MENU_MAIN,
	STATE_MENU_SELECT,
	STATE_MENU_SETTINGS,
	STATE_MENU_HELP,
	STATE_MENU_SHOP,
	STATE_MENU_GAMEOVER,

	STATE_GAME_INGAME,
	STATE_GAME_PAUSED
};

class GameState {
	
private:
	STATE gameState = STATE::STATE_MENU_MAIN;
	STATE lastState = gameState;

	MODE gameMode = MODE::MODE_INFINITE;

public:
	STATE getGameState() {
		return gameState;
	}

	void revertGameState() {
		setGameState(lastState);
	}

	STATE getLastState() {
		return lastState;
	}

	bool getLastState(STATE lastState) {
		return lastState == this->lastState;
	}

	bool getGameState(STATE gameState) {
		return gameState == this->gameState;
	}

	MODE getGameMode() {
		return gameMode;
	}

	bool getGameMode(MODE gameMode) {
		return gameMode == this->gameMode;
	}

	void setGameState(STATE state) {
		lastState = gameState;
		gameState = state;
	}

	void setGameMode(MODE mode) {
		gameMode = mode;
	}
};