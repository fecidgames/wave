#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class MenuParticleEntity : public Entity { 
public:
	MenuParticleEntity(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui);

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

	virtual void setX(int32_t x) {
		this->x = x;
	}

	virtual void setY(int32_t y) {
		this-> y = y;
	}

private:
	int32_t x, y;
	float_t velX, velY;
	ID id;
	uint32_t uid;
	bool overGui;

	sf::RectangleShape r;
	sf::Color color;
	
	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	EntityHandler& e;
};

