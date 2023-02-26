#pragma once
#include "Entity.hpp"
#include "PlayerEntity.h"

class EntityHandler;

class LaserEntity : public Entity {
public:
	LaserEntity(int32_t y, ID id, int32_t uid, PlayerEntity* target, EntityHandler& e, double scale, int32_t renderLayer);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();

	int32_t getX() { return target->getBounds().getPosition().x; }
	int32_t getY() { return y; }

	virtual void setX(int32_t x) {  }
	virtual void setY(int32_t y) { this->y = y; }

	virtual int32_t getVelX() { return 0; }
	virtual int32_t getVelY() { return 0; }

	virtual void setVelX(int32_t velX) {  }
	virtual void setVelY(int32_t velY) {  }

	void setID(ID id) { this->id = id; }
	virtual ID getId() { return id; }
	virtual bool getId(ID id) { return this->id == id; }

	uint32_t getUid() { return uid; }

	virtual sf::Color getColor() { return sf::Color::Red; }

	virtual void setRenderLayer(int32_t layer) { renderLayer = layer; }
	virtual int32_t getRenderLayer() { return renderLayer; }
	virtual bool getRenderLayer(int32_t layer) { return layer == renderLayer; }

	virtual void update();

private:
	int32_t y;
	double scale;

	ID id;
	int32_t uid;

	PlayerEntity* target;

	int32_t renderLayer;

	sf::RectangleShape r;
	EntityHandler& e;

};
