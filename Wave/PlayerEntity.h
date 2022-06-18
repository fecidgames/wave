#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class PlayerEntity : public Entity {
public:
	PlayerEntity(uint32_t x, uint32_t y, ID id, uint32_t uid, sf::Vector2i horizontalBounds, sf::Vector2i verticalBounds, EntityHandler& e, bool overGui, bool controllable, double scale, int32_t renderLayer);
	PlayerEntity(uint32_t x, uint32_t y, ID id, uint32_t uid, sf::Vector2i horizontalBounds, sf::Vector2i verticalBounds, EntityHandler& e, bool overGui, bool controllable, int32_t health, double scale, int32_t renderLayer);

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

	virtual sf::Color getColor() { return color; }

	virtual void setRenderLayer(int32_t layer);
	virtual int32_t getRenderLayer()			{ return renderLayer; }
	virtual bool getRenderLayer(int32_t layer)	{ return layer == renderLayer; }

	double getHealth() { return health; }
	void setHealth(double v) { health = v; }

	void setAlive(bool v) { alive = v; }
	bool isAlive() { return alive; }
	bool isDead() { return !alive; }

	void collision();
	virtual void update();

	bool isControllable() { return controllable; }

	bool isPlayerOne() { return !secondPlayer; }

private:
	int32_t x, y;
	int32_t velX = 0, velY = 0;

	double health;

	ID id;
	uint32_t uid;

	sf::Color color;

	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	int32_t renderLayer = 0;
	sf::RectangleShape r;
	double scale = 1;

	bool overGui = false;
	bool controllable = true;
	bool secondPlayer = false;

	bool alive = true;

	EntityHandler& e;
};

