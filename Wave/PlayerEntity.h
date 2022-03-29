#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class PlayerEntity : public Entity {
public:
	PlayerEntity(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui, bool controllable);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();

	virtual uint32_t getUid() {
		return uid;
	}

	virtual sf::Color getColor() {
		return color;
	}

	virtual ID getId() {
		return id;
	}

	virtual float_t getVelX() {
		return velX;
	}

	virtual float_t getVelY() {
		return velY;
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

	bool isControllable() {
		return controllable;
	}

	virtual void setX(int32_t x) {
		this->x = x;
	}

	virtual void setY(int32_t y) {
		this-> y = y;
	}

	float_t velX, velY;

private:
	int32_t x;
	int32_t y;

	ID id;
	uint32_t uid;

	sf::Color color;

	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	sf::RectangleShape r;

	bool overGui = false;
	bool controllable = true;
	bool secondPlayer = false;

	EntityHandler& e;
};

