#pragma once
#include "Entity.hpp"
#include "EntityHandler.h"

class EntityHandler;

class TrailEntity : public Entity {
public:
	TrailEntity(int32_t x, int32_t y, ID id, uint32_t uid, float_t life, sf::Color c, EntityHandler& e);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();
	
	float getX() {
		return x;
	}
	
	float getY() {
		return y;
	}
	
	void setID(ID id) {
		this->id = id;
	}
	
	virtual ID getId() {
		return id;
	}

	virtual uint32_t getUid() {
		return uid;
	}

	virtual sf::Color getColor() {
		return parent->getColor();
	}

	virtual float_t getVelX() {
		return parent->getVelX();
	}

	virtual float_t getVelY() {
		return parent->getVelY();
	}

	virtual void setVelX(float_t velX) {
		this->velX = velX;
	}

	virtual void setVelY(float_t velY) {
		this->velY = velY;
	}

	virtual bool renderOverGui() {
		return overGui;
	}

	virtual void setX(int32_t x) {
		this->x = x;
	}

	virtual void setY(int32_t y) {
		this-> y = y;
	}

private:
	Entity* parent;
	int32_t x = 0, y = 0;
	float_t velX = 0, velY = 0, life = 0;
	ID id;
	uint32_t uid;
	uint32_t alpha = 255;
	bool overGui;

	sf::Color c;

	EntityHandler& e;
};

