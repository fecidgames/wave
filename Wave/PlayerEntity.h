#pragma once
#include "Entity.hpp"
#include "TrailEntity.h"

class PlayerEntity : public Entity {
public:
	PlayerEntity(float_t x, float_t y, ID id, uint32_t uid, sf::Vector2f horizontalBounds, sf::Vector2f verticalBounds, EntityHandler& e, bool overGui, bool controllable);

	virtual void render(sf::RenderWindow& w);
	virtual void tick();
	virtual sf::RectangleShape getBounds();

private:
	EntityHandler& e;
};

