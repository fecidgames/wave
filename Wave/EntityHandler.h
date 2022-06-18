#pragma once

#include "MenuParticleEntity.h"
#include "PlayerEntity.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "SmartEnemy.h"
#include "TrailEntity.h"

class Wave;
class PlayerEntity;

class EntityHandler {

public:
	EntityHandler(Wave& wave);
	~EntityHandler();

	void setup();

	void add(Entity* e);

	void render(sf::RenderWindow& w, int32_t layer);
	void tick();

	void addMenuParticles();
	void addMenuParticles(int32_t layer);
	void addMenuParticlesWithPreviousColor();
	void removeMenuParticles();

	void hideHostileEntities();
	void hidePlayer();
	void hideParticles();
	void hideMeteors();

	void update();

	void die(PlayerEntity* player);

	std::vector<Entity*> entities;
	std::map<Entity*, Entity*> trails;

	Wave& getWaveAccess() {
		return wave;	
	}

	bool isSetup() {
		return hasBeenSetup;
	}

private:
	int32_t spawnTimer = 0;
	int32_t overTime = 0;
	int32_t msTime = 0;

	int32_t dpCount = 0; //Dead players

	std::vector<sf::Color> colors;

	bool hasBeenSetup = false;

	void tickSpawner(int32_t time);

	Wave& wave;
};

