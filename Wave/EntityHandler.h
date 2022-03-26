#pragma once

#include "MenuParticleEntity.h"
#include "TrailEntity.h"

class EntityHandler {

public:
	EntityHandler();
	~EntityHandler();

	void add(Entity* e);

	void render(sf::RenderWindow& w);
	void tick(sf::Time& dt);

	std::vector<Entity*> entities;
	std::map<Entity*, Entity*> trails;

};

