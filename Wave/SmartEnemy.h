#pragma once
#include "Entity.hpp"
#include "PlayerEntity.h"
#include "TrailEntity.h"

class EntityHandler;
class PlayerEntity;

class SmartEnemy : public Entity {
public:
	SmartEnemy(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, double scale, int32_t renderLayer, int32_t target);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();
	
	int32_t getX() { return x; }
	int32_t getY() { return y; }

	virtual void setX(int32_t x) { this->x = x; }
	virtual void setY(int32_t y) { this->y = y; }

	virtual int32_t getVelX() { return velX; }
	virtual int32_t getVelY() { return velY; }

	virtual void setVelX(int32_t velX) { this->velX = velX; }
	virtual void setVelY(int32_t velY) { this->velY = velY; }
	
	void setID(ID id)		  { this->id = id; }
	virtual ID getId()		  { return id; }
	virtual bool getId(ID id) { return this->id == id; }

	uint32_t getUid() { return uid; }

	virtual sf::Color getColor() { return sf::Color::Green; }

	virtual void setRenderLayer(int32_t layer);
	virtual int32_t getRenderLayer()			{ return renderLayer; }
	virtual bool getRenderLayer(int32_t layer)	{ return layer == renderLayer; }

	virtual void update();

private:
	int32_t x, y;
	float velX = 5, velY = -5;

	ID id;
	uint32_t uid;

	int32_t renderLayer = 0;
	sf::RectangleShape r;
	double scale = 1;

	PlayerEntity* target;
	
	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	EntityHandler& e;

	bool isOdd(int n) {
		return n % 2 == 0;
	}
};

