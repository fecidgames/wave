#pragma once

#include <chrono>
#include <sys/timeb.h>
#include <ctime>

#include "InputHandler.h"
#include "EntityHandler.h"

class Wave {

public:
	Wave(sf::ContextSettings settings);
	~Wave();

	sf::RenderWindow* getWindow();

private:
	void init();
	void render(sf::Time& dt);
	void tick(sf::Time& dt);
	void loop();

	MenuRenderer menuRenderer;
	InputHandler inputHandler;
	EntityHandler entityHandler;

	GameState state;

	sf::RenderWindow window;
};

