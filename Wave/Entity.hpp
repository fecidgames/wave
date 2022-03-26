#pragma once

#include "STATE.h"
#include <cstdlib>
#include <iostream>
#include <list>

class Entity {
public:
	virtual void render(sf::RenderWindow& w) = 0;
	virtual void tick(sf::Time& dt) = 0;
	virtual sf::RectangleShape getBounds() = 0;
	virtual uint32_t getUid() = 0;
	virtual sf::Color getColor() = 0;
	virtual ID getId() = 0;

	virtual float_t getVelX() = 0;
	virtual float_t getVelY() = 0;

	virtual void setVelX(float_t velX) = 0;
	virtual void setVelY(float_t velY) = 0;

	virtual bool renderOverGui() = 0;

};