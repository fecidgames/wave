#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class EntityHandler;

class MenuParticleEntity : public Entity { 
public:
	MenuParticleEntity(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui, double& scale, int32_t renderLayer);
	MenuParticleEntity(int32_t x, int32_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui, double& scale, sf::Color color, int32_t renderLayer);

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

	virtual void update();

private:
	int32_t x, y;
	int32_t velX, velY;

	ID id;
	uint32_t uid;

	int32_t renderLayer = 0;
	sf::RectangleShape r;
	double& scale;

	sf::Color color;
	
	sf::Vector2f horizontalBounds;
	sf::Vector2f verticalBounds;

	EntityHandler& e;
};

