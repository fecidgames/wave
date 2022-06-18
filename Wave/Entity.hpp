#pragma once

#include "STATE.h"
#include <cstdlib>
#include <iostream>
#include <list>

class Entity {
public:
	virtual void render(sf::RenderWindow& w) = 0;
	virtual void tick() = 0;

	virtual sf::RectangleShape getBounds() = 0;

	virtual uint32_t getUid() = 0;
	virtual ID getId() = 0;
	virtual bool getId(ID id) = 0;

	virtual sf::Color getColor() = 0;

	virtual void setRenderLayer(int32_t layer) = 0; //Renderlayer -1 will stop entity from rendering
	virtual int32_t getRenderLayer() = 0;
	virtual bool getRenderLayer(int32_t layer) = 0;

	virtual int32_t getVelX() = 0;
	virtual int32_t getVelY() = 0;

	virtual void setVelX(int32_t velX) = 0;
	virtual void setVelY(int32_t velY) = 0;

	virtual void setX(int32_t x) = 0;
	virtual void setY(int32_t y) = 0;

	virtual bool renderOverGui() = 0; //Will be unnecessary

	virtual void update() = 0;
};