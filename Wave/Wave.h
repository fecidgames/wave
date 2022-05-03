#pragma once

#include <chrono>
#include <sys/timeb.h>
#include <ctime>
#include <fstream>
#include <sstream>

#include "InputHandler.h"
#include "EntityHandler.h"
#include "HUD.h"

class Wave {

public:
	Wave();
	~Wave();

	sf::RenderWindow* getWindow();
	GameState& getGameState();
	HUD& getHud();
	MenuRenderer& getMenuRenderer();

	void setVolume(int32_t volume);
	int32_t getVolume();

	void setHudSize(int32_t hudSize);
	int32_t getHudSize();

	void setVSyncEnabled(bool enabled);
	bool isVSyncEnabled();

	void setFullscreenEnabled(bool enabled);
	bool isFullscreenEnabled();

	void setMenuParticlesEnabled(bool enabled);
	bool isMenuParticlesEnabled();

	void setDebugMenuEnabled(bool enabled);
	bool isDebugMenuEnabled();

	void loadSettings();
	void saveSettings();

	void stop();

private:
	void init();
	void render();
	void tick();
	void loop();
	void renderwin();

	uint32_t setting_volume = 100; //0 is off, dont pause song when volume is 0
	uint32_t setting_hudSize = 0; //0 is default. This is a hud size multiplier

	bool setting_vSync = true;
	bool setting_fullscreen = false;
	bool setting_menuParticles = true;
	bool setting_debugMenu = false;

	MenuRenderer menuRenderer;
	InputHandler inputHandler;
	EntityHandler entityHandler;
	HUD hud;

	GameState state;

	sf::RenderWindow window;
};

