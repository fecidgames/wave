#pragma once
#include "STATE.h"
#include "PlayerEntity.h"
#include "EntityHandler.h"
#include "Timer.hpp"

class EntityHandler;

class HUD {

public:
	HUD(sf::RenderWindow& window, EntityHandler& e);
	~HUD();

	void render();
	void startTime();
	void stopTime();

private:
	sf::RenderWindow& window;

	EntityHandler& e;
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

		std::string sec = "00";
		std::string min = "00";
		std::string ret = min + ":" + sec;

		sec = (seconds < 10) ? ("0" + std::to_string(seconds)) : std::to_string(seconds);
		min = (seconds < 10) ? ("0" + std::to_string(minutes)) : std::to_string(minutes);

		if(hours > 0)
			ret = std::to_string(hours) + ":" + min + ":" + sec;
		if(hours <= 0)
			ret = min + ":" + sec;
		if(hours > 0 && showMilliseconds)
			ret = std::to_string(hours) + ":" + min + ":" + sec + ":" + std::to_string(ms);
		if(hours <= 0 && showMilliseconds)
			ret = min + ":" + sec + ":" + std::to_string(ms);

		return ret;
	}

};

