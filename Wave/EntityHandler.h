#pragma once

#include "MenuParticleEntity.h"
#include "PlayerEntity.h"
#include "TrailEntity.h"

class EntityHandler {

public:
	EntityHandler();
	~EntityHandler();

	void add(Entity* e);

	void render(sf::RenderWindow& w, bool afterGui);
	void tick();

	std::vector<Entity*> entities;
	std::map<Entity*, Entity*> trails;

};

