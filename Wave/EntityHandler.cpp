#include "EntityHandler.h"
#include "Wave.h"

EntityHandler::EntityHandler(Wave& wave) : wave(wave) {
	std::srand(NULL);

	if(wave.isMenuParticlesEnabled())
		addMenuParticles();
}

EntityHandler::~EntityHandler() {
	for(Entity* e : entities) {
		delete e;
	}
}

void EntityHandler::tick() {
	if(wave.getMenuRenderer().isGamePaused())
		return;

	for(Entity* e : entities) {
		e->tick();
	}

	for(auto const& t : trails) {
		t.first->tick();
	}

	if(wave.getGameState().getGameState(STATE::STATE_GAME_INGAME)) {
		spawnTimer++;

		tickSpawner(spawnTimer);
	} else {
		spawnTimer = 0;
	}
}

void EntityHandler::render(sf::RenderWindow& w, bool afterGui) {
	for(Entity* e : entities) {
		if(!afterGui && !e->renderOverGui())
			e->render(w);
		if(afterGui && e->renderOverGui())
			e->render(w);
	}

	for(auto const& t : trails) {
		if(!afterGui && !t.first->renderOverGui())
			t.first->render(w);
		if(afterGui && t.first->renderOverGui()) 
			t.first->render(w);
	}
}

void EntityHandler::addMenuParticles() {
	for(int32_t i = 0; i < 15; i++)
		add(new MenuParticleEntity(std::rand()%(Window::WIDTH - 50), std::rand()%(Window::HEIGHT - 50), ID::MenuParticle, i, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this, false));
}

void EntityHandler::removeMenuParticles() {
	for(int i = 0; i < entities.size(); i++)
		if(entities.at(i)->getId() == ID::MenuParticle) {
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
		add(new BasicEnemy(std::rand()%(Window::WIDTH - 50), std::rand()%(Window::HEIGHT - 50), ID::BasicEnemy, uid, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this));
	}
	if(time == 300) {
		add(new BasicEnemy(std::rand()%(Window::WIDTH - 150), std::rand()%(Window::HEIGHT - 30), ID::BasicEnemy, uid, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this));
	}
	if(time == 600) {
		add(new BasicEnemy(std::rand()%(Window::WIDTH - 150), std::rand()%(Window::HEIGHT - 30), ID::BasicEnemy, uid, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this));
		add(new FastEnemy(std::rand()%(Window::WIDTH - 150), std::rand()%(Window::HEIGHT - 30), ID::FastEnemy, uid + 1, sf::Vector2f(0, Window::WIDTH), sf::Vector2f(0, Window::HEIGHT), *this));
	}
}
