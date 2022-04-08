#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class PlayerEntity : public Entity {
public:
	PlayerEntity(uint32_t x, uint32_t y, ID id, uint32_t uid, sf::Vector2i horizontalBounds, sf::Vector2i verticalBounds, EntityHandler& e, bool overGui, bool controllable);

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

	virtual int32_t getVelX() {
		return velX;
	}

	virtual int32_t getVelY() {
		return velY;
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

	bool isControllable() {
		return controllable;
	}

	virtual void setX(int32_t x) {
		this->x = x;
	}

	virtual void setY(int32_t y) {
		this-> y = y;
	}

	bool isPlayerOne() {
		return !secondPlayer;
	}

	int32_t velX = 0, velY = 0;

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

