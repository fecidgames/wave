#pragma once

#include "MenuParticleEntity.h"
#include "PlayerEntity.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "TrailEntity.h"

class Wave;

class EntityHandler {

public:
	EntityHandler(Wave& wave);
	~EntityHandler();

	void add(Entity* e);

	void render(sf::RenderWindow& w, bool afterGui);
	void tick();

	void addMenuParticles();

	std::vector<Entity*> entities;
	std::map<Entity*, Entity*> trails;

private:
	int32_t spawnTimer = 0;
	int32_t overTime = 0;
	int32_t msTime = 0;

	void tickSpawner(int32_t time);

	Wave& wave;
};

