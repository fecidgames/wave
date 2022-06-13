#pragma once
#include "Entity.hpp"
#include "EntityHandler.h"

class EntityHandler;

class TrailEntity : public Entity {
public:
	TrailEntity(int32_t x, int32_t y, ID id, uint32_t uid, int32_t life, sf::Color c, EntityHandler& e, double scale);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();
	
	int32_t getX() {
		return x;
	}
	
	int32_t getY() {
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

	virtual int32_t getVelX() {
		return parent->getVelX();
	}

	virtual int32_t getVelY() {
		return parent->getVelY();
	}

	virtual void setVelX(int32_t velX) {
		this->velX = velX;
	}

	virtual void setVelY(int32_t velY) {
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

	virtual void update();

private:
	Entity* parent;
	int32_t x = 0, y = 0;
	int32_t velX = 0, velY = 0, life = 0;
	ID id;
	uint32_t uid;
	uint32_t alpha = 255;
	double scale;
	bool overGui;

	sf::Color c;

	EntityHandler& e;
};

