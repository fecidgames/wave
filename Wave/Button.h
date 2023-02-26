#pragma once

#include "STATE.h"
#include <iostream>
#include <initializer_list>

namespace Gui {

class Button {

public:
	Button(float_t x, float_t y, float_t width, float_t height, std::string text, int32_t id, int32_t layer);

	void render(sf::RenderWindow& window);

	void press();
	void release();

	void hover();
	void unHover();

	void notify();

	int32_t getId();
	bool getId(int32_t id);
	bool getId(std::initializer_list<int> ids);

	float_t getX();
	float_t getY();
	float_t getWidth();
	float_t getHeight();

	std::string getText();

	int32_t getLayer() { return layer; }

	const static int ID_MAIN_GAMEMODES = 0;
	const static int ID_MAIN_OPTIONS = 1;
	const static int ID_MAIN_HELP = 2;
	const static int ID_MAIN_QUIT = 3;
	const static int ID_MAIN_SHOP = 8;

	const static int ID_SELECT_PLAY = 5;
	const static int ID_DEBUG_KILLALL = 40;

	const static int ID_PAUSE_CONTINUE = 9;
	const static int ID_PAUSE_MAINMENU = 10;
	const static int ID_PAUSE_OPTIONS = 99;

	const static int ID_QUIT_NO = 90;
	const static int ID_QUIT_YES = 91;

	const static int ID_GLOBAL_BACK = 4;

private:
	float_t x, y;
	float_t width, height;

	std::string text;

	int32_t id;
	int32_t layer = 1;

	bool down = false;
	bool hovering = false;
};

}

