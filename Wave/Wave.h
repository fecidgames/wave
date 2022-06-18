#pragma once

#include <chrono>
#include <sys/timeb.h>
#include <ctime>
#include <fstream>
#include <sstream>

#include "InputHandler.h"
#include "EntityHandler.h"
#include "SoundHandler.h"
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

	double& getScale() {
		return scale;
	}

	uint32_t fps() {
		return framesPerSecond;
	}

	uint32_t nearest10(int32_t n) {
		int32_t a = (n / 10) * 10;
		int32_t b = a + 10;
		return (n - a > b - n)? b : a;
	}

private:
	void init();
	void render();
	void tick();
	void loop();
	void renderwin();

	uint32_t setting_volume = 50; //0 is off, dont pause song when volume is 0

	bool setting_vSync = true;
	bool setting_fullscreen = false;
	bool setting_menuParticles = true;
	bool setting_debugMenu = false;

	MenuRenderer menuRenderer;
	InputHandler inputHandler;
	EntityHandler entityHandler;
	SoundHandler soundHandler;
	HUD hud;

	uint32_t framesPerSecond = 0;

	GameState state;

	sf::RenderWindow window;

	double scale = 1;
	double startupFadeCol = 250;
};

