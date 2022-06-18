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
	//MenuParticles update while game is paused.

	for(Entity* e : entities)
		if(!wave.getMenuRenderer().isGamePaused() || e->getId(ID::MenuParticle))
			e->tick();

	for(auto const& t : trails)
		if(!wave.getMenuRenderer().isGamePaused() || t.first->getId(ID::MenuParticle))
			t.first->tick();

	if(!wave.getMenuRenderer().isGamePaused()) {
		if(wave.getGameState().getGameState(STATE::STATE_GAME_INGAME)) {
			spawnTimer++;

			tickSpawner(spawnTimer);
			return;
		}
	}

	spawnTimer = 0;
}

void EntityHandler::update() {
	for(Entity* e : entities)
		e->update();
}

void EntityHandler::render(sf::RenderWindow& w, int32_t layer) {
	for(Entity* e : entities)
		if(e->getRenderLayer(layer))
			e->render(w);

	for(auto const& t : trails)
		if(t.first->getRenderLayer(layer))
			t.first->render(w);
}

void EntityHandler::hideHostileEntities() {
	for(Entity* e : entities)
		if(e->getId(ID::BasicEnemy) || e->getId(ID::FastEnemy) || e->getId(ID::MeteorShowerParticle) || e->getId(ID::SmartEnemy)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::hidePlayer() {
	for(Entity* e : entities)
		if(e->getId(ID::Player)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::hideParticles() {
	for(Entity* e : entities)
		if(e->getId(ID::MenuParticle)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::hideMeteors() {
	for(Entity* e : entities)
		if(e->getId(ID::MeteorShowerParticle)) {
			e->setRenderLayer(e->getRenderLayer() >= 0 ? -1 : 0);
			std::cout << "Set render layer of E:" << e->getUid() << " to " << e->getRenderLayer() << std::endl;
		}
}

void EntityHandler::addMenuParticles() {
	addMenuParticles(0);
}

void EntityHandler::addMenuParticles(int32_t layer) {
	for(int32_t i = 0; i < 15; i++)
		add(new MenuParticleEntity(std::rand()%(wave.getWindow()->getSize().x - 100), std::rand()%(wave.getWindow()->getSize().y - 50), ID::MenuParticle, i, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, false, wave.getScale(), layer));
}

void EntityHandler::addMenuParticlesWithPreviousColor() {
	int32_t i = 0;
	for(sf::Color color : colors) {
		i++;
		add(new MenuParticleEntity(std::rand()%(wave.getWindow()->getSize().x - 100), std::rand()%(wave.getWindow()->getSize().y - 50), ID::MenuParticle, i, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, false, wave.getScale(), color, 0));
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
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}
	if(time == 300) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}
	if(time == 600) {
		add(new BasicEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::BasicEnemy, uid, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
		add(new FastEnemy(std::rand()%(wave.getWindow()->getSize().x - (int) (32 * wave.getScale() + 10)), std::rand()%(wave.getWindow()->getSize().y - (int) (32 * wave.getScale() + 10)), ID::FastEnemy, uid + 1, sf::Vector2f(0, wave.getWindow()->getSize().x), sf::Vector2f(0, wave.getWindow()->getSize().y), *this, wave.getScale(), 0));
	}
}
