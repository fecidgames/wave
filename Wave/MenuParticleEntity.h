#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class MenuParticleEntity : public Entity { 
public:
	MenuParticleEntity(float_t x, float_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();

	void setX(float_t x) {
		this->x = x;
	}
	
	void setY(float_t y) {
		this->y = y;
	}
	
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

	uint32_t getUid() {
		return uid;
	}

	virtual sf::Color getColor() {
		return color;
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

private:
	float_t x, y, velX = 0, velY = 0;
	ID id;
	uint32_t uid;
	bool overGui;

	sf::RectangleShape r;
	sf::Color color;
	
	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	EntityHandler& e;
};

