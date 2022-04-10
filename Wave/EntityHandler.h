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

	void addMenuParticles();

	std::vector<Entity*> entities;
	std::map<Entity*, Entity*> trails;

	int32_t spawnTimer = 0;
};

