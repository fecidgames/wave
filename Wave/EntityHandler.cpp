#include "EntityHandler.h"
#include "Wave.h"

EntityHandler::EntityHandler(Wave& wave) : wave(wave) {
	
}

EntityHandler::~EntityHandler() {
	for(Entity* e : entities)
		delete &e;
}

void EntityHandler::setup() {
	std::srand(NULL);

	hasBeenSetup = true;

	if(wave.isMenuParticlesEnabled())
		addMenuParticles();
}

void EntityHandler::tick() {
	//All entities and trails will not update if the game is paused, with the exception of MenuParticles and their trails.

	for(Entity* e : entities) {
		//Allowing MenuParticles to be updated if the game is paused.
		if(e->getId() == ID::MenuParticle && wave.getMenuRenderer().isGamePaused()) {
			e->tick();
		} else {
			//Entities will update if the game is not paused.
			if(!wave.getMenuRenderer().isGamePaused())
				e->tick();
		}
	}

	for(auto const& t : trails) {
		//Allowing MenuParticle trails to be updated if the game is paused.
		if(t.first->getId() == ID::MenuParticle && wave.getMenuRenderer().isGamePaused()) {
			t.first->tick();
		} else {
			//Trails will update if the game is not paused.
			if(!wave.getMenuRenderer().isGamePaused())
				t.first->tick();
		}
	}

	if(wave.getMenuRenderer().isGamePaused())
		return;

	if(wave.getGameState().getGameState(STATE::STATE_GAME_INGAME)) {
		spawnTimer++;

		tickSpawner(spawnTimer);
	} else {
		spawnTimer = 0;
	}
}

void EntityHandler::update() {
	for(Entity* entity : entities)
		entity->update();
}

void EntityHandler::render(sf::RenderWindow& w, bool afterGui) {
	for(Entity* e : entities) {
		if(wave.getMenuRenderer().isPauseGuiHidden() && wave.getMenuRenderer().isGamePaused()) {
			if(e->getId() == ID::MenuParticle)
				e->render(w);
		} else {
			if(!afterGui && !e->renderOverGui())
				e->render(w);
			if(afterGui && e->renderOverGui())
				e->render(w);
		}
	}

	//The trail ID is the same as the parent ID
	for(auto const& t : trails) {
		if(wave.getMenuRenderer().isPauseGuiHidden() && wave.getMenuRenderer().isGamePaused()) {
			if(t.first->getId() == ID::MenuParticle)
				t.first->render(w);
		} else {
			if(!afterGui && !t.first->renderOverGui())
				t.first->render(w);
			if(afterGui && t.first->renderOverGui()) 
				t.first->render(w);
		}
	}
}

void EntityHandler::addMenuParticles() {
	for(int32_t i = 0; i < 15; i++)
		add(new MenuParticleEntity(std::rand()%(wave.getWindow()->getSize().x - 100), std::rand()%(wave.getWindow()->getSize().y - 50), ID::MenuParticle, i, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, false, wave.getScale()));
}

void EntityHandler::addMenuParticlesWithPreviousColor() {
	int32_t i = 0;
	for(sf::Color color : colors) {
		i++;
		add(new MenuParticleEntity(std::rand()%(wave.getWindow()->getSize().x - 100), std::rand()%(wave.getWindow()->getSize().y - 50), ID::MenuParticle, i, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, false, wave.getScale(), color));
	}
}

void EntityHandler::removeMenuParticles() {
	colors.clear();

	for(int32_t i = 0; i < entities.size(); i++)
		if(entities.at(i)->getId() == ID::MenuParticle) {
			colors.insert(colors.begin(), entities.at(i)->getColor());

			delete entities.at(i);

			entities.erase(entities.begin() + i);
			i--;
		}
}

void EntityHandler::add(Entity* e) {
	entities.insert(entities.begin(), e);
}

void EntityHandler::die(PlayerEntity* player) {
	bool shouldEnd = false;
	bool p1Died = false;

	for(int i = 0; i < entities.size(); i++) {
		if(entities.at(i)->getId() == ID::Player) {
			PlayerEntity* p = (PlayerEntity*) entities.at(i);
			if(p == player) {
				dpCount++;
				p->setAlive(false);
				p1Died = p->isPlayerOne();
			}
		}
	}

	shouldEnd = wave.getGameState().getGameMode(MODE::MODE_INFINITE) ? dpCount >= 1 : dpCount >= 2;

	if(wave.getGameState().getGameMode(MODE::MODE_DUAL) && !shouldEnd)
		wave.getMenuRenderer().setWinningPlayer(p1Died ? "Player 2" : "Player 1");

	if(shouldEnd) { //On GameOver
		dpCount = 0; //Reset dead players count
		wave.getHud().stopTime();
		wave.getMenuRenderer().sendTime(wave.getHud().getTimer().getElapsedMilliseconds(), !wave.getGameState().getGameMode(MODE::MODE_INFINITE));
		wave.getMenuRenderer().gameEnd();
	}
}

void EntityHandler::tickSpawner(int32_t time) {
	uint32_t uid = 28 + time;

	if(time == 1) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale()));
	}
	if(time == 300) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale()));
	}
	if(time == 600) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale()));
		add(new FastEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::FastEnemy, uid + 1, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale()));
	}
}
