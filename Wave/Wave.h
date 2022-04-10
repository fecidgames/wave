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

private:
	void init();
	void render();
	void tick();
	void loop();

	MenuRenderer menuRenderer;
	InputHandler inputHandler;
	EntityHandler entityHandler;
	HUD hud;

	GameState state;

	sf::RenderWindow window;
};

