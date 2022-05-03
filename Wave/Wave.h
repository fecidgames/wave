#pragma once

#include <chrono>
#include <sys/timeb.h>
#include <ctime>

#include "InputHandler.h"
#include "EntityHandler.h"
#include "HUD.h"

class Wave {

public:
	Wave(sf::ContextSettings settings);
	~Wave();

	sf::RenderWindow* getWindow();
	GameState& getGameState();
	HUD& getHud();
	MenuRenderer& getMenuRenderer();

	void setMenuParticlesEnabled(bool enabled) {
		setting_menuParticles = enabled;
	}

	bool isMenuParticlesEnabled() {
		return setting_menuParticles;
	}

	void setDebugMenuEnabled(bool enabled) {
		setting_debugMenu = enabled;
	}

	bool isDebugMenuEnabled() {
		return setting_debugMenu;
	}

private:
	void init();
	void render();
	void tick();
	void loop();

	int32_t setting_volume = 0; //0 is off, dont pause song when volume is 0
	int32_t setting_hudSize = 0; //0 is default. This is a hud size multiplier

	bool setting_vSync = 1;
	bool setting_fullscreen = 0;
	bool setting_menuParticles = 1;
	bool setting_debugMenu = 0;

	MenuRenderer menuRenderer;
	InputHandler inputHandler;
	EntityHandler entityHandler;
	HUD hud;

	GameState state;

	sf::RenderWindow window;
};

