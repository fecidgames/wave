#pragma once
#include "STATE.h"
#include "PlayerEntity.h"
#include "EntityHandler.h"
#include "Timer.hpp"

class EntityHandler;

class HUD {

public:
	HUD(sf::RenderWindow& window, EntityHandler& entityHandler);
	~HUD();

	void render();
	void startTime();
	void stopTime();

private:
	sf::RenderWindow& window;

	EntityHandler& entityHandler;
	Timer timer{};

	void renderHealth(PlayerEntity* player);
	void renderTimer();
	void renderShopAccess();
	void renderPauseAccess();

	bool showMilliseconds = false;

	std::string formatTime(int ms) {
		int seconds = ms / 1000;
		ms %= 1000;

		int minutes = seconds / 60;
		seconds %= 60;

		int hours = minutes / 60;
		minutes %= 60;

		std::string ret = "00:00";
		if(hours > 0)
			ret = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
		if(hours <= 0)
			ret = std::to_string(minutes) + ":" + std::to_string(seconds);
		if(hours > 0 && showMilliseconds)
			ret = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(ms);
		if(hours <= 0 && showMilliseconds)
			ret = std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(ms);

		return ret;
	}

};

