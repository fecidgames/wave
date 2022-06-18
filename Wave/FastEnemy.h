#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class FastEnemy : public Entity {
public:
	FastEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, double scale, int32_t renderLayer);

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

	virtual bool getId(ID id) {
		return this->id == id;
	}
	
	virtual ID getId() {
		return id;
	}

	uint32_t getUid() {
		return uid;
	}

	virtual sf::Color getColor() {
		return sf::Color(242, 202, 90);
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
		return false;
	}

	virtual void setX(int32_t x) {
		this->x = x;
	}

	virtual void setY(int32_t y) {
		this-> y = y;
	}

	virtual int32_t getRenderLayer() {
		return renderLayer;
	}

	virtual bool getRenderLayer(int32_t layer) {
		return layer == renderLayer;
	}

	virtual void setRenderLayer(int32_t layer);

	virtual void update();

private:
	int32_t x, y;
	int32_t velX = 5, velY = -5;
	int32_t renderLayer = 0;
	ID id;
	uint32_t uid;

	double scale = 1.0;

	sf::RectangleShape r;
	
	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	EntityHandler& e;

	bool isOdd(int n) {
		return n % 2 == 0;
	}
};

